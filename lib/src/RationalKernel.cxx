//                                               -*- C++ -*-
/**
 *  @brief Implementation of the rational kernel
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
#include "otsvm/RationalKernel.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(RationalKernel)

static Factory<RationalKernel> RegisteredFactory_RationalKernel;

/* Constructor with parameters */
RationalKernel::RationalKernel(const Scalar constant)
  : SVMKernelImplementation(),
    constant_(constant)
{
  // Nothing to do
}


/* Virtual constructor */
RationalKernel * RationalKernel::clone() const
{
  return new RationalKernel(*this);
}


/* String converter */
String RationalKernel::__repr__() const
{
  return OSS() << "class=" << getClassName()
         << " constant=" << getConstant();
}


/* Constant term accessor */
Scalar RationalKernel::getConstant() const
{
  return constant_;
}

void RationalKernel::setConstant(Scalar constant)
{
  constant_ = constant;
}


/* Accessor to the parameter used for cross-validation */
Scalar RationalKernel::getParameter() const
{
  return constant_;
}

void RationalKernel::setParameter(Scalar value)
{
  constant_ = value;
}


/* Parameters value and description accessor */
PointWithDescription RationalKernel::getParameters() const
{
  PointWithDescription parameters(0);
  Description description(0);
  parameters.add(constant_);
  description.add("constant");
  parameters.setDescription(description);
  return parameters;
}

void RationalKernel::setParameters(const PointWithDescription & parameters)
{
  if(parameters.getDimension() > 0)
    constant_ = parameters[0];
}

/* Operator () */
Scalar RationalKernel::operator() (const Point & x1, const Point & x2) const
{
  Point difference(x1 - x2);
  Scalar norm2 = difference.normSquare();
  Scalar value = 1.0 - norm2 / (norm2 + constant_);
  return value;
}


/* Partial gradient */
Point RationalKernel::partialGradient(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Point difference(x1 - x2);
  Scalar norm2 = difference.normSquare();
  Point result(dimension);
  for(UnsignedInteger i = 0; i < dimension; ++ i)
  {
    result[i] = - 2.0 * constant_ * (x1[i] - x2[i]) / ((norm2 + constant_) * (norm2 + constant_));
  }
  return result;
}


/* Partial hessian */
SymmetricMatrix RationalKernel::partialHessian(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Point difference(x1 - x2);
  Scalar norm2 = difference.normSquare();
  Scalar denominator = (norm2 + constant_) * (norm2 + constant_) * (norm2 + constant_);
  SymmetricMatrix result(dimension);
  for(UnsignedInteger i = 0; i < dimension; ++ i)
  {
    for(UnsignedInteger j = 0; j <= i; ++ j)
    {
      if(i == j)
      {
        result(i, i) = 2.0 * constant_ * (- (norm2 + constant_) + 4.0 * (x1[i] - x2[i]) * (x1[i] - x2[i])) / denominator;
      }
      else
      {
        result(i, j) = 8.0 * constant_ * (x1[i] - x2[i]) * (x1[j] - x2[j]) / denominator;
      }
    }
  }
  return result;
}

void RationalKernel::save(OT::Advocate& adv) const
{
  SVMKernelImplementation::save(adv);
  adv.saveAttribute("constant_", constant_);
}

void RationalKernel::load(OT::Advocate& adv)
{
  SVMKernelImplementation::load(adv);
  adv.loadAttribute("constant_", constant_);
}


}
