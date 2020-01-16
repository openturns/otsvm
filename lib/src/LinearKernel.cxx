//                                               -*- C++ -*-
/**
 *  @brief Implementation of the linear kernel
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

#include "otsvm/LinearKernel.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>
#include <cmath>

using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(LinearKernel)

static Factory<LinearKernel> RegisteredFactory_LinearKernel;

/* Constructor */
LinearKernel::LinearKernel():
  SVMKernelImplementation()
{
  //Nothing to do
}


/* Virtual constructor */
LinearKernel * LinearKernel::clone() const
{
  return new LinearKernel(*this);
}


/* String converter */
String LinearKernel::__repr__() const
{
  return OSS()  << "class=" << getClassName();
}


/* Operator */
Scalar LinearKernel::operator() ( const Point & x1 , const Point & x2 ) const
{
  Scalar value = x1.dot(x2);
  return value;
}


/* Partial Gradient */
Point LinearKernel::partialGradient( const Point & x1 , const Point & x2 ) const
{
  UnsignedInteger dimension = x1.getDimension();
  Point result(dimension , 0.0);
  for( UnsignedInteger i = 0 ; i < dimension ; i ++ )
  {
    result[i] = x2[i];
  }
  return result;
}


/* Partial Hessian */
SymmetricMatrix LinearKernel::partialHessian( const Point & x1 , const Point & x2 )const
{
  UnsignedInteger dimension = x1.getDimension();
  SymmetricMatrix result(dimension);
  for( UnsignedInteger i = 0 ; i < dimension ; i++ )
  {
    for( UnsignedInteger j = 0 ; j <= i ; j++ )
    {
      result( i , j ) = 0;
    }
  }
  return result;
}


void LinearKernel::save(OT::Advocate& adv) const
{
  SVMKernelImplementation::save(adv);
}

void LinearKernel::load(OT::Advocate& adv)
{
  SVMKernelImplementation::load(adv);
}


}

