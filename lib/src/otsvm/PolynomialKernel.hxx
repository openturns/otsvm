//                                               -*- C++ -*-
/**
 *  @file  PolynomialKernel.hxx
 *  @brief Implementation of the polynomial kernel
 *
 *  (C) Copyright 2005-2015 EDF-EADS-Phimeca
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
  CLASSNAME;
public:


  /** Constructor with parameters */
  PolynomialKernel(const OT::NumericalScalar degree = 3.0, const OT::NumericalScalar linear = 1.0, const OT::NumericalScalar constant = 0.0);

  /** Virtual constructor */
  virtual PolynomialKernel * clone() const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Degree accessor */
  virtual OT::NumericalScalar getDegree() const;
  virtual void setDegree(OT::NumericalScalar degree);

  /** Linear term accessor */
  virtual OT::NumericalScalar getLinear() const;
  virtual void setLinear(OT::NumericalScalar linear);

  /** Constant term accessor */
  virtual OT::NumericalScalar getConstant() const;
  virtual void setConstant(OT::NumericalScalar constant);

  /** Accessor to the parameter used for cross-validation */
  virtual OT::NumericalScalar getParameter() const;
  virtual void setParameter(OT::NumericalScalar value);

  /** Parameters value and description accessor */
  virtual OT::NumericalPointWithDescription getParameters() const;
  virtual void setParameters(const OT::NumericalPointWithDescription & parameters);

  /** Operator () */
  virtual OT::NumericalScalar operator() (const OT::NumericalPoint & x1, const OT::NumericalPoint & x2) const;

  /** Partial gradient */
  virtual OT::NumericalPoint partialGradient(const OT::NumericalPoint & x1, const OT::NumericalPoint & x2) const;

  /** Partial hessian */
  virtual OT::SymmetricMatrix partialHessian(const OT::NumericalPoint & x1, const OT::NumericalPoint & x2) const;

    
  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv);
  
  
protected:
  OT::NumericalScalar degree_;
  OT::NumericalScalar linear_;
  OT::NumericalScalar constant_;
private:

} ; /* class PolynomialKernel */


}

#endif
