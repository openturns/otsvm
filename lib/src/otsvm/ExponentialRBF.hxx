//                                               -*- C++ -*-
/**
 *  @brief Implementation of the Exponential RBF kernel
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
  OT::Point getParameter() const override;
  void setParameter(const OT::Point & parameter) override;
  OT::Description getParameterDescription() const override;

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
  OT::Scalar sigma_ = 0.0;

private:

} ; /* class ExponentialRBF */


}

#endif
