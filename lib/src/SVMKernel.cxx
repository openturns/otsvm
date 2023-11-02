//                                               -*- C++ -*-
/**
 *  @brief This is the interface class for kernels used by support vector regression
 *
 *  Copyright 2014-2023 Phimeca
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
#include "otsvm/SVMKernel.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>
#include <openturns/Point.hxx>

using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(SVMKernel)


/* Default constructor */
SVMKernel::SVMKernel()
  : TypedInterfaceObject<SVMKernelImplementation>()
{
  // Nothing to do
}


/* Constructor from implementation */
SVMKernel::SVMKernel(const SVMKernelImplementation & implementation)
  : TypedInterfaceObject<SVMKernelImplementation>(implementation.clone())
{
  // Nothing to do
}


/* Constructor with parameters */
SVMKernel::SVMKernel(Implementation & p_implementation)
  : TypedInterfaceObject<SVMKernelImplementation>(p_implementation)
{
  // Nothing to do
}


/* String converter */
String SVMKernel::__repr__() const
{
  return OSS() << "class=" << getClassName()
         << " implementation=" << getImplementation()->__repr__();
}


/* String converter */
String SVMKernel::__str__(const String & /*offset*/) const
{
  return __repr__();
}


/* Parameter accessor */
Point SVMKernel::getParameter() const
{
  return getImplementation()->getParameter();
}

void SVMKernel::setParameter(const Point & parameter)
{
  copyOnWrite();
  getImplementation()->setParameter(parameter);
}

/* Parameters value and description accessor */
Description SVMKernel::getParameterDescription() const
{
  return getImplementation()->getParameterDescription();
}

/* Operator () */
Scalar SVMKernel::operator() (const Point & x1, const Point & x2) const
{
  return getImplementation()->operator()(x1, x2);
}


/* Partial gradient */
Point SVMKernel::partialGradient(const Point & x1, const Point & x2) const
{
  return getImplementation()->partialGradient(x1, x2);
}


/* Partial hessian */
SymmetricMatrix SVMKernel::partialHessian(const Point & x1, const Point & x2) const
{
  return getImplementation()->partialHessian(x1, x2);
}


}
