//                                               -*- C++ -*-
/**
 *  @file  SVMRegression.hxx
 *  @brief Implementation of the rational kernel
 *
 *  Copyright 2014-2020 Phimeca
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

#ifndef OTSVM_SVMREGRESSION_HXX
#define OTSVM_SVMREGRESSION_HXX


#include <openturns/TypedInterfaceObject.hxx>
#include "SVMRegressionImplementation.hxx"
#include "LibSVMRegression.hxx"

namespace OTSVM
{


class OTSVM_API SVMRegression : public OT::TypedInterfaceObject< SVMRegressionImplementation >
{
  CLASSNAME

public:

  typedef OT::Pointer< SVMRegressionImplementation > Implementation;

  /* Default constructor */
  SVMRegression();

  /* Constructor with parameters */
  SVMRegression(const SVMRegressionImplementation & reg);

  /* Constructor with parameters */
  SVMRegression(Implementation & p_implementation);

  /* constructor with parameters */
  SVMRegression(const OT::Sample & dataIn, const OT::Sample & dataOut, const LibSVM::KernelType kerneltype);

  /* Kernel parameter accessor */
  void setKernelParameter(const OT::Point & kernel);
  OT::Point getKernelParameter();

  /* Tradeoff factor accessor */
  void setTradeoffFactor(const OT::Point & factor);
  OT::Point getTradeoffFactor();

  /* Results accessor */
  OT::MetaModelResult getResult();

  /* Method run */
  void run();


};

}

#endif

