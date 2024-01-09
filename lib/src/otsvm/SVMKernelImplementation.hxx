//                                               -*- C++ -*-
/**
 *  @brief This is a abstract class for the kernels used by support vector regression
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
  SVMKernelImplementation * clone() const override;

  /** String converter */
  OT::String __repr__() const override;

  /** Parameter accessor */
  virtual OT::Point getParameter() const;
  virtual void setParameter(const OT::Point & parameter);
  virtual OT::Description getParameterDescription() const;

  /** Operator () */
  virtual OT::Scalar operator () (const OT::Point & x1, const OT::Point & x2) const;

  /** Partial gradient */
  virtual OT::Point partialGradient(const OT::Point & x1, const OT::Point & x2) const;

  /** Partial hessian */
  virtual OT::SymmetricMatrix partialHessian(const OT::Point & x1, const OT::Point & x2) const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

protected:


private:

} ; /* class SVMKernelImplementation */


}

#endif /* OPENTURNS_SVMKERNELIMPLEMENTATION_HXX */
