//                                               -*- C++ -*-
/**
 *  @file  LibSVMRegression.hxx
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

#ifndef OTSVM_LIBSVMREGRESSION
#define OTSVM_LIBSVMREGRESSION


#include "SVMRegressionImplementation.hxx"
#include <openturns/Distribution.hxx>
#include <openturns/Function.hxx>
#include "LibSVM.hxx"
#include "SVMResourceMap.hxx"
#include <openturns/ResourceMap.hxx>
#include <openturns/Experiment.hxx>



namespace OTSVM
{


class OTSVM_API LibSVMRegression: public SVMRegressionImplementation
{
  CLASSNAME

public:

  /* default constructor */
  LibSVMRegression();

  /* constructor with parameters */
  LibSVMRegression(const OT::Sample & dataIn,
                   const OT::Sample & dataOut,
                   const LibSVM::KernelType kerneltype = LibSVM::NormalRbf);

  /* Virtual constructor*/
  LibSVMRegression * clone() const override;

  /* Method run */
  void run() override;

  OT::Sample getInputSample() const;
  OT::Sample getOutputSample() const;

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

protected:

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

