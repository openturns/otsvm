//                                               -*- C++ -*-
/**
 *  @brief Implementation of the Normal RBF kernel, also known as the gaussian kernel
 *
 *  Copyright 2005-2012 EDF-EADS-Phimeca
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
#include "otsvm/NormalRBF.hxx"
#include <OSS.hxx>
#include <PersistentObjectFactory.hxx>

using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(NormalRBF);

static Factory<NormalRBF> RegisteredFactory;


/* Constructor with parameters */
NormalRBF::NormalRBF(const NumericalScalar sigma)
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
NumericalScalar NormalRBF::getSigma() const
{
  return sigma_;
}

void NormalRBF::setSigma(NumericalScalar sigma)
{
  sigma_ = sigma;
}


/* Accessor to the parameter used for cross-validation */
NumericalScalar NormalRBF::getParameter() const
{
  return sigma_;
}

void NormalRBF::setParameter(NumericalScalar value)
{
  sigma_ = value;
}


/* Parameters value and description accessor */
NumericalPointWithDescription NormalRBF::getParameters() const
{
  NumericalPointWithDescription parameters(0);
  Description description(0);
  parameters.add(sigma_);
  description.add("sigma");
  parameters.setDescription(description);
  return parameters;
}

void NormalRBF::setParameters(const NumericalPointWithDescription & parameters)
{
  if(parameters.getDimension() > 0)
    sigma_ = parameters[0];
}


/* Operator () */
NumericalScalar NormalRBF::operator() (const NumericalPoint & x1, const NumericalPoint & x2) const
{
  NumericalPoint difference(x1 - x2);
  NumericalScalar value = exp(- difference.normSquare() / (2.0 * sigma_ * sigma_));
  return value;
}


/* Partial gradient */
NumericalPoint NormalRBF::partialGradient(const NumericalPoint & x1, const NumericalPoint & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  NumericalPoint difference(x1 - x2);
  NumericalPoint result(dimension);
  for(UnsignedInteger i = 0; i < dimension; ++ i)
  {
    result[i]  = exp(- difference.normSquare() / (2.0 * sigma_ * sigma_)) * (- (x1[i] - x2[i]) / (sigma_ * sigma_));
  }
  return result;
}


/* Partial hessian */
SymmetricMatrix NormalRBF::partialHessian(const NumericalPoint & x1, const NumericalPoint & x2) const
{
  UnsignedInteger dimension = x1.getDimension();
  NumericalPoint difference(x1 - x2);
  NumericalScalar norm2 = difference.normSquare();
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
