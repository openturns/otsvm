//                                               -*- C++ -*-
/**
 *  @brief Implementation of the sigmoid kernel
 *
 *  Copyright 2005-2016 EDF-EADS-Phimeca
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


CLASSNAMEINIT(SigmoidKernel);

static Factory<SigmoidKernel> RegisteredFactory;

/* Constructor with parameters */
SigmoidKernel::SigmoidKernel( const NumericalScalar linear , const NumericalScalar constant ):
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
NumericalScalar SigmoidKernel::getLinear() const
{
  return linear_;
}

void SigmoidKernel::setLinear( NumericalScalar linear )
{
  linear_ = linear;
}


/* Constant term accessor */
NumericalScalar SigmoidKernel::getConstant() const
{
  return constant_;
}

void SigmoidKernel::setConstant( NumericalScalar constant )
{
  constant_ = constant;
}


/* Parameters value and description accessor */
NumericalPointWithDescription SigmoidKernel::getParameters() const
{
  NumericalPointWithDescription parameters(0);
  Description description(0);
  parameters.add(linear_);
  description.add("linear term");
  parameters.add(constant_);
  description.add("constant term");
  parameters.setDescription(description);
  return parameters;
}

void SigmoidKernel::setParameters( const NumericalPointWithDescription & parameters )
{
  if( parameters.getDimension() > 0 )
    linear_ = parameters[0];
  if( parameters.getDimension() > 1 )
    constant_ = parameters[1];
}


/* Operator () */
NumericalScalar SigmoidKernel::operator() ( const NumericalPoint & x1 , const NumericalPoint & x2 ) const
{
  NumericalScalar dotProduct = dot( x1 , x2 );
  NumericalScalar value = tanh( linear_ * dotProduct + constant_ );
  return value;
}


/* Partial gradient */
NumericalPoint SigmoidKernel::partialGradient( const NumericalPoint & x1 , const NumericalPoint & x2 ) const
{
  UnsignedInteger dimension = x1.getDimension();
  NumericalScalar dotProduct = dot( x1 , x2 );
  NumericalPoint result(dimension , 0.0);
  for( UnsignedInteger i = 0 ; i < dimension ; i ++ )
  {
    result[i] = linear_ * x2[i] * ( 1 - std::pow( tanh( linear_ * dotProduct + constant_), 2));
  }
  return result;
}


/* Partial hessian */
SymmetricMatrix SigmoidKernel::partialHessian( const NumericalPoint & x1 , const NumericalPoint & x2 )const
{
  UnsignedInteger dimension = x1.getDimension();
  NumericalScalar dotProduct = dot( x1 , x2 );
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

