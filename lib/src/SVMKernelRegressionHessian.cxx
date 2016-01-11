//                                               -*- C++ -*-
/**
 * @file  SVMKernelRegressionHessian.cxx
 * @brief Implementation of SVM regression hessian
 *
 *  Copyright 2005-2015 EDF-EADS-Phimeca
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

#include "SVMKernelRegressionHessian.hxx"
#include "PersistentObjectFactory.hxx"

using namespace OT;

namespace OTSVM
{

CLASSNAMEINIT(SVMKernelRegressionHessian);

static Factory<SVMKernelRegressionHessian> RegisteredFactory;

/* Default constructor */
SVMKernelRegressionHessian::SVMKernelRegressionHessian() :
  NumericalMathHessianImplementation()
{
  // nothing to do
}


/* Constructor with parameters */
SVMKernelRegressionHessian::SVMKernelRegressionHessian(const SVMKernel & kernel,
    const NumericalPoint & lagrangeMultiplier,
    const NumericalSample & dataIn,
    const NumericalScalar constant) :
  kernel_(kernel),
  lagrangeMultiplier_(lagrangeMultiplier),
  dataIn_(dataIn),
  constant_(constant)
{
  // Nothing to do
}


/* Constructor from SVMKernelRegressionEvaluation */
SVMKernelRegressionHessian::SVMKernelRegressionHessian(const SVMKernelRegressionEvaluation & evaluation) :
  NumericalMathHessianImplementation()
  //  :
  //      kernel_(kernel),
  //      dataIn_(dataIn),
  //      constant_(constant)
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
  return true;
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

/* Test for actual implementation */
Bool SVMKernelRegressionHessian::isActualImplementation() const
{
  return true;
}

/* Hessian method */
SymmetricTensor SVMKernelRegressionHessian::hessian(const NumericalPoint & inP) const
{
  ++ callsNumber_;

  UnsignedInteger dimension = inP.getDimension();
  if(dimension != dataIn_.getDimension())
    throw InvalidArgumentException(HERE) << "Invalid input dimension=" << dimension;

  // compute the sum of the partial Hessians
  UnsignedInteger size = dataIn_.getSize();
  SymmetricMatrix partialHessian(dimension);
  for(UnsignedInteger i = 0; i < size; ++ i)
  {
    if(lagrangeMultiplier_[i] != 0.0)
      partialHessian = partialHessian + lagrangeMultiplier_[i] * kernel_.partialHessian(inP, dataIn_[i]);
  }

  // return the result into a symmetric tensor
  SymmetricTensor result(dimension, 1);
  for(UnsignedInteger i = 0; i < dimension; ++ i)
  {
    for(UnsignedInteger j = 0; j <= i; ++ j)
    {
      result(i, j, 0) = partialHessian(i, j);
    }
  }
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
  NumericalMathHessianImplementation::save(adv);
  adv.saveAttribute("kernel_", kernel_);
  adv.saveAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.saveAttribute("dataIn_", dataIn_);
  adv.saveAttribute("constant_", constant_);
}

/* Method load() reloads the object from the StorageManager */
void SVMKernelRegressionHessian::load(Advocate & adv)
{
  NumericalMathHessianImplementation::load(adv);
  adv.loadAttribute("kernel_", kernel_);
  adv.loadAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.loadAttribute("dataIn_", dataIn_);
  adv.loadAttribute("constant_", constant_);
}


}
