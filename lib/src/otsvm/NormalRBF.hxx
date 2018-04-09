//                                               -*- C++ -*-
/**
 *  @file  NormalRBF.hxx
 *  @brief Implementation of the Normal RBF kernel, also known as the gaussian kernel
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
#ifndef OTSVM_NORMALRBF_HXX
#define OTSVM_NORMALRBF_HXX

#include "SVMKernelImplementation.hxx"

namespace OTSVM
{

/**
 * @class NormalRBF
 *
 * Implementation of the Normal RBF kernel, also known as the gaussian kernel
 */
class OTSVM_API NormalRBF
  : public SVMKernelImplementation
{
  CLASSNAME
public:


  /** Constructor with parameters */
  explicit NormalRBF(const OT::Scalar sigma = 1.0);

  /** Virtual constructor */
  virtual NormalRBF * clone() const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Sigma parameter accessor */
  virtual OT::Scalar getSigma() const;
  virtual void setSigma(OT::Scalar sigma);

  /** Accessor to the parameter used for cross-validation */
  virtual OT::Scalar getParameter() const;
  virtual void setParameter(OT::Scalar value);

  /** Parameters value and description accessor */
  virtual OT::PointWithDescription getParameters() const;
  virtual void setParameters(const OT::PointWithDescription & parameters);

  /** Operator () */
  virtual OT::Scalar operator() (const OT::Point & x1, const OT::Point & x2) const;

  /** Partial gradient */
  virtual OT::Point partialGradient(const OT::Point & x1, const OT::Point & x2) const;

  /** Partial hessian */
  virtual OT::SymmetricMatrix partialHessian(const OT::Point & x1, const OT::Point & x2) const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);


protected:
  OT::Scalar sigma_;

private:

} ; /* class NormalRBF */


}

#endif
