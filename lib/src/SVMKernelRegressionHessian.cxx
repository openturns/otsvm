//                                               -*- C++ -*-
/**
 * @brief Implementation of SVM regression hessian
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

#include "otsvm/SVMKernelRegressionHessian.hxx"
#include <openturns/PersistentObjectFactory.hxx>

using namespace OT;

namespace OTSVM
{

CLASSNAMEINIT(SVMKernelRegressionHessian)

static Factory<SVMKernelRegressionHessian> Factory_SVMKernelRegressionHessian;

/* Default constructor */
SVMKernelRegressionHessian::SVMKernelRegressionHessian()
: HessianImplementation()
{
  // Nothing to do
}


/* Constructor with parameters */
SVMKernelRegressionHessian::SVMKernelRegressionHessian(const SVMKernel & kernel,
    const Point & lagrangeMultiplier,
    const Sample & dataIn,
    const Scalar constant)
: HessianImplementation()
, kernel_(kernel)
, lagrangeMultiplier_(lagrangeMultiplier)
, dataIn_(dataIn)
, constant_(constant)
{
  // Nothing to do
}

/* Virtual constructor */
SVMKernelRegressionHessian * SVMKernelRegressionHessian::clone() const
{
  return new SVMKernelRegressionHessian(*this);
}

/* Comparison operator */
Bool SVMKernelRegressionHessian::operator==(const SVMKernelRegressionHessian & other) const
{
  if (this == &other) return true;
  return (kernel_ == other.kernel_) && (lagrangeMultiplier_ == other.lagrangeMultiplier_) && (constant_ == other.constant_) && (dataIn_ == other.dataIn_);
}

/* String converter */
String SVMKernelRegressionHessian::__repr__() const
{
  OSS oss;
  oss << "class=" << SVMKernelRegressionHessian::GetClassName()
      << " kernel=" << kernel_
      << " lagrange multipliers=" << lagrangeMultiplier_
      << " data in=" << dataIn_
      << " constant=" << constant_;
  return oss;
}

/* Hessian method */
SymmetricTensor SVMKernelRegressionHessian::hessian(const Point & inP) const
{
  callsNumber_.increment();

  const UnsignedInteger dimension = inP.getDimension();
  if(dimension != dataIn_.getDimension())
    throw InvalidArgumentException(HERE) << "Invalid input dimension=" << dimension;

  // compute the sum of the partial Hessians
  const UnsignedInteger size = dataIn_.getSize();
  SymmetricMatrix partialHessian(dimension);
  for (UnsignedInteger i = 0; i < size; ++ i)
    if (lagrangeMultiplier_[i] != 0.0)
      partialHessian = partialHessian + lagrangeMultiplier_[i] * kernel_.partialHessian(inP, dataIn_[i]);

  // return the result into a symmetric tensor
  SymmetricTensor result(dimension, 1);
  for(UnsignedInteger i = 0; i < dimension; ++ i)
    for(UnsignedInteger j = 0; j <= i; ++ j)
      result(i, j, 0) = partialHessian(i, j);

  return result;
}

/* Accessor for input point dimension */
UnsignedInteger SVMKernelRegressionHessian::getInputDimension() const
{
  return dataIn_.getDimension();
}

/* Accessor for output point dimension */
UnsignedInteger SVMKernelRegressionHessian::getOutputDimension() const
{
  return 1;
}

/* Method save() stores the object through the StorageManager */
void SVMKernelRegressionHessian::save(Advocate & adv) const
{
  HessianImplementation::save(adv);
  adv.saveAttribute("kernel_", kernel_);
  adv.saveAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.saveAttribute("dataIn_", dataIn_);
  adv.saveAttribute("constant_", constant_);
}

/* Method load() reloads the object from the StorageManager */
void SVMKernelRegressionHessian::load(Advocate & adv)
{
  HessianImplementation::load(adv);
  adv.loadAttribute("kernel_", kernel_);
  adv.loadAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.loadAttribute("dataIn_", dataIn_);
  adv.loadAttribute("constant_", constant_);
}


}
