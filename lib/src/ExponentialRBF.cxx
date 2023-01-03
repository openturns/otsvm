//                                               -*- C++ -*-
/**
 *  @file  ExponentialRBF.cxx
 *  @brief Implementation of the Exponential RBF kernel
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

void ExponentialRBF::setSigma(Scalar sigma)
{
  sigma_ = sigma;
}


/* Accessor to the parameter used for cross-validation */
Scalar ExponentialRBF::getParameter() const
{
  return sigma_;
}

void ExponentialRBF::setParameter(Scalar value)
{
  sigma_ = value;
}


/* Parameters value and description accessor */
PointWithDescription ExponentialRBF::getParameters() const
{
  PointWithDescription parameters(0);
  Description description(0);
  parameters.add(sigma_);
  description.add("sigma");
  parameters.setDescription(description);
  return parameters;
}

void ExponentialRBF::setParameters(const PointWithDescription & parameters)
{
  if(parameters.getDimension() > 0)
    sigma_ = parameters[0];
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
