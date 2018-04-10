//                                               -*- C++ -*-
/**
 *  @brief Implementation of the regression
 *
 *  Copyright 2005-2018 EDF-EADS-Phimeca
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


#include "otsvm/SVMRegressionImplementation.hxx"

using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(SVMRegressionImplementation)

/* Default constructor*/
SVMRegressionImplementation::SVMRegressionImplementation()
  : PersistentObject()
  , tradeoffFactor_(1, 10.)
  , kernelParameter_(1, 1.0)
{
  //Nothing to do
}

/* Virtual constructor */
SVMRegressionImplementation* SVMRegressionImplementation::clone() const
{
  return new SVMRegressionImplementation(*this);
}


/* Method run */
void SVMRegressionImplementation::run()
{
  //Nothing to do
}

/* Tradeoff factor accessor */
void SVMRegressionImplementation::setTradeoffFactor(const Point & tradeoffFactor)
{
  tradeoffFactor_ = tradeoffFactor;
}

Point SVMRegressionImplementation::getTradeoffFactor()
{
  return tradeoffFactor_;
}

/* Kernel parameter accessor */
void SVMRegressionImplementation::setKernelParameter(const Point & kernelParameter)
{
  kernelParameter_ = kernelParameter;
}

Point SVMRegressionImplementation::getKernelParameter()
{
  return kernelParameter_;
}

/* Results accessor */
MetaModelResult SVMRegressionImplementation::getResult() const
{
  return result_;
}

/* Method save() stores the object through the StorageManager */
void SVMRegressionImplementation::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute( "tradeoffFactor_", tradeoffFactor_ );
  adv.saveAttribute( "kernelParameter_", kernelParameter_ );
  adv.saveAttribute( "kernel_", kernel_ );
  adv.saveAttribute( "result_", result_ );
}


/* Method load() reloads the object from the StorageManager */
void SVMRegressionImplementation::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute( "tradeoffFactor_", tradeoffFactor_ );
  adv.loadAttribute( "kernelParameter_", kernelParameter_ );
  adv.loadAttribute( "kernel_", kernel_ );
  adv.loadAttribute( "result_", result_ );
}


}

