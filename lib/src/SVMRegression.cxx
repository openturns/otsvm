//                                               -*- C++ -*-
/**
 *  @file  SVMRegression.cxx
 *  @brief Implementation of the rational kernel
 *
 *  (C) Copyright 2005-2012 EDF-EADS-Phimeca
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

#include "SVMRegression.hxx"


using namespace OT;

namespace OTSVM
{


CLASSNAMEINIT(SVMRegression);

/* Default constructor */
SVMRegression::SVMRegression(): OT::TypedInterfaceObject < SVMRegressionImplementation > ()
{

}

/* constructor with parameters */
SVMRegression::SVMRegression(const NumericalSample & dataIn,
                             const NumericalSample & dataOut,
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
void SVMRegression::setTradeoffFactor( NumericalPoint factor )
{
  copyOnWrite();
  getImplementation() -> setTradeoffFactor( factor );
}

NumericalPoint SVMRegression::getTradeoffFactor()
{
  return getImplementation() -> getTradeoffFactor();
}

/* Kernel parameter accessor */
void SVMRegression::setKernelParameter( NumericalPoint kernel )
{
  copyOnWrite();
  getImplementation() -> setKernelParameter( kernel );
}

NumericalPoint SVMRegression::getKernelParameter()
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

