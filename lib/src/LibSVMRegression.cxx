//                                               -*- C++ -*-
/**
 *  @brief Regression
 *
 *  Copyright 2014-2023 Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
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
#include <openturns/SpecFunc.hxx>

using namespace OT;


namespace OTSVM
{

static Factory<LibSVMRegression> RegisteredFactory_LibSVMRegression;


CLASSNAMEINIT(LibSVMRegression)

/* Default constructor */
LibSVMRegression::LibSVMRegression() : PersistentObject()
{
  //Nothing to do
}

/* Constructor with parameters */
LibSVMRegression::LibSVMRegression(const Sample & dataIn,
                                   const Sample & dataOut,
                                   const LibSVM::KernelType kerneltype )
  : PersistentObject()
  , tradeoffFactor_(1, 10.)
  , kernelParameter_(1, 1.0)
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

  if (outputSample_.getSize() != size)
    throw InvalidArgumentException(HERE) << "LibSVMRegression: the input sample and the output sample must have the same size";

  Scalar bestTradeoffFactor = tradeoffFactor_[0];
  Scalar bestKernelParameter = kernelParameter_[0];

  Sample isoProbSample( size, inputDimension );
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
  * Second, we train the problem and retrieve some results (support vectors, support vectors coefficients, kernel parameters).
  * Third, we build the model with OT and save results in the MetaModelResult */
  for (UnsignedInteger componentIndex = 0 ; componentIndex < outputDimension; ++ componentIndex)
  {
    driver_.convertData(inputSample_, normalizedOutputSample.getMarginal(componentIndex) );

    if (tradeoffFactor_.getSize() > 1 || kernelParameter_.getSize() > 1)
    {
      Scalar minerror = SpecFunc::MaxScalar;
      for (UnsignedInteger tradeoffIndex = 0 ; tradeoffIndex < tradeoffFactor_.getSize(); ++ tradeoffIndex)
      {
        driver_.setTradeoffFactor( tradeoffFactor_[tradeoffIndex] );
        for( UnsignedInteger kernelParameterIndex = 0 ; kernelParameterIndex < kernelParameter_.getSize() ; kernelParameterIndex ++)
        {
          driver_.setKernelParameter(kernelParameter_[kernelParameterIndex]);

          const Scalar totalerror = driver_.runCrossValidation();

          if (totalerror < minerror)
          {
            minerror = totalerror;
            bestTradeoffFactor = tradeoffFactor_[tradeoffIndex];
            bestKernelParameter = kernelParameter_[kernelParameterIndex];
          }
          LOGINFO( OSS() << "Cross Validation for C=" << tradeoffFactor_[tradeoffIndex] << " and gamma=" << kernelParameter_[kernelParameterIndex] << " error=" << totalerror );
        }
      }
    }
    driver_.setTradeoffFactor(bestTradeoffFactor);
    driver_.setKernelParameter(bestKernelParameter);
    driver_.performTrain();

    Point svcoef(driver_.getSupportVectorCoef());

    Sample supportvector( driver_.getNumberSupportVector(), inputDimension );
    supportvector = driver_.getSupportVector( inputDimension );

    const SVMKernel kernel(driver_.getKernel());

    Function function;
    function.setEvaluation(new SVMKernelRegressionEvaluation(kernel, svcoef, supportvector, driver_.getConstant()));
    function.setGradient(new SVMKernelRegressionGradient(kernel, svcoef, supportvector, driver_.getConstant()));
    function.setHessian(new SVMKernelRegressionHessian(kernel, svcoef, supportvector, driver_.getConstant()));

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

  for (UnsignedInteger outputIndex = 0; outputIndex < outputDimension; ++ outputIndex)
  {
    Scalar quadraticResidual = 0.;
    for (UnsignedInteger i = 0; i < size; ++ i)
    {
      const Scalar slack = outputSample_[i][outputIndex] - mY[i][outputIndex];
      quadraticResidual += slack * slack;
    }
    residuals[outputIndex] = sqrt( quadraticResidual ) / size;
    const Scalar empiricalError = quadraticResidual / size;
    relativeErrors[outputIndex] = empiricalError / outputVariance[outputIndex];
  }

  result_ = MetaModelResult(inputSample_, outputSample_, metaModel, residuals, relativeErrors);
}


OT::Sample LibSVMRegression::getInputSample() const
{
  return inputSample_;
}


OT::Sample LibSVMRegression::getOutputSample() const
{
  return outputSample_;
}

/* Tradeoff factor accessor */
void LibSVMRegression::setTradeoffFactor(const Point & tradeoffFactor)
{
  tradeoffFactor_ = tradeoffFactor;
}

Point LibSVMRegression::getTradeoffFactor()
{
  return tradeoffFactor_;
}

/* Kernel parameter accessor */
void LibSVMRegression::setKernelParameter(const Point & kernelParameter)
{
  kernelParameter_ = kernelParameter;
}

Point LibSVMRegression::getKernelParameter()
{
  return kernelParameter_;
}

/* Results accessor */
MetaModelResult LibSVMRegression::getResult() const
{
  return result_;
}

/* Method save() stores the object through the StorageManager */
void LibSVMRegression::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute( "tradeoffFactor_", tradeoffFactor_ );
  adv.saveAttribute( "kernelParameter_", kernelParameter_ );
  adv.saveAttribute( "result_", result_ );
  adv.saveAttribute( "inputSample_", inputSample_ );
  adv.saveAttribute( "outputSample_", outputSample_ );
}


/* Method load() reloads the object from the StorageManager */
void LibSVMRegression::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute( "tradeoffFactor_", tradeoffFactor_ );
  adv.loadAttribute( "kernelParameter_", kernelParameter_ );
  adv.loadAttribute( "result_", result_ );
  adv.loadAttribute( "inputSample_", inputSample_ );
  adv.loadAttribute( "outputSample_", outputSample_ );
}


}
