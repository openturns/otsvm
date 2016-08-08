//                                               -*- C++ -*-
/**
 *  @file  LibSVMRegression.hxx
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

#ifndef OTSVM_LIBSVMREGRESSION
#define OTSVM_LIBSVMREGRESSION


#include "SVMRegressionImplementation.hxx"
#include <openturns/Distribution.hxx>
#include <openturns/NumericalMathFunction.hxx>
#include "LibSVM.hxx"
#include "SVMResourceMap.hxx"
#include <openturns/ResourceMap.hxx>
#include <openturns/Experiment.hxx>



namespace OTSVM
{


class OTSVM_API LibSVMRegression: public SVMRegressionImplementation
{
  CLASSNAME;

public:

  /* default constructor */
  LibSVMRegression();

  /* constructor with parameters */
  LibSVMRegression(const OT::NumericalSample & dataIn,
                   const OT::NumericalSample & dataOut,
                   const LibSVM::KernelType kerneltype = LibSVM::NormalRbf);

  /* Virtual constructor*/
  virtual LibSVMRegression * clone() const;

  /* Method run */
  virtual void run();

  OT::NumericalSample getInputSample() const;
  OT::NumericalSample getOutputSample() const;
  
  /** Method save() stores the object through the StorageManager */
  virtual void save(OT::Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(OT::Advocate & adv);

protected:

private:

  /* Libsvm model */
  LibSVM driver_;

  /* Input Sample */
  OT::NumericalSample inputSample_;

  /* Output Sample */
  OT::NumericalSample outputSample_;

};

}

#endif

