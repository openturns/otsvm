//                                               -*- C++ -*-
/**
 * @file  SVMKernelRegressionEvaluation.cxx
 * @brief Implementation of evaluation using support vector machines
 *
 *  (C) Copyright 2005-2012 EDF-EADS-Phimeca
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
 *  @author schueller
 *  @date   2008-05-05 08:50:15 +0200 (lun, 05 mai 2008)
 *  Id      SVMKernelRegressionEvaluation.cxx 805 2008-05-05 06:50:15Z schueller
 */

#include "SVMKernelRegressionEvaluation.hxx"
#include "PersistentObjectFactory.hxx"

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(SVMKernelRegressionEvaluation);

static Factory<SVMKernelRegressionEvaluation> RegisteredFactory;

/* Default constructor */
SVMKernelRegressionEvaluation::SVMKernelRegressionEvaluation() :
  NumericalMathEvaluationImplementation()
{
  // nothing to do
}

/* Constructor with parameters */
SVMKernelRegressionEvaluation::SVMKernelRegressionEvaluation(const SVMKernel & kernel,
    const NumericalPoint & lagrangeMultiplier,
    const NumericalSample & dataIn,
    const NumericalScalar constant) :
  kernel_(kernel),
  lagrangeMultiplier_(lagrangeMultiplier),
  dataIn_(dataIn),
  constant_(constant)
{
  Description description;
  for (UnsignedInteger i = 0; i < getInputDimension(); ++i)
  {
    OSS oss;
    oss << "x" << i;
    description.add(oss);
  }
  for (UnsignedInteger i = 0; i < getOutputDimension(); ++i)
  {
    OSS oss;
    oss << "y" << i;
    description.add(oss);
  }
  setDescription(description);
}

/* Virtual constructor */
SVMKernelRegressionEvaluation * SVMKernelRegressionEvaluation::clone() const
{
  return new SVMKernelRegressionEvaluation(*this);
}

/* Comparison operator */
Bool SVMKernelRegressionEvaluation::operator==(const SVMKernelRegressionEvaluation & other) const
{
  return true;
}

/* String converter */
String SVMKernelRegressionEvaluation::__repr__() const
{
  OSS oss;
  oss << "class=" << SVMKernelRegressionEvaluation::GetClassName()
      << " kernel=" << kernel_
      << " lagrange multipliers=" << lagrangeMultiplier_
      << " data in=" << dataIn_
      << " constant=" << constant_;

  return oss;
}

/* Test for actual implementation */
Bool SVMKernelRegressionEvaluation::isActualImplementation() const
{
  return true;
}

/* Operator () */
NumericalPoint SVMKernelRegressionEvaluation::operator() (const NumericalPoint & inP) const
{
  ++callsNumber_;

  const UnsignedInteger dimension(inP.getDimension());
  if (dimension != dataIn_.getDimension())
    throw InvalidArgumentException(HERE) << "Invalid input dimension";

  // compute the sum of the kernel evaluation over the data
  NumericalScalar output(constant_);
  UnsignedInteger size(dataIn_.getSize());
  for (UnsignedInteger i = 0; i < size; ++ i)
  {
    if (lagrangeMultiplier_[i] != 0.0)
      output += lagrangeMultiplier_[i] * kernel_(dataIn_[i], inP);
  }
  const NumericalPoint result(1, output);
  if (isHistoryEnabled_)
  {
    inputStrategy_.store(inP);
    outputStrategy_.store(result);
  }
  return NumericalPoint(1, output);
}

/* Accessor for input point dimension */
UnsignedInteger SVMKernelRegressionEvaluation::getInputDimension() const
{
  return dataIn_.getDimension();
}

/* Accessor for output point dimension */
UnsignedInteger SVMKernelRegressionEvaluation::getOutputDimension() const
{
  return 1;
}

/* Method save() stores the object through the StorageManager */
void SVMKernelRegressionEvaluation::save(Advocate & adv) const
{
  NumericalMathEvaluationImplementation::save(adv);
  adv.saveAttribute("kernel_", kernel_);
  adv.saveAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.saveAttribute("dataIn_", dataIn_);
  adv.saveAttribute("constant_", constant_);
}

/* Method load() reloads the object from the StorageManager */
void SVMKernelRegressionEvaluation::load(Advocate & adv)
{
  NumericalMathEvaluationImplementation::load(adv);
  adv.loadAttribute("kernel_", kernel_);
  adv.loadAttribute("lagrangeMultiplier_", lagrangeMultiplier_);
  adv.loadAttribute("dataIn_", dataIn_);
  adv.loadAttribute("constant_", constant_);
}


}
