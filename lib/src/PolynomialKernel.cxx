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
#include <OSS.hxx>
#include <PersistentObjectFactory.hxx>
#include <cmath>

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(PolynomialKernel);


/* Constructor with parameters */
PolynomialKernel::PolynomialKernel(const NumericalScalar degree, const NumericalScalar linear, const NumericalScalar constant)
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
NumericalScalar PolynomialKernel::getDegree() const
{
  return degree_;
}

void PolynomialKernel::setDegree(NumericalScalar degree)
{
  degree_ = degree;
}


/* Linear term accessor */
NumericalScalar PolynomialKernel::getLinear() const
{
  return linear_;
}

void PolynomialKernel::setLinear(NumericalScalar linear)
{
  linear_ = linear;
}


/* Constant term accessor */
NumericalScalar PolynomialKernel::getConstant() const
{
  return constant_;
}

void PolynomialKernel::setConstant(NumericalScalar constant)
{
  constant_ = constant;
}


/* Accessor to the parameter used for cross-validation */
NumericalScalar PolynomialKernel::getParameter() const
{
  return degree_;
}

void PolynomialKernel::setParameter(NumericalScalar value)
{
  degree_ = value;
}


/* Operator () */
NumericalScalar PolynomialKernel::operator() (const NumericalPoint & x1, const NumericalPoint & x2) const
{
  NumericalScalar dotProduct = dot(x1, x2);
  NumericalScalar value = std::pow(linear_ * dotProduct + constant_, degree_);
  return value;
}


/* Parameters value and description accessor */
NumericalPointWithDescription PolynomialKernel::getParameters() const
{
  NumericalPointWithDescription parameters(0);
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

void PolynomialKernel::setParameters(const NumericalPointWithDescription & parameters)
{
  if(parameters.getDimension() > 0)
    degree_ = parameters[0];
  if(parameters.getDimension() > 1)
    constant_ = parameters[1];
}


/* Partial gradient */
NumericalPoint PolynomialKernel::partialGradient(const NumericalPoint & x1, const NumericalPoint & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  NumericalScalar dotProduct = dot(x1, x2);
  NumericalPoint result(dimension, 0.0);
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
SymmetricMatrix PolynomialKernel::partialHessian(const NumericalPoint & x1, const NumericalPoint & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  SymmetricMatrix result(dimension);
  NumericalScalar dotProduct = dot(x1, x2);
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
