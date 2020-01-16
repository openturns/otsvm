//                                               -*- C++ -*-
/**
 *  @brief This is a abstract class for the kernels used by support vector regression
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
#ifndef OPENTURNS_SVMKERNELIMPLEMENTATION_HXX
#define OPENTURNS_SVMKERNELIMPLEMENTATION_HXX

#include <openturns/PointWithDescription.hxx>
#include <openturns/SymmetricMatrix.hxx>
#include "otsvm/OTSVMprivate.hxx"

namespace OTSVM
{


/**
 * @class SVMKernelImplementation
 *
 * This is a abstract class for the kernels used by support vector regression
 */

class OTSVM_API SVMKernelImplementation
  : public OT::PersistentObject

{
  CLASSNAME
public:


  /** Default constructor */
  SVMKernelImplementation();

  /** Virtual constructor */
  virtual SVMKernelImplementation * clone() const;

  /** String converter */
  virtual OT::String __repr__() const;

  /** Parameter accessor */
  virtual OT::Scalar getParameter() const;
  virtual void setParameter(OT::Scalar value);

  /** Parameters value and description accessor */
  virtual OT::PointWithDescription getParameters() const;
  virtual void setParameters(const OT::PointWithDescription & parameters);

  /** Operator () */
  virtual OT::Scalar operator () (const OT::Point & x1, const OT::Point & x2) const;

  /** Partial gradient */
  virtual OT::Point partialGradient(const OT::Point & x1, const OT::Point & x2) const;

  /** Partial hessian */
  virtual OT::SymmetricMatrix partialHessian(const OT::Point & x1, const OT::Point & x2) const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

protected:


private:

} ; /* class SVMKernelImplementation */


}

#endif /* OPENTURNS_SVMKERNELIMPLEMENTATION_HXX */
