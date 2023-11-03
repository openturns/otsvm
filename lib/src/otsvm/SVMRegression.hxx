//                                               -*- C++ -*-
/**
 *  @brief Implementation of the rational kernel
 *
 *  Copyright 2014-2023 Phimeca
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

#ifndef OTSVM_LIBSVMREGRESSION
#define OTSVM_LIBSVMREGRESSION


#include <openturns/Distribution.hxx>
#include <openturns/MetaModelResult.hxx>
#include "otsvm/LibSVM.hxx"
#include "otsvm/OTSVM.hxx"
#include <openturns/ResourceMap.hxx>
#include <openturns/Experiment.hxx>

namespace OTSVM
{

class OTSVM_API SVMRegression: public OT::PersistentObject
{
  CLASSNAME

public:

  /* default constructor */
  SVMRegression();

  /* constructor with parameters */
  SVMRegression(const OT::Sample & dataIn,
                   const OT::Sample & dataOut,
                   const LibSVM::KernelType kerneltype = LibSVM::NormalRbf);

  /* Virtual constructor*/
  SVMRegression * clone() const override;

  /* Method run */
  virtual void run();

  OT::Sample getInputSample() const;
  OT::Sample getOutputSample() const;

  /** Tradeoff factor accessor */
  virtual void setTradeoffFactor(const OT::Point & factor);
  virtual OT::Point getTradeoffFactor();

  /** Kernel parameter accessor */
  virtual OT::Point getKernelParameter();
  virtual void setKernelParameter(const OT::Point & kernel);

  /** Results accessor*/
  virtual OT::MetaModelResult getResult() const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

protected:

  /* Tradeoff factor parameter*/
  OT::Point tradeoffFactor_;

  /* Kernel parameter */
  OT::Point kernelParameter_;

  /* Results */
  OT::MetaModelResult result_;
private:

  /* Libsvm model */
  LibSVM driver_;

  /* Input Sample */
  OT::Sample inputSample_;

  /* Output Sample */
  OT::Sample outputSample_;

};

}

#endif

