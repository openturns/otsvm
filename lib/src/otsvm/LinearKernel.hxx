//                                               -*- C++ -*-
/**
 *  @brief Implementation of the rational kernel
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

#ifndef OTSVM_LINEARKERNEL_HXX
#define OTSVM_LINEARKERNEL_HXX

#include "SVMKernelImplementation.hxx"

namespace OTSVM
{

class OTSVM_API LinearKernel : public SVMKernelImplementation
{
  CLASSNAME

public:

  /* Constructor */
  LinearKernel();

  /* Virtual constructor */
  LinearKernel * clone() const override;

  /* String converter */
  OT::String __repr__() const override;

  /** Accessor to the parameter used for cross-validation */
  OT::Point getParameter() const override;
  void setParameter(const OT::Point & parameter) override;
  OT::Description getParameterDescription() const override;

  /* Operator () */
  OT::Scalar operator() ( const OT::Point & x1, const OT::Point & x2 ) const override;

  /* Partial gradient */
  OT::Point partialGradient( const OT::Point & x1, const OT::Point & x2 ) const override;

  /* Partial hessian */
  OT::SymmetricMatrix partialHessian( const OT::Point & x1, const OT::Point & x2 ) const override;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;
};

}

#endif

