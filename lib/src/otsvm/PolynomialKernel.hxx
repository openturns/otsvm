//                                               -*- C++ -*-
/**
 *  @brief Implementation of the polynomial kernel
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
 */
#ifndef OTSVM_POLYNOMIALKERNEL_HXX
#define OTSVM_POLYNOMIALKERNEL_HXX

#include "SVMKernelImplementation.hxx"

namespace OTSVM
{

/**
 * @class PolynomialKernel
 *
 * Implementation of the polynomial kernel
 */
class OTSVM_API PolynomialKernel
  : public SVMKernelImplementation
{
  CLASSNAME
public:


  /** Constructor with parameters */
  PolynomialKernel(const OT::Scalar degree = 3.0, const OT::Scalar linear = 1.0, const OT::Scalar constant = 0.0);

  /** Virtual constructor */
  PolynomialKernel * clone() const override;

  /** String converter */
  OT::String __repr__() const override;

  /** Degree accessor */
  virtual OT::Scalar getDegree() const;
  virtual void setDegree(OT::Scalar degree);

  /** Linear term accessor */
  virtual OT::Scalar getLinear() const;
  virtual void setLinear(OT::Scalar linear);

  /** Constant term accessor */
  virtual OT::Scalar getConstant() const;
  virtual void setConstant(OT::Scalar constant);

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
  OT::Scalar degree_ = 0.0;
  OT::Scalar linear_ = 0.0;
  OT::Scalar constant_ = 0.0;
private:

} ; /* class PolynomialKernel */


}

#endif
