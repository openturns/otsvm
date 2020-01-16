/**
 *  @brief
 *  This is the class which makes the link between LibSVM and OpenTURNS for Classification.
 *
 *  Copyright 2014-2020 Phimeca
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

#include "otsvm/LibSVMClassification.hxx"
#include "otsvm/NormalRBF.hxx"
#include "otsvm/PolynomialKernel.hxx"
#include "otsvm/SVMKernelRegressionEvaluation.hxx"
#include "otsvm/SigmoidKernel.hxx"
#include "otsvm/LinearKernel.hxx"
#include "otsvm/KMeansClustering.hxx"
#include <openturns/PersistentObjectFactory.hxx>
#include <openturns/ComposedFunction.hxx>


using namespace OT;


namespace OTSVM
{



CLASSNAMEINIT(LibSVMClassification)


static Factory<LibSVMClassification> RegisteredFactory_LibSVMClassification;


LibSVMClassification::LibSVMClassification()
  : PersistentObject()
  , accuracy_(0.)
{
  ///Nothing to do
}


LibSVMClassification* LibSVMClassification::clone() const
{
  return new LibSVMClassification(*this);
}


LibSVMClassification::LibSVMClassification(const Sample & dataIn,
    const Indices & outClasses):
  PersistentObject(),
  inputSample_(dataIn),
  classes_(outClasses.getSize())
{
  for (UnsignedInteger i = 0; i < outClasses.getSize(); ++ i)
  {
    classes_[i] = outClasses[i];
  }

  driver_.setSvmType(LibSVM::CSupportClassification);
  driver_.setNu(0.);
}

LibSVMClassification::LibSVMClassification(const Sample & dataIn,
    const Collection<SignedInteger> & outClasses ):
  PersistentObject(),
  inputSample_(dataIn),
  classes_(outClasses)
{
  driver_.setSvmType(LibSVM::CSupportClassification);
  driver_.setNu(0.);
}



Scalar LibSVMClassification::getAccuracy()
{
  return accuracy_;
}

/** String converter */
String LibSVMClassification::__repr__() const
{
  return OSS()  << "class=" << getClassName()
         << "accuracy=" << accuracy_;
}

void LibSVMClassification::run()
{

  const UnsignedInteger sizeInput = inputSample_.getSize();
  const UnsignedInteger sizeOutput = classes_.getSize();

  UnsignedInteger tempTradeoff = 0;
  UnsignedInteger tempKernel = 0;

  Scalar totalerror = 0;
  Scalar minerror = 0;

  if(sizeOutput != sizeInput) throw InvalidArgumentException(HERE) << "Error: the input sample and the output sample must have the same size ";

  Sample outputSample(inputSample_.getSize(), 1);
  for (UnsignedInteger i = 0; i < classes_.getSize(); ++ i)
  {
    outputSample[i][0] = classes_[i];
  }
  driver_.convertData(inputSample_, outputSample);

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
        LOGINFO( OSS() << "Cross Validation for C=" << tradeoffFactor_[tradeoffIndex] << " gamma=" << kernelParameter_[kernelParameterIndex] << " error=" << totalerror );
      }
    }
  }

  driver_.setTradeoffFactor(tradeoffFactor_[tempTradeoff]);
  driver_.setKernelParameter(kernelParameter_[tempKernel]);

  driver_.performTrain();

  totalerror = driver_.computeAccuracy();

  accuracy_ = (1 - (totalerror / sizeInput)) * 100;
}


UnsignedInteger LibSVMClassification::classify(const Point & vector) const
{
  return driver_.getLabel(vector);
}


void LibSVMClassification::setKernelType(const LibSVM::KernelType & kerneltype)
{
  driver_.setKernelType(kerneltype);
}

void LibSVMClassification::setTradeoffFactor(const Point & trade)
{
  tradeoffFactor_ = trade;
}

void LibSVMClassification::setKernelParameter(const Point & kernel)
{
  kernelParameter_ = kernel;
}

/* Grade a point as if it were associated to a class */
UnsignedInteger LibSVMClassification::grade(const Point & inP, const  SignedInteger & outC) const
{
  return driver_.getLabelValues(inP, outC);
}

OT::Scalar LibSVMClassification::predict(const OT::Point& inP) const
{
  return driver_.predict(inP);
}

void LibSVMClassification::setWeight(const Point & weight)
{
  Point label(weight.getSize());
  UnsignedInteger j = 1;
  UnsignedInteger change = 0;

  for(UnsignedInteger i = 0 ; i < classes_.getSize() ; i++)
  {
    for(UnsignedInteger k = 0 ; k < j ; k++)
    {
      if( classes_[i] == label[k])
      {
        change = 1;
      }
    }
    if(change == 0)
    {
      label[j - 1] = classes_[i];
      j++;
    }
    change = 0;
  }
  LOGINFO( OSS() << "Labels found: " << label );
  driver_.setWeight(weight, label);
}

void LibSVMClassification::runKMeans( UnsignedInteger k )
{
  Scalar error = 0;
  Indices cluster;
  Sample finalSample(0, inputSample_[0].getDimension());
  Collection<SignedInteger> finalIndices;
  Collection<SignedInteger> tempIndices;
  KMeansClustering kmeans(inputSample_ , k);
  kmeans.run();

  cluster = kmeans.getCluster();

  for( UnsignedInteger i = 0 ; i < k ; i++)
  {
    Collection<SignedInteger> partialIndices;
    Sample partialSample(0, inputSample_[0].getDimension());
    for( UnsignedInteger j = 0 ; j < cluster.getSize() ; j++ )
    {
      if( cluster[j] == i )
      {
        partialSample.add(inputSample_[j]);
        partialIndices.add(classes_[j]);
        tempIndices.add(classes_[j]);
      }
    }
    LibSVMClassification partial(partialSample , partialIndices);
    partial.setKernelType(driver_.getKernelType());
    partial.setTradeoffFactor(tradeoffFactor_);
    partial.setKernelParameter(kernelParameter_);
    partial.run();
    finalSample.add(partialSample);
    for( UnsignedInteger j = 0 ; j < partialSample.getSize() ; j++ )
    {
      finalIndices.add(partial.classify(partialSample[j]));
    }
  }

  inputSample_ = finalSample;
  classes_ = finalIndices;

  for( UnsignedInteger i = 0 ; i < inputSample_.getSize() ; i++ )
  {
    if( tempIndices[i] == finalIndices[i] )
    {
      error ++;
    }
  }

  accuracy_ = (error / finalSample.getSize()) * 100;
}


// void LibSVMClassification::save(Advocate & adv) const
// {
//   Classifier::save(adv);
//   adv.saveAttribute( "inputSample_", inputSample_ );
//   adv.saveAttribute( "classes_", classes_ );
//   adv.saveAttribute( "tradeoffFactor_", tradeoffFactor_ );
//   adv.saveAttribute( "kernelParameter_", kernelParameter_ );
//   adv.saveAttribute( "accuracy_", accuracy_ );
// }


/* Method load() reloads the object from the StorageManager */
// void LibSVMClassification::load(Advocate & adv)
// {
//   Classifier::load(adv);
//   adv.saveAttribute( "inputSample_", inputSample_ );
//   adv.saveAttribute( "classes_", classes_ );
//   adv.saveAttribute( "tradeoffFactor_", tradeoffFactor_ );
//   adv.saveAttribute( "kernelParameter_", kernelParameter_ );
//   adv.saveAttribute( "accuracy_", accuracy_ );
// }


}

