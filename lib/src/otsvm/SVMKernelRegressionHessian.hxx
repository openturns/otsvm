//                                               -*- C++ -*-
/**
 * @file  SVMKernelRegressionHessian.hxx
 * @brief Implementation of SVM regression hessian
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

#ifndef OTSVM_SVMKERNELREGRESSIONHESSIAN_HXX
#define OTSVM_SVMKERNELREGRESSIONHESSIAN_HXX

#include "SVMKernel.hxx"
#include <openturns/HessianImplementation.hxx>
#include "SVMKernelRegressionEvaluation.hxx"
#include <openturns/Sample.hxx>


namespace OTSVM
{

class SVMKernelRegressionEvaluation;

/**
 * @class SVMKernelRegressionHessian
 *
 * Implementation of SVM regression hessian
 */

class OTSVM_API SVMKernelRegressionHessian
  : public OT::HessianImplementation
{
  CLASSNAME
public:


  /** Default constructor */
  SVMKernelRegressionHessian();

  /** Constructor with parameters */
  SVMKernelRegressionHessian(const SVMKernel & kernel,
                             const OT::Point & lagrangeMultiplier,
                             const OT::Sample & dataIn,
                             const OT::Scalar constant);

  /** Virtual constructor */
  SVMKernelRegressionHessian * clone() const override;

  /** Comparison operator */
  OT::Bool operator ==(const SVMKernelRegressionHessian & other) const;

  /** String converter */
  OT::String __repr__() const override;

  /** Test for actual implementation */
  OT::Bool isActualImplementation() const override;

  /** Hessian method */
  OT::SymmetricTensor hessian(const OT::Point & inP) const override;

  /** Accessor for input point dimension */
  OT::UnsignedInteger getInputDimension() const override;

  /** Accessor for output point dimension */
  OT::UnsignedInteger getOutputDimension() const override;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;
private:

protected:
  SVMKernel kernel_;
  OT::Point lagrangeMultiplier_;
  OT::Sample dataIn_;
  OT::Scalar constant_;

}; /* class SVMKernelRegressionHessian */


}

#endif /* OTSVM_SVMKERNELREGRESSIONHESSIAN_HXX */
