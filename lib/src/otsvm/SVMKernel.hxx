//                                               -*- C++ -*-
/**
 *  @file  SVMKernel.hxx
 *  @brief
 *
 *  (C) Copyright 2005-2012 EDF-EADS-Phimeca
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
 *  @date   2008-07-03 14:14:36 +0200 (Thu, 03 Jul 2008)
 *  Id      SVMKernel.hxx 870 2008-07-03 12:14:36Z schueller
 */
#ifndef OPENTURNS_SVMKERNEL_HXX
#define OPENTURNS_SVMKERNEL_HXX

#include <openturns/TypedInterfaceObject.hxx>
#include "SVMKernelImplementation.hxx"

namespace OTSVM
{


/**
 * @class SVMKernel
 */

class OTSVM_API SVMKernel
  : public OT::TypedInterfaceObject<SVMKernelImplementation>
{

  CLASSNAME

public:

  typedef OT::Pointer<SVMKernelImplementation>          Implementation;

  /** Default constructor */
  SVMKernel();

  /** Constructor with parameters */
  SVMKernel(const SVMKernelImplementation & implementation);

  /** Constructor with parameters */
  SVMKernel(Implementation & p_implementation);

  /** String converter */
  OT::String __repr__() const;

  /** String converter */
  OT::String __str__(const OT::String & offset = "") const;

  /** Parameter accessor */
  OT::Scalar getParameter() const;
  void setParameter(OT::Scalar value);

  /** Parameters value and description accessor */
  OT::PointWithDescription getParameters() const;
  void setParameters(const OT::PointWithDescription & parameters);

  /** Operator () */
  OT::Scalar operator () (const OT::Point & x1, const OT::Point & x2) const;

  /** Partial Gradient */
  OT::Point partialGradient(const OT::Point & x1, const OT::Point & x2) const;

  /** Partial hessian */
  OT::SymmetricMatrix partialHessian(const OT::Point & x1, const OT::Point & x2) const;

} ; /* class SVMKernel */

}

#endif /* OPENTURNS_SVMKERNEL_HXX */
