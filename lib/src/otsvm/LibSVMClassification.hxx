/**
 *  This is the class which makes the link between LibSVM and OpenTURNS for Classification.
 *
 *  Copyright 2014-2023 Phimeca
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

#ifndef OTSVM_LIBSVMCLASSIFICATION_HXX
#define OTSVM_LIBSVMCLASSIFICATION_HXX

#include "LibSVM.hxx"
#include <openturns/ClassifierImplementation.hxx>

namespace OTSVM
{

class OTSVM_API LibSVMClassification: public OT::ClassifierImplementation
{
  CLASSNAME

public:

  /**
  *Default constructor
  */
  LibSVMClassification();

  /**
  *Constructor with parameters.
  * @param  dataIn a Sample, an OpenTURNS object which is the input Sample.
  * @param  outClasses an Indices, an OpenTURNS object which is the label for each vector.
  */
  LibSVMClassification(const OT::Sample & dataIn,
                       const OT::Indices & outClasses);

  /**
  *Virtual constructor
  */
  LibSVMClassification * clone() const override;

  /* Accuracy accessor */
  OT::Scalar getAccuracy();

  /**
  *Associate a point with a class
  *@param vector a Point, an Openturns object.
  */
  OT::UnsignedInteger classify(const OT::Point & vector) const override;

  /* String converter */
  OT::String __repr__() const override;

  /* Grade a point as if it were associated to a class */
  OT::Scalar grade(const OT::Point & inP, const OT::UnsignedInteger outC) const override;
  OT::Scalar predict(const OT::Point & inP) const;

  void runKMeans(const OT::UnsignedInteger k);

  void setKernelType(const LibSVM::KernelType & kerneltype);
  void setTradeoffFactor(const OT::Point & trade);
  void setKernelParameter( const OT::Point & kernel);
  void setWeight(const OT::Point & weight);

  /** Method run */
  virtual void run();

  /** Method save() stores the object through the StorageManager */
  void save(OT::Advocate & adv) const override;

  /** Method load() reloads the object from the StorageManager */
  void load(OT::Advocate & adv) override;

protected:


private:

  /* Libsvm model */
  LibSVM driver_;

  /* Accuracy value */
  OT::Scalar accuracy_;

  /* Tradeoff factor parameter*/
  OT::Point tradeoffFactor_;

  /* Kernel parameter */
  OT::Point kernelParameter_;

};

}

#endif

