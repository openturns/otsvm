//                                               -*- C++ -*-
/**
 *  @brief Implementation of SVM regression gradient
 *
 *  Copyright 2014-2024 Phimeca
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

#include "otsvm/SVMKernelRegressionGradient.hxx"
#include <openturns/PersistentObjectFactory.hxx>

using namespace OT;

namespace OTSVM
{

CLASSNAMEINIT(SVMKernelRegressionGradient)
static Factory<SVMKernelRegressionGradient> Factory_SVMKernelRegressionGradient;


/* Default constructor */
SVMKernelRegressionGradient::SVMKernelRegressionGradient()
: GradientImplementation()
{
  // Nothing to do
}


/* Constructor with parameters */
SVMKernelRegressionGradient::SVMKernelRegressionGradient(const SVMKernel & kernel,
    const Point & lagrangeMultiplier,
    const Sample & dataIn,
    const Scalar constant)
: GradientImplementation()
, kernel_(kernel)
, lagrangeMultiplier_(lagrangeMultiplier)
, dataIn_(dataIn)
, constant_(constant)
{
  // Nothing to do
}


/* Virtual constructor */
SVMKernelRegressionGradient * SVMKernelRegressionGradient::clone() const
{
  return new SVMKernelRegressionGradient(*this);
}

/* Comparison operator */
Bool SVMKernelRegressionGradient::operator==(const SVMKernelRegressionGradient & other) const
{
  if (this == &other) return true;
  return (kernel_ == other.kernel_) && (lagrangeMultiplier_ == other.lagrangeMultiplier_) && (constant_ == other.constant_) && (dataIn_ == other.dataIn_);
}

/* String converter */
String SVMKernelRegressionGradient::__repr__() const
{
  OSS oss;
  oss << "class=" << SVMKernelRegressionGradient::GetClassName()
      << " kernel=" << kernel_
      << " lagrange multipliers=" << lagrangeMultiplier_
      << " data in=" << dataIn_
      << " constant=" << constant_;
  return oss;
}

/* Gradient method */
Matrix SVMKernelRegressionGradient::gradient(const Point & inP) const
{
  callsNumber_.increment();

  const UnsignedInteger dimension = inP.getDimension();
  if(dimension != dataIn_.getDimension())
    throw InvalidArgumentException(HERE) << "Invalid input dimension";

  // compute the sum of the partial gradients
  const UnsignedInteger size = dataIn_.getSize();
  Point partialGradient(dimension, 0.0);
  for(UnsignedInteger i = 0; i < size; ++ i)
  {
    if(lagrangeMultiplier_[i] != 0.0)
      partialGradient += lagrangeMultiplier_[i] * kernel_.partialGradient(inP, dataIn_[i]);
  }

  // return the gradient into a column Matrix
  Matrix result(dimension, 1);
  for(UnsignedInteger i = 0; i < dimension; ++ i)
  {
    result(i, 0) = partialGradient[i];
  }
  return result;
}

/* Accessor for input point dimension */
UnsignedInteger SVMKernelRegressionGradient::getInputDimension() const
{
  return dataIn_.getDimension();
}

/* Accessor for output point dimension */
UnsignedInteger SVMKernelRegressionGradient::getOutputDimension() const
{
  return 1;
}

/* Method save() stores the object through the StorageManager */
void SVMKernelRegressionGradient::save(Advocate & adv) const
{
  GradientImplementation::save(adv);
  adv.saveAttribute("kernel_", kernel_);
  adv.saveAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.saveAttribute("dataIn_", dataIn_);
  adv.saveAttribute("constant_", constant_);
}

/* Method load() reloads the object from the StorageManager */
void SVMKernelRegressionGradient::load(Advocate & adv)
{
  GradientImplementation::load(adv);
  adv.loadAttribute("kernel_", kernel_);
  adv.loadAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.loadAttribute("dataIn_", dataIn_);
  adv.loadAttribute("constant_", constant_);
}


}
