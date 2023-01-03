//                                               -*- C++ -*-
/**
 *  @brief Implementation of the sigmoid kernel
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

#include "otsvm/SigmoidKernel.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>
#include <cmath>

using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(SigmoidKernel)

static Factory<SigmoidKernel> RegisteredFactory_SigmoidKernel;

/* Constructor with parameters */
SigmoidKernel::SigmoidKernel( const Scalar linear , const Scalar constant ):
  SVMKernelImplementation(),
  linear_(linear),
  constant_(constant)
{
  //Nothing to do
}


/* Virtual constructor */
SigmoidKernel * SigmoidKernel::clone() const
{
  return new SigmoidKernel(*this);
}


/* String converter */
String SigmoidKernel::__repr__() const
{
  return OSS()  << "class=" << getClassName()
         << "constant=" << constant_
         << "linear=" << linear_;
}


/* Linear term accessor */
Scalar SigmoidKernel::getLinear() const
{
  return linear_;
}

void SigmoidKernel::setLinear( Scalar linear )
{
  linear_ = linear;
}


/* Constant term accessor */
Scalar SigmoidKernel::getConstant() const
{
  return constant_;
}

void SigmoidKernel::setConstant( Scalar constant )
{
  constant_ = constant;
}


/* Parameters value and description accessor */
PointWithDescription SigmoidKernel::getParameters() const
{
  PointWithDescription parameters(0);
  Description description(0);
  parameters.add(linear_);
  description.add("linear term");
  parameters.add(constant_);
  description.add("constant term");
  parameters.setDescription(description);
  return parameters;
}

void SigmoidKernel::setParameters( const PointWithDescription & parameters )
{
  if( parameters.getDimension() > 0 )
    linear_ = parameters[0];
  if( parameters.getDimension() > 1 )
    constant_ = parameters[1];
}


/* Operator () */
Scalar SigmoidKernel::operator() ( const Point & x1 , const Point & x2 ) const
{
  Scalar dotProduct = x1.dot(x2);
  Scalar value = tanh( linear_ * dotProduct + constant_ );
  return value;
}


/* Partial gradient */
Point SigmoidKernel::partialGradient( const Point & x1 , const Point & x2 ) const
{
  UnsignedInteger dimension = x1.getDimension();
  Scalar dotProduct = x1.dot(x2);
  Point result(dimension , 0.0);
  for( UnsignedInteger i = 0 ; i < dimension ; i ++ )
  {
    result[i] = linear_ * x2[i] * ( 1 - std::pow( tanh( linear_ * dotProduct + constant_), 2));
  }
  return result;
}


/* Partial hessian */
SymmetricMatrix SigmoidKernel::partialHessian( const Point & x1 , const Point & x2 )const
{
  UnsignedInteger dimension = x1.getDimension();
  Scalar dotProduct = x1.dot(x2);
  SymmetricMatrix result(dimension);
  for (UnsignedInteger i = 0 ; i < dimension ; ++ i)
  {
    for (UnsignedInteger j = 0 ; j <= i ; ++ j)
    {
      result(i, j) = 2 * linear_ * x2[i] * linear_ * x2[j] * ( 1 - std::pow( tanh(linear_ * dotProduct + constant_) , 2 )) * tanh( linear_ * dotProduct + constant_ );
    }
  }

  return result;
}


void SigmoidKernel::save(OT::Advocate& adv) const
{
  SVMKernelImplementation::save(adv);
  adv.saveAttribute("linear_", linear_);
  adv.saveAttribute("constant_", constant_);
}

void SigmoidKernel::load(OT::Advocate& adv)
{
  SVMKernelImplementation::load(adv);
  adv.loadAttribute("linear_", linear_);
  adv.loadAttribute("constant_", constant_);
}


}

