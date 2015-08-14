//                                               -*- C++ -*-
/**
 *  @file  ExponentialRBF.cxx
 *  @brief Implementation of the Exponential RBF kernel
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
#include "ExponentialRBF.hxx"
#include "OSS.hxx"
#include "PersistentObjectFactory.hxx"

using namespace OT;

namespace OTSVM
{



CLASSNAMEINIT(ExponentialRBF);

static Factory<ExponentialRBF> RegisteredFactory("ExponentialRBF");

/* Constructor with parameters */
ExponentialRBF::ExponentialRBF(const NumericalScalar sigma)
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
NumericalScalar ExponentialRBF::getSigma() const
{
  return sigma_;
}

void ExponentialRBF::setSigma(NumericalScalar sigma)
{
  sigma_ = sigma;
}


/* Accessor to the parameter used for cross-validation */
NumericalScalar ExponentialRBF::getParameter() const
{
  return sigma_;
}

void ExponentialRBF::setParameter(NumericalScalar value)
{
  sigma_ = value;
}


/* Parameters value and description accessor */
NumericalPointWithDescription ExponentialRBF::getParameters() const
{
  NumericalPointWithDescription parameters(0);
  Description description(0);
  parameters.add(sigma_);
  description.add("sigma");
  parameters.setDescription(description);
  return parameters;
}

void ExponentialRBF::setParameters(const NumericalPointWithDescription & parameters)
{
  if(parameters.getDimension() > 0)
    sigma_ = parameters[0];
}


/* Operator () */
NumericalScalar ExponentialRBF::operator() (const NumericalPoint & x1, const NumericalPoint & x2) const
{
  NumericalPoint difference(x1 - x2);
  NumericalScalar value = exp(- difference.norm() / (2.0 * sigma_ * sigma_));
  return value;
}


/* Partial gradient */
NumericalPoint ExponentialRBF::partialGradient(const NumericalPoint & x1, const NumericalPoint & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  NumericalPoint difference(x1 - x2);
  NumericalScalar norm = difference.norm();
  NumericalPoint result(dimension, 0.0);
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
SymmetricMatrix ExponentialRBF::partialHessian(const NumericalPoint & x1, const NumericalPoint & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  NumericalPoint difference(x1 - x2);
  NumericalScalar norm = difference.norm();
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
