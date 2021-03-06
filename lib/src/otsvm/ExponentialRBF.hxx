//                                               -*- C++ -*-
/**
 *  @file  ExponentialRBF.hxx
 *  @brief Implementation of the Exponential RBF kernel
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
#ifndef OTSVM_EXPONENTIALRBF_HXX
#define OTSVM_EXPONENTIALRBF_HXX

#include "SVMKernelImplementation.hxx"

namespace OTSVM
{



/**
 * @class ExponentialRBF
 *
 * Implementation of the Exponential RBF kernel
 */



class OTSVM_API ExponentialRBF
  : public SVMKernelImplementation
{
  CLASSNAME
public:


  /** Constructor with parameters */
  explicit ExponentialRBF(const OT::Scalar sigma = 1.0);

  /** Virtual constructor */
  ExponentialRBF * clone() const override;

  /** String converter */
  OT::String __repr__() const override;

  /** Sigma parameter accessor */
  virtual OT::Scalar getSigma() const;
  virtual void setSigma(OT::Scalar sigma);

  /** Accessor to the parameter used for cross-validation */
  OT::Scalar getParameter() const override;
  void setParameter(OT::Scalar value) override;

  /** Parameters value and description accessor */
  OT::PointWithDescription getParameters() const override;
  void setParameters(const OT::PointWithDescription & parameters) override;

  /** Operator () */
  OT::Scalar operator() (const OT::Point & x1, const OT::Point & x2) const override;

  /** Partial gradient */
  OT::Point partialGradient(const OT::Point & x1, const OT::Point & x2) const override;

  /** Partial hessian */
  OT::SymmetricMatrix partialHessian(const OT::Point & x1, const OT::Point & x2) const override;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

protected:
  OT::Scalar sigma_;

private:

} ; /* class ExponentialRBF */


}

#endif
