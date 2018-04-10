//                                               -*- C++ -*-
/**
 *  @brief Regression
 *
 *  Copyright 2005-2018 EDF-EADS-Phimeca
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include "otsvm/LibSVMRegression.hxx"
#include "otsvm/NormalRBF.hxx"
#include "otsvm/PolynomialKernel.hxx"
#include "otsvm/SVMKernelRegressionEvaluation.hxx"
#include "otsvm/SigmoidKernel.hxx"
#include "otsvm/LinearKernel.hxx"
#include <openturns/ComposedFunction.hxx>
#include <openturns/PersistentObjectFactory.hxx>
#include <openturns/AggregatedFunction.hxx>

using namespace OT;


namespace OTSVM
{

static Factory<LibSVMRegression> RegisteredFactory;


CLASSNAMEINIT(LibSVMRegression)

/* Default constructor */
LibSVMRegression::LibSVMRegression(): SVMRegressionImplementation()
{
  //Nothing to do
}

/* Constructor with parameters */
LibSVMRegression::LibSVMRegression(const Sample & dataIn,
                                   const Sample & dataOut,
                                   const LibSVM::KernelType kerneltype )
  : SVMRegressionImplementation()
  , inputSample_(dataIn)
  , outputSample_(dataOut)
{
  driver_.setSvmType(LibSVM::EpsilonSupportRegression);
  driver_.setKernelType(kerneltype);
  driver_.setP(1e-5);
}


/* Virtual constructor */
LibSVMRegression * LibSVMRegression::clone() const
{
  return new LibSVMRegression(*this);
}

/* Method run */
void LibSVMRegression::run()
{

  const UnsignedInteger outputDimension = outputSample_.getDimension();
  const UnsignedInteger inputDimension = inputSample_.getDimension();
  const UnsignedInteger size = inputSample_.getSize();
  const UnsignedInteger sizeOutput = outputSample_.getSize();

  if(sizeOutput != size) throw InvalidArgumentException(HERE) << "Error: the input sample and the output sample must have the same size ";

  UnsignedInteger tempTradeoff = 0;
  UnsignedInteger tempKernel = 0;

  Scalar totalerror = 0;
  Scalar minerror = 0;

  Sample isoProbSample( size , inputDimension );
  Function outputTransformation;
  Function outputInverseTransformation;

  Collection<Function> marginals;
  Collection<Function> outputTransformationMarginals;

  Point relativeError( outputDimension );
  Point residu( outputDimension );
  Point variance( outputDimension );

  driver_.normalize(outputSample_, outputTransformation, outputInverseTransformation);
  Sample normalizedOutputSample(outputTransformation(outputSample_));

  /* For each component of the output Sample , we compute the same algorithm.
  * First, we make a cross validation to determinate the best parameters.
  * Second, we train the problem and retreive some results ( support vectors, support vectors coefficients, kernel parameters).
  * Third, we build the model with OpenTurns and save results in the MetaModelResult */
  for( UnsignedInteger componentIndex = 0 ; componentIndex < outputDimension ; componentIndex ++)
  {
    driver_.convertData(inputSample_, normalizedOutputSample.getMarginal(componentIndex) );

    if( tradeoffFactor_.getSize() > 1 || kernelParameter_.getSize() > 1 )
    {
      for( UnsignedInteger tradeoffIndex = 0 ; tradeoffIndex < tradeoffFactor_.getSize() ; tradeoffIndex ++ )
      {
        driver_.setTradeoffFactor( tradeoffFactor_[tradeoffIndex] );
        for( UnsignedInteger kernelParameterIndex = 0 ; kernelParameterIndex < kernelParameter_.getSize() ; kernelParameterIndex ++)
        {
          driver_.setKernelParameter( kernelParameter_[kernelParameterIndex] );

          totalerror = driver_.runCrossValidation();

          if( totalerror < minerror || (tradeoffIndex == 0 && kernelParameterIndex == 0))
          {
            minerror = totalerror;
            tempTradeoff = tradeoffIndex;
            tempKernel = kernelParameterIndex;
          }
          LOGINFO( OSS() << "Cross Validation for C=" << tradeoffFactor_[tradeoffIndex] << " and gamma=" << kernelParameter_[kernelParameterIndex] << " error=" << totalerror );
          totalerror = 0;
        }
      }
    }
    driver_.setTradeoffFactor( tradeoffFactor_[tempTradeoff] );
    driver_.setKernelParameter( kernelParameter_[tempKernel] );
    driver_.performTrain();

    Point svcoef(driver_.getSupportVectorCoef());

    Sample supportvector( driver_.getNumberSupportVector() , inputDimension );
    supportvector = driver_.getSupportVector( inputDimension );

    switch(driver_.getKernelType())
    {
      case POLY:
        kernel_ = PolynomialKernel( driver_.getDegree() , driver_.getGamma() , driver_.getPolynomialConstant() );
        break;
      case RBF:
        kernel_ = NormalRBF( 1 / ( sqrt( 2 * driver_.getGamma() )));
        break;
      case SIGMOID:
        kernel_ = SigmoidKernel( driver_.getGamma() , driver_.getConstant() );
        break;
      case LINEAR:
        kernel_ = LinearKernel();
        break;
    }

    Function function;
    function.setEvaluation(new SVMKernelRegressionEvaluation( kernel_ , svcoef , supportvector , driver_.getConstant()));
    function.setGradient(new SVMKernelRegressionGradient( kernel_ , svcoef , supportvector , driver_.getConstant()));
    function.setHessian(new SVMKernelRegressionHessian( kernel_ , svcoef , supportvector , driver_.getConstant()));

    marginals.add( function );
    driver_.destroy();
    driver_.destroyModel();
  }

  AggregatedFunction aggregated(marginals);
  ComposedFunction composed(aggregated, driver_.getInputTransformation());
  ComposedFunction metaModel(outputInverseTransformation, composed);

  // compute residual, relative error
  Point residuals(outputDimension);
  Point relativeErrors(outputDimension);
  Sample mY(metaModel(inputSample_));
  Point outputVariance(outputSample_.computeVariance());

  for ( UnsignedInteger outputIndex = 0; outputIndex < outputDimension; ++ outputIndex )
  {
    Scalar quadraticResidual = 0.;
    for ( UnsignedInteger i = 0; i < size; ++ i )
    {
      const Scalar slack = outputSample_[i][outputIndex] - mY[i][outputIndex];
      quadraticResidual += slack * slack;
    }
    residuals[outputIndex] = sqrt( quadraticResidual ) / size;
    const Scalar empiricalError = quadraticResidual / size;
    relativeErrors[outputIndex] = empiricalError / outputVariance[outputIndex];
  }

  result_ = MetaModelResult(Function(), metaModel, residuals, relativeErrors);
}


OT::Sample LibSVMRegression::getInputSample() const
{
  return inputSample_;
}


OT::Sample LibSVMRegression::getOutputSample() const
{
  return outputSample_;
}


/* Method save() stores the object through the StorageManager */
void LibSVMRegression::save(Advocate & adv) const
{
  SVMRegressionImplementation::save(adv);
  adv.saveAttribute( "inputSample_", inputSample_ );
  adv.saveAttribute( "outputSample_", outputSample_ );
}


/* Method load() reloads the object from the StorageManager */
void LibSVMRegression::load(Advocate & adv)
{
  SVMRegressionImplementation::load(adv);
  adv.loadAttribute( "inputSample_", inputSample_ );
  adv.loadAttribute( "outputSample_", outputSample_ );
}


}
