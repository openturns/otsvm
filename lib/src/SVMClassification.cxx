/**
 *  @brief
 *  This is the class which makes the link between LibSVM and OpenTURNS for Classification.
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

#include "otsvm/SVMClassification.hxx"
#include "otsvm/NormalRBF.hxx"
#include "otsvm/PolynomialKernel.hxx"
#include "otsvm/SVMKernelRegressionEvaluation.hxx"
#include "otsvm/SigmoidKernel.hxx"
#include "otsvm/LinearKernel.hxx"
#include "otsvm/KMeansClustering.hxx"
#include <openturns/PersistentObjectFactory.hxx>
#include <openturns/ComposedFunction.hxx>
#include <openturns/SpecFunc.hxx>

using namespace OT;


namespace OTSVM
{



CLASSNAMEINIT(SVMClassification)


static Factory<SVMClassification> RegisteredFactory_SVMClassification;


SVMClassification::SVMClassification()
  : ClassifierImplementation()
  , accuracy_(0.)
  , tradeoffFactor_(1, 10.)
  , kernelParameter_(1, 1.0)
{
  // Nothing to do
}


SVMClassification* SVMClassification::clone() const
{
  return new SVMClassification(*this);
}


SVMClassification::SVMClassification(const Sample & dataIn,
    const Indices & outClasses)
  : ClassifierImplementation(dataIn, outClasses)
//   inputSample_(dataIn),
{
  driver_.setSvmType(LibSVM::CSupportClassification);
  driver_.setNu(0.);
}

Scalar SVMClassification::getAccuracy()
{
  return accuracy_;
}

/** String converter */
String SVMClassification::__repr__() const
{
  return OSS()  << "class=" << getClassName()
         << "accuracy=" << accuracy_;
}

void SVMClassification::run()
{
  const UnsignedInteger size = inputSample_.getSize();

  Scalar bestTradeoffFactor = tradeoffFactor_[0];
  Scalar bestKernelParameter = kernelParameter_[0];

  if (classes_.getSize() != size)
    throw InvalidArgumentException(HERE) << "SVMClassification: the input sample and the output sample must have the same size";

  Sample outputSample(inputSample_.getSize(), 1);
  for (UnsignedInteger i = 0; i < classes_.getSize(); ++ i)
    outputSample[i][0] = classes_[i];
  driver_.convertData(inputSample_, outputSample);

  if (tradeoffFactor_.getSize() > 1 || kernelParameter_.getSize() > 1)
  {
    Scalar minerror = SpecFunc::MaxScalar;
    for (UnsignedInteger tradeoffIndex = 0 ; tradeoffIndex < tradeoffFactor_.getSize(); ++ tradeoffIndex)
    {
      driver_.setTradeoffFactor(tradeoffFactor_[tradeoffIndex]);
      for (UnsignedInteger kernelParameterIndex = 0 ; kernelParameterIndex < kernelParameter_.getSize(); ++ kernelParameterIndex)
      {
        driver_.setKernelParameter(kernelParameter_[kernelParameterIndex]);
        const Scalar totalerror = driver_.runCrossValidation();
        if (totalerror < minerror)
        {
          minerror = totalerror;
          bestTradeoffFactor = tradeoffFactor_[tradeoffIndex];
          bestKernelParameter = kernelParameter_[kernelParameterIndex];
        }
        LOGINFO( OSS() << "Cross Validation for C=" << tradeoffFactor_[tradeoffIndex] << " gamma=" << kernelParameter_[kernelParameterIndex] << " error=" << totalerror );
      }
    }
  }

  driver_.setTradeoffFactor(bestTradeoffFactor);
  driver_.setKernelParameter(bestKernelParameter);
  driver_.performTrain();

  Scalar totalerror = driver_.computeAccuracy();
  accuracy_ = (1.0 - (totalerror / size)) * 100.0;
}


UnsignedInteger SVMClassification::classify(const Point & vector) const
{
  return driver_.getLabel(vector);
}


void SVMClassification::setKernelType(const LibSVM::KernelType & kerneltype)
{
  driver_.setKernelType(kerneltype);
}

void SVMClassification::setTradeoffFactor(const Point & tradeoffFactor)
{
  if (!tradeoffFactor.getSize())
    throw InvalidArgumentException(HERE) << "SVMClassification: tradeoff factor should be of size>=1";
  tradeoffFactor_ = tradeoffFactor;
}

void SVMClassification::setKernelParameter(const Point & kernelParameter)
{
  if (!kernelParameter.getSize())
    throw InvalidArgumentException(HERE) << "SVMClassification: kernel parameter should be of size>=1";
  kernelParameter_ = kernelParameter;
}

/* Grade a point as if it were associated to a class */
Scalar SVMClassification::grade(const Point & inP, const UnsignedInteger outC) const
{
  return driver_.getLabelValues(inP, outC);
}

OT::Scalar SVMClassification::predict(const OT::Point& inP) const
{
  return driver_.predict(inP);
}

void SVMClassification::setWeight(const Point & weight)
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

void SVMClassification::runKMeans(const UnsignedInteger k)
{
  Scalar error = 0;
  Indices cluster;
  Sample finalSample(0, inputSample_[0].getDimension());
  Indices finalIndices;
  Indices tempIndices;
  KMeansClustering kmeans(inputSample_, k);
  kmeans.run();

  cluster = kmeans.getCluster();

  for (UnsignedInteger i = 0 ; i < k ; ++ i)
  {
    Indices partialIndices;
    Sample partialSample(0, inputSample_[0].getDimension());
    for (UnsignedInteger j = 0; j < cluster.getSize(); ++ j)
    {
      if (cluster[j] == i)
      {
        partialSample.add(inputSample_[j]);
        partialIndices.add(classes_[j]);
        tempIndices.add(classes_[j]);
      }
    }
    SVMClassification partial(partialSample, partialIndices);
    partial.setKernelType(driver_.getKernelType());
    partial.setTradeoffFactor(tradeoffFactor_);
    partial.setKernelParameter(kernelParameter_);
    partial.run();
    finalSample.add(partialSample);
    for (UnsignedInteger j = 0; j < partialSample.getSize(); ++ j)
      finalIndices.add(partial.classify(partialSample[j]));
  }

  inputSample_ = finalSample;
  classes_ = finalIndices;

  for (UnsignedInteger i = 0; i < inputSample_.getSize(); ++ i)
    if (tempIndices[i] == finalIndices[i])
      error += 1.0;

  accuracy_ = (error / finalSample.getSize()) * 100;
}


void SVMClassification::save(Advocate & adv) const
{
  ClassifierImplementation::save(adv);
  adv.saveAttribute( "tradeoffFactor_", tradeoffFactor_ );
  adv.saveAttribute( "kernelParameter_", kernelParameter_ );
  adv.saveAttribute( "accuracy_", accuracy_ );
}


/* Method load() reloads the object from the StorageManager */
void SVMClassification::load(Advocate & adv)
{
  ClassifierImplementation::load(adv);
  adv.saveAttribute( "tradeoffFactor_", tradeoffFactor_ );
  adv.saveAttribute( "kernelParameter_", kernelParameter_ );
  adv.saveAttribute( "accuracy_", accuracy_ );
}


}

