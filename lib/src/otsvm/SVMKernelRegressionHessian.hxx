//                                               -*- C++ -*-
/**
 * @file  SVMKernelRegressionHessian.hxx
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

#ifndef OTSVM_SVMKERNELREGRESSIONHESSIAN_HXX
#define OTSVM_SVMKERNELREGRESSIONHESSIAN_HXX

#include "SVMKernel.hxx"
#include <openturns/NumericalMathHessianImplementation.hxx>
#include "SVMKernelRegressionEvaluation.hxx"
#include <openturns/NumericalSample.hxx>


namespace OTSVM
{

class SVMKernelRegressionEvaluation;

/**
 * @class SVMKernelRegressionHessian
 *
 * Implementation of SVM regression hessian
 */

class OTSVM_API SVMKernelRegressionHessian
  : public OT::NumericalMathHessianImplementation
{
  CLASSNAME;
public:


  /** Default constructor */
  SVMKernelRegressionHessian();

  /** Constructor with parameters */
  SVMKernelRegressionHessian(const SVMKernel & kernel,
                             const OT::NumericalPoint & lagrangeMultiplier,
                             const OT::NumericalSample & dataIn,
                             const OT::NumericalScalar constant);

  /** Constructor from SVMKernelRegressionEvaluation */
  SVMKernelRegressionHessian(const SVMKernelRegressionEvaluation & evaluation);

  /** Virtual constructor */
  virtual SVMKernelRegressionHessian * clone() const;

  /** Comparison operator */
  OT::Bool operator ==(const SVMKernelRegressionHessian & other) const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Test for actual implementation */
  virtual OT::Bool isActualImplementation() const;

  /** Hessian method */
  virtual OT::SymmetricTensor hessian(const OT::NumericalPoint & inP) const;

  /** Accessor for input point dimension */
  virtual OT::UnsignedInteger getInputDimension() const;

  /** Accessor for output point dimension */
  virtual OT::UnsignedInteger getOutputDimension() const;
  
  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);
private:

protected:
  SVMKernel kernel_;
  OT::NumericalPoint lagrangeMultiplier_;
  OT::NumericalSample dataIn_;
  OT::NumericalScalar constant_;

}; /* class SVMKernelRegressionHessian */


}

#endif /* OTSVM_SVMKERNELREGRESSIONHESSIAN_HXX */
