//                                               -*- C++ -*-
/**
 * @brief Abstract top-level class for all numerical math function implementations
 *
 *  Copyright 2014-2023 Phimeca
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
 *  Id      SVMKernelRegressionEvaluation.hxx 805 2008-05-05 06:50:15Z schueller
 */

#ifndef OPENTURNS_SVMKERNELREGRESSIONEVALUATION_HXX
#define OPENTURNS_SVMKERNELREGRESSIONEVALUATION_HXX

#include "SVMKernel.hxx"
#include <openturns/EvaluationImplementation.hxx>
#include "SVMKernelRegressionGradient.hxx"
#include "SVMKernelRegressionHessian.hxx"

namespace OTSVM
{


/**
 * @class SVMKernelRegressionEvaluation
 *
 * This class permits prediction on a support vector machine
 */

class OTSVM_API SVMKernelRegressionEvaluation
  : public OT::EvaluationImplementation
{
  CLASSNAME

public:


  /** Default constructor */
  SVMKernelRegressionEvaluation();

  /** Constructor with parameters */
  SVMKernelRegressionEvaluation(const SVMKernel & kernel,
                                const OT::Point & lagrangeMultiplier,
                                const OT::Sample & dataIn,
                                const OT::Scalar constant);

  /** Virtual constructor */
  SVMKernelRegressionEvaluation * clone() const override;

  /** Comparison operator */
  OT::Bool operator ==(const SVMKernelRegressionEvaluation & other) const;

  /** String converter */
  OT::String __repr__() const override;

  /** Test for actual implementation */
  OT::Bool isActualImplementation() const override;

  /** Operator () */
  OT::Point operator() (const OT::Point & inP) const override;

  /** Accessor for input point dimension */
  OT::UnsignedInteger getInputDimension() const override;

  /** Accessor for output point dimension */
  OT::UnsignedInteger getOutputDimension() const override;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

private:

  friend class SVMKernelRegressionGradient;
  friend class SVMKernelRegressionHessian;

protected:
  SVMKernel kernel_;
  OT::Point lagrangeMultiplier_;
  OT::Sample dataIn_;
  OT::Scalar constant_;

}; /* class SVMKernelRegressionEvaluation */


}

#endif /* OPENTURNS_SVMKERNELREGRESSIONEVALUATION_HXX */
