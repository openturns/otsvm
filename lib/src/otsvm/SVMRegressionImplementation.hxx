//                                               -*- C++ -*-
/**
 *  @file  SVMRegressionImplementation.hxx
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

#ifndef OTSVM_SVMREGRESSIONIMPLEMENTATION
#define OTSVM_SVMREGRESSIONIMPLEMENTATION


#include <openturns/PersistentObject.hxx>
// #include "OTprivate.hxx"
#include "SVMKernel.hxx"
#include <openturns/MetaModelResult.hxx>


namespace OTSVM
{


class OTSVM_API SVMRegressionImplementation
  : public OT::PersistentObject
{

  CLASSNAME

public:

  /** Default constructor*/
  SVMRegressionImplementation();

  /** Virtual constructor */
  SVMRegressionImplementation * clone() const override;

  /** Method run */
  virtual void run();

  /** Results accessor*/
  virtual OT::MetaModelResult getResult() const;

  /** Tradeoff factor accessor */
  virtual void setTradeoffFactor(const OT::Point & factor);
  virtual OT::Point getTradeoffFactor();

  /** Kernel parameter accessor */
  virtual OT::Point getKernelParameter();
  virtual void setKernelParameter(const OT::Point & kernel);

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

protected:

  /* Tradeoff factor parameter*/
  OT::Point tradeoffFactor_;

  /* Kernel parameter */
  OT::Point kernelParameter_;

  /* Kernel on OpenTurns format*/
  SVMKernel kernel_;

  /* Results */
  OT::MetaModelResult result_;

private:


};




}


#endif

