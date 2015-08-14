//                                               -*- C++ -*-
/**
 *  @file  SVMRegressionImplementation.hxx
 *  @brief Implementation of the rational kernel
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

#ifndef OTSVM_SVMREGRESSIONIMPLEMENTATION
#define OTSVM_SVMREGRESSIONIMPLEMENTATION


#include "PersistentObject.hxx"
#include "OTprivate.hxx"
#include "NumericalPoint.hxx"
#include "SVMKernel.hxx"
#include "svm.h"
#include "MetaModelResult.hxx"


namespace OTSVM
{


class OTSVM_API SVMRegressionImplementation: public OT::PersistentObject
{

  CLASSNAME;

public:

  /* Default constructor*/
  SVMRegressionImplementation();

  /* Virtual constructor */
  virtual SVMRegressionImplementation * clone() const;



  /* Method run */
  virtual void run();

  /* Results accessor*/
  virtual OT::MetaModelResult getResult() const;

  /* Tradeoff factor accessor */
  virtual void setTradeoffFactor(const OT::NumericalPoint & factor);
  virtual OT::NumericalPoint getTradeoffFactor();

  /* Kernel parameter accessor */
  virtual OT::NumericalPoint getKernelParameter();
  virtual void setKernelParameter(const OT::NumericalPoint & kernel);

  /** Method save() stores the object through the StorageManager */
//     virtual void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
//     virtual void load(Advocate & adv);

protected:

  /* Tradeoff factor parameter*/
  OT::NumericalPoint tradeoffFactor_;

  /* Kernel parameter */
  OT::NumericalPoint kernelParameter_;

  /* Kernel on OpenTurns format*/
  SVMKernel kernel_;

  /* Results */
  OT::MetaModelResult result_;

private:


};




}


#endif

