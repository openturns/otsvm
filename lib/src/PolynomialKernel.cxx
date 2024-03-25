//                                               -*- C++ -*-
/**
 *  @brief Implementation of the polynomial kernel
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
#include "otsvm/PolynomialKernel.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>
#include <cmath>

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(PolynomialKernel)

static Factory<PolynomialKernel> RegisteredFactory_PolynomialKernel;

/* Constructor with parameters */
PolynomialKernel::PolynomialKernel(const Scalar degree, const Scalar linear, const Scalar constant)
  : SVMKernelImplementation(),
    degree_(degree),
    linear_(linear),
    constant_(constant)
{
  // Nothing to do
}


/* Virtual constructor */
PolynomialKernel * PolynomialKernel::clone() const
{
  return new PolynomialKernel(*this);
}


/* String converter */
String PolynomialKernel::__repr__() const
{
  return OSS() << "class=" << getClassName()
         << " degree=" << degree_
         << " linear=" << linear_
         << " constant=" << constant_;
}


/* Sigma parameter accessor */
Scalar PolynomialKernel::getDegree() const
{
  return degree_;
}

void PolynomialKernel::setDegree(Scalar degree)
{
  degree_ = degree;
}


/* Linear term accessor */
Scalar PolynomialKernel::getLinear() const
{
  return linear_;
}

void PolynomialKernel::setLinear(Scalar linear)
{
  linear_ = linear;
}


/* Constant term accessor */
Scalar PolynomialKernel::getConstant() const
{
  return constant_;
}

void PolynomialKernel::setConstant(Scalar constant)
{
  constant_ = constant;
}


/* Accessor to the parameter used for cross-validation */
Point PolynomialKernel::getParameter() const
{
  return {degree_, linear_, constant_};
}

void PolynomialKernel::setParameter(const Point & parameter)
{
  if (parameter.getDimension() != 3)
    throw InvalidArgumentException(HERE) << "PolynomialKernel expected a parameter of dimension 3";
  degree_ = parameter[0];
  linear_ = parameter[1];
  constant_ = parameter[2];
}


/* Operator () */
Scalar PolynomialKernel::operator() (const Point & x1, const Point & x2) const
{
  Scalar dotProduct = x1.dot(x2);
  Scalar value = std::pow(linear_ * dotProduct + constant_, degree_);
  return value;
}


/* Parameters value and description accessor */
Description PolynomialKernel::getParameterDescription() const
{
  return { "degree", "linear term", "constant term"};
}

/* Partial gradient */
Point PolynomialKernel::partialGradient(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Scalar dotProduct = x1.dot(x2);
  Point result(dimension, 0.0);
  if(degree_ >= 1.0)
  {
    for(UnsignedInteger i = 0; i < dimension; ++ i)
    {
      result[i] = degree_ * std::pow(linear_ * dotProduct + constant_, degree_ - 1.0) * linear_ * x2[i];
    }
  }
  return result;
}


/* Partial hessian */
SymmetricMatrix PolynomialKernel::partialHessian(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  SymmetricMatrix result(dimension);
  Scalar dotProduct = x1.dot(x2);
  if (degree_ >= 2.0)
  {
    for (UnsignedInteger i = 0; i < dimension; ++ i)
    {
      for (UnsignedInteger j = 0; j <= i; ++ j)
      {
        result(i, j) = degree_ * (degree_ - 1.0) * std::pow(linear_ * dotProduct + constant_, degree_ - 2.0) * linear_ * x2[i] * linear_ * x2[j];
      }
    }
  }
  return result;
}


void PolynomialKernel::save(OT::Advocate& adv) const
{
  SVMKernelImplementation::save(adv);
  adv.saveAttribute("degree_", degree_);
  adv.saveAttribute("linear_", linear_);
  adv.saveAttribute("constant_", constant_);
}

void PolynomialKernel::load(OT::Advocate& adv)
{
  SVMKernelImplementation::load(adv);
  adv.loadAttribute("degree_", degree_);
  adv.loadAttribute("linear_", linear_);
  adv.loadAttribute("constant_", constant_);
}


}
