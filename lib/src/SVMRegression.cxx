//                                               -*- C++ -*-
/**
 *  @brief Regression
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

#include "otsvm/SVMRegression.hxx"


using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(SVMRegression)

/* Default constructor */
SVMRegression::SVMRegression(): OT::TypedInterfaceObject < SVMRegressionImplementation > ()
{

}

/* constructor with parameters */
SVMRegression::SVMRegression(const Sample & dataIn,
                             const Sample & dataOut,
                             const LibSVM::KernelType kerneltype)
: TypedInterfaceObject< SVMRegressionImplementation >(new LibSVMRegression(dataIn, dataOut, kerneltype))
{
}

/* Constructor with parameters */
SVMRegression::SVMRegression( const SVMRegressionImplementation & reg ): TypedInterfaceObject< SVMRegressionImplementation >( reg.clone() )
{
}

/* Constructor with parameters */
SVMRegression::SVMRegression( Implementation & p_implementation ): TypedInterfaceObject< SVMRegressionImplementation >( p_implementation )
{
}

/* Tradeoff factor accessor */
void SVMRegression::setTradeoffFactor(const Point & factor)
{
  copyOnWrite();
  getImplementation() -> setTradeoffFactor(factor);
}

Point SVMRegression::getTradeoffFactor()
{
  return getImplementation() -> getTradeoffFactor();
}

/* Kernel parameter accessor */
void SVMRegression::setKernelParameter(const Point & kernel)
{
  copyOnWrite();
  getImplementation() -> setKernelParameter(kernel);
}

Point SVMRegression::getKernelParameter()
{
  return getImplementation() -> getKernelParameter();
}

/* Results accessor */
MetaModelResult SVMRegression::getResult()
{
  return getImplementation() -> getResult();
}

/* Method run */
void SVMRegression::run()
{
  getImplementation() ->run();
}


}

