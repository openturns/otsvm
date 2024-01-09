//                                               -*- C++ -*-
/**
 *  @brief K-means clustering
 *
 *  Copyright 2014-2024 Phimeca
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
 */

#ifndef OTSVM_KMEANSCLUSTERING_HXX
#define OTSVM_KMEANSCLUSTERING_HXX


#include <openturns/Sample.hxx>
#include "otsvm/OTSVMprivate.hxx"

namespace OTSVM
{

class OTSVM_API KMeansClustering : public OT::PersistentObject
{
  CLASSNAME

public:

  KMeansClustering();

  KMeansClustering * clone() const override;

  KMeansClustering(const OT::Sample & dataIn, OT::UnsignedInteger k);

  virtual void run();

  OT::Indices getCluster();

  OT::Sample getMeans();

protected:

  OT::UnsignedInteger k_;

  OT::Sample inputSample_;

  OT::Indices cluster_;

  OT::Sample means_;
};

}

#endif
