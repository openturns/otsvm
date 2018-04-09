//                                               -*- C++ -*-
/**
 * @file  SVMKernelRegressionGradient.hxx
 * @brief Implementation of SVM regression gradient
 *
 *  Copyright 2005-2018 EDF-EADS-Phimeca
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

#ifndef OTSVM_SVMKERNELREGRESSIONGRADIENT_HXX
#define OTSVM_SVMKERNELREGRESSIONGRADIENT_HXX

#include "SVMKernel.hxx"
#include <openturns/GradientImplementation.hxx>
#include "SVMKernelRegressionEvaluation.hxx"
#include <openturns/Sample.hxx>


namespace OTSVM
{

class SVMKernelRegressionEvaluation;

/**
 * @class SVMKernelRegressionGradient
 *
 * Implementation of SVM regression gradient
 */

class OTSVM_API SVMKernelRegressionGradient
  : public OT::GradientImplementation
{
  CLASSNAME
public:

  typedef OT::Pointer<SVMKernelRegressionEvaluation> SVMEvaluation;

  /** Default constructor */
  SVMKernelRegressionGradient();

  /** Constructor with parameters */
  SVMKernelRegressionGradient(const SVMKernel & kernel,
                              const OT::Point & lagrangeMultiplier,
                              const OT::Sample & dataIn,
                              const OT::Scalar constant);

  /** Virtual constructor */
  virtual SVMKernelRegressionGradient * clone() const;

  /** Comparison operator */
  OT::Bool operator ==(const SVMKernelRegressionGradient & other) const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Test for actual implementation */
  virtual OT::Bool isActualImplementation() const;

  /** Gradient method */
  virtual OT::Matrix gradient(const OT::Point & inP) const;

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
  OT::Point lagrangeMultiplier_;
  OT::Sample dataIn_;
  OT::Scalar constant_;

}; /* class SVMKernelRegressionGradient */


}

#endif /* OTSVM_SVMKERNELREGRESSIONGRADIENT_HXX */
