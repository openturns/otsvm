//                                               -*- C++ -*-
/**
 *  @brief Implementation of SVM regression gradient
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

#include "otsvm/SVMKernelRegressionGradient.hxx"
#include <openturns/PersistentObjectFactory.hxx>

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(SVMKernelRegressionGradient)
static Factory<SVMKernelRegressionGradient> RegisteredFactory_SVMKernelRegressionGradient;


/* Default constructor */
SVMKernelRegressionGradient::SVMKernelRegressionGradient() :
  GradientImplementation()
{
  // nothing to do
}


/* Constructor with parameters */
SVMKernelRegressionGradient::SVMKernelRegressionGradient(const SVMKernel & kernel,
    const Point & lagrangeMultiplier,
    const Sample & dataIn,
    const Scalar constant) :
  kernel_(kernel),
  lagrangeMultiplier_(lagrangeMultiplier),
  dataIn_(dataIn),
  constant_(constant)
{
  // nothing to do
}


/* Virtual constructor */
SVMKernelRegressionGradient * SVMKernelRegressionGradient::clone() const
{
  return new SVMKernelRegressionGradient(*this);
}

/* Comparison operator */
Bool SVMKernelRegressionGradient::operator==(const SVMKernelRegressionGradient & /*other*/) const
{
  return true;
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

/* Test for actual implementation */
Bool SVMKernelRegressionGradient::isActualImplementation() const
{
  return true;
}

/* Gradient method */
Matrix SVMKernelRegressionGradient::gradient(const Point & inP) const
{
  callsNumber_.increment();

  UnsignedInteger dimension = inP.getDimension();
  if(dimension != dataIn_.getDimension())
    throw InvalidArgumentException(HERE) << "Invalid input dimension";

  // compute the sum of the partial gradients
  UnsignedInteger size = dataIn_.getSize();
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
