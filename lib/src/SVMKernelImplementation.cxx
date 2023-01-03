//                                               -*- C++ -*-
/**
 *  @brief Implementation of SVMKernel
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
#include "otsvm/SVMKernelImplementation.hxx"
#include <openturns/Exception.hxx>

using namespace OT;

namespace OTSVM
{

/**
 * @class SVMKernelImplementation
 */

CLASSNAMEINIT(SVMKernelImplementation)

/* Constructor with parameters */
SVMKernelImplementation::SVMKernelImplementation()
  : PersistentObject()
{
  // Nothing to do
}

/* Virtual constructor */
SVMKernelImplementation * SVMKernelImplementation::clone() const
{
  return new SVMKernelImplementation(*this);
}

/* String converter */
String SVMKernelImplementation::__repr__() const
{
  OSS oss;
  oss << "class=" << SVMKernelImplementation::GetClassName();
  return oss;
}


/* Parameter accessor */
Scalar SVMKernelImplementation::getParameter() const
{
  throw NotYetImplementedException(HERE);
}

void SVMKernelImplementation::setParameter(Scalar /*value*/)
{
  throw NotYetImplementedException(HERE);
}


/* Parameters value and description accessor */
PointWithDescription SVMKernelImplementation::getParameters() const
{
  throw NotYetImplementedException(HERE);
}

void SVMKernelImplementation::setParameters(const PointWithDescription & /*parameters*/)
{
  throw NotYetImplementedException(HERE);
}


/* Operator () */
Scalar SVMKernelImplementation::operator () (const Point & /*x1*/, const Point & /*x2*/) const
{
  throw NotYetImplementedException(HERE);
}


/* Partial gradient */
Point SVMKernelImplementation::partialGradient(const Point & /*x*/, const Point & /*y*/) const
{
  throw NotYetImplementedException(HERE);
}


/* Partial hessian */
SymmetricMatrix SVMKernelImplementation::partialHessian(const Point & x, const Point & /*y*/) const
{
  return SymmetricMatrix(x.getDimension());
  //      throw NotYetImplementedException(HERE);
}

/* Method save() stores the object through the StorageManager */
void SVMKernelImplementation::save(Advocate & adv) const
{
  PersistentObject::save(adv);
}


/* Method load() reloads the object from the StorageManager */
void SVMKernelImplementation::load(Advocate & adv)
{
  PersistentObject::load(adv);
}


}
