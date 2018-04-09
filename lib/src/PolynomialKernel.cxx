//                                               -*- C++ -*-
/**
 *  @brief Implementation of the polynomial kernel
 *
 *  Copyright 2005-2015 EDF-EADS-Phimeca
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
#include "otsvm/PolynomialKernel.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>
#include <cmath>

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(PolynomialKernel)


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
Scalar PolynomialKernel::getParameter() const
{
  return degree_;
}

void PolynomialKernel::setParameter(Scalar value)
{
  degree_ = value;
}


/* Operator () */
Scalar PolynomialKernel::operator() (const Point & x1, const Point & x2) const
{
  Scalar dotProduct = dot(x1, x2);
  Scalar value = std::pow(linear_ * dotProduct + constant_, degree_);
  return value;
}


/* Parameters value and description accessor */
PointWithDescription PolynomialKernel::getParameters() const
{
  PointWithDescription parameters(0);
  Description description(0);
  parameters.add(degree_);
  description.add("degree");
  parameters.add(linear_);
  description.add("linear term");
  parameters.add(constant_);
  description.add("constant term");
  parameters.setDescription(description);
  return parameters;
}

void PolynomialKernel::setParameters(const PointWithDescription & parameters)
{
  if(parameters.getDimension() > 0)
    degree_ = parameters[0];
  if(parameters.getDimension() > 1)
    constant_ = parameters[1];
}


/* Partial gradient */
Point PolynomialKernel::partialGradient(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Scalar dotProduct = dot(x1, x2);
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
  Scalar dotProduct = dot(x1, x2);
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
