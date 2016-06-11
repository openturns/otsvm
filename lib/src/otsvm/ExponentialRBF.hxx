//                                               -*- C++ -*-
/**
 *  @file  ExponentialRBF.hxx
 *  @brief Implementation of the Exponential RBF kernel
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
  CLASSNAME;
public:


  /** Constructor with parameters */
  ExponentialRBF(const OT::NumericalScalar sigma = 1.0);

  /** Virtual constructor */
  virtual ExponentialRBF * clone() const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Sigma parameter accessor */
  virtual OT::NumericalScalar getSigma() const;
  virtual void setSigma(OT::NumericalScalar sigma);

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
  OT::NumericalScalar sigma_;

private:

} ; /* class ExponentialRBF */


}

#endif