//                                               -*- C++ -*-
/**
 *  @brief Implementation of the Normal RBF kernel, also known as the gaussian kernel
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
#include "otsvm/NormalRBF.hxx"
#include <openturns/OSS.hxx>
#include <openturns/PersistentObjectFactory.hxx>

using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(NormalRBF)

static Factory<NormalRBF> RegisteredFactory_NormalRBF;


/* Constructor with parameters */
NormalRBF::NormalRBF(const Scalar sigma)
  : SVMKernelImplementation(),
    sigma_(sigma)
{
  // Nothing to do
}


/* Virtual constructor */
NormalRBF * NormalRBF::clone() const
{
  return new NormalRBF(*this);
}


/* String converter */
String NormalRBF::__repr__() const
{
  return OSS() << "class=" << getClassName()
         << " sigma=" << getSigma();
}


/* Sigma parameter accessor */
Scalar NormalRBF::getSigma() const
{
  return sigma_;
}

void NormalRBF::setSigma(Scalar sigma)
{
  sigma_ = sigma;
}


/* Accessor to the parameter used for cross-validation */
Point NormalRBF::getParameter() const
{
  return {sigma_};
}

void NormalRBF::setParameter(const Point & parameter)
{
  sigma_ = parameter[0];
}


/* Parameters value and description accessor */
Description NormalRBF::getParameterDescription() const
{
  return {"sigma"};
}


/* Operator () */
Scalar NormalRBF::operator() (const Point & x1, const Point & x2) const
{
  Point difference(x1 - x2);
  Scalar value = exp(- difference.normSquare() / (2.0 * sigma_ * sigma_));
  return value;
}


/* Partial gradient */
Point NormalRBF::partialGradient(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Point difference(x1 - x2);
  Point result(dimension);
  for(UnsignedInteger i = 0; i < dimension; ++ i)
  {
    result[i]  = exp(- difference.normSquare() / (2.0 * sigma_ * sigma_)) * (- (x1[i] - x2[i]) / (sigma_ * sigma_));
  }
  return result;
}


/* Partial hessian */
SymmetricMatrix NormalRBF::partialHessian(const Point & x1, const Point & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  Point difference(x1 - x2);
  Scalar norm2 = difference.normSquare();
  SymmetricMatrix result(dimension);
  for (UnsignedInteger i = 0; i < dimension; ++ i)
  {
    for (UnsignedInteger j = 0; j <= i; ++ j)
    {
      if (i == j)
      {
        result(i, i) = exp(- norm2 / (2.0 * sigma_ * sigma_)) * ((- (x1[i] - x2[i]) / (sigma_ * sigma_)) * (- (x1[i] - x2[i]) / (sigma_ * sigma_)) - 1.0 / (sigma_ * sigma_));
      }
      else
      {
        result(i, j) = exp(- norm2 / (2.0 * sigma_ * sigma_)) * (- (x1[i] - x2[i]) / (sigma_ * sigma_)) * (- (x1[j] - x2[j]) / (sigma_ * sigma_));
      }
    }
  }
  return result;
}


void NormalRBF::save(Advocate& adv) const
{
  SVMKernelImplementation::save(adv);
  adv.saveAttribute("sigma_", sigma_);
}


void NormalRBF::load(Advocate& adv)
{
  SVMKernelImplementation::load(adv);
  adv.loadAttribute("sigma_", sigma_);
}


}
