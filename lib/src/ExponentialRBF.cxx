//                                               -*- C++ -*-
/**
 *  @brief Implementation of the Exponential RBF kernel
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
#include "otsvm/ExponentialRBF.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(ExponentialRBF)

static Factory<ExponentialRBF> RegisteredFactory_ExponentialRBF;

/* Constructor with parameters */
ExponentialRBF::ExponentialRBF(const Scalar sigma)
  : SVMKernelImplementation(),
    sigma_(sigma)
{
  // Nothing to do
}


/* Virtual constructor */
ExponentialRBF * ExponentialRBF::clone() const
{
  return new ExponentialRBF(*this);
}


/* String converter */
String ExponentialRBF::__repr__() const
{
  return OSS() << "class=" << getClassName()
         << " sigma=" << getSigma();
}


/* Sigma parameter accessor */
Scalar ExponentialRBF::getSigma() const
{
  return sigma_;
}

void ExponentialRBF::setSigma(const Scalar sigma)
{
  sigma_ = sigma;
}


/* Accessor to the parameter used for cross-validation */
Point ExponentialRBF::getParameter() const
{
  return {sigma_};
}

void ExponentialRBF::setParameter(const Point & parameter)
{
  if (parameter.getDimension() != 1)
    throw InvalidArgumentException(HERE) << "ExponentialRBF expected a parameter of dimension 1";
  sigma_ = parameter[0];
}


/* Parameters value and description accessor */
Description ExponentialRBF::getParameterDescription() const
{
  return {"sigma"};
}

/* Operator () */
Scalar ExponentialRBF::operator() (const Point & x1, const Point & x2) const
{
  Point difference(x1 - x2);
  Scalar value = exp(- difference.norm() / (2.0 * sigma_ * sigma_));
  return value;
}


/* Partial gradient */
Point ExponentialRBF::partialGradient(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Point difference(x1 - x2);
  Scalar norm = difference.norm();
  Point result(dimension, 0.0);
  if (norm > 0.0)
  {
    for (UnsignedInteger i = 0; i < dimension; ++ i)
    {
      result[i] = exp(- norm / (2.0 * sigma_ * sigma_)) * (- 1.0 / (2.0 * sigma_ * sigma_)) * (x1[i] - x2[i]) / norm;
    }
  }
  return result;
}


/* Partial hessian */
SymmetricMatrix ExponentialRBF::partialHessian(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Point difference(x1 - x2);
  Scalar norm = difference.norm();
  SymmetricMatrix result(dimension);
  if (norm > 0.0)
  {
    for (UnsignedInteger i = 0; i < dimension; ++ i)
    {
      for (UnsignedInteger j = 0; j <= i; ++ j)
      {
        if (i == j)
        {
          result(i, i) = exp(- norm / (2.0 * sigma_ * sigma_)) * (- 1.0 / (2.0 * sigma_ * sigma_)) / norm * ( (- 1.0 / (2.0 * sigma_ * sigma_)) * (x1[i] - x2[i]) * (x1[i] - x2[i]) / norm + 1.0 - 0.5 * (x1[i] - x2[i]) * (x1[i] - x2[i]) / (norm * norm) );
        }
        else
        {
          result(i, j) = exp(- norm / (2.0 * sigma_ * sigma_)) * (- 1.0 / (2.0 * sigma_ * sigma_)) * (x1[i] - x2[i]) * (x1[j] - x2[j]) / (norm * norm) * ( (- 1.0 / (2.0 * sigma_ * sigma_)) - 1.0 / norm );
        }
      }
    }
  }
  return result;
}


void ExponentialRBF::save(OT::Advocate& adv) const
{
  SVMKernelImplementation::save(adv);
  adv.saveAttribute("sigma_", sigma_);
}


void ExponentialRBF::load(OT::Advocate& adv)
{
  SVMKernelImplementation::load(adv);
  adv.loadAttribute("sigma_", sigma_);
}


}
