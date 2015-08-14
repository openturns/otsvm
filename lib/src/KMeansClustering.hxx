#ifndef KMEANSCLUSTERING_HXX
#define KMEANSCLUSTERING_HXX

#include "PersistentObject.hxx"
#include "NumericalPoint.hxx"
#include "NumericalSample.hxx"
#include "OTSVMprivate.hxx"

namespace OTSVM
{

class OTSVM_API KMeansClustering : public OT::PersistentObject
{
  CLASSNAME;

public:

  KMeansClustering();

  virtual KMeansClustering * clone() const;

  KMeansClustering(const OT::NumericalSample & dataIn, OT::UnsignedInteger k);

  virtual void run();

  OT::Indices getCluster();

  OT::NumericalSample getMeans();

protected:

  OT::UnsignedInteger k_;

  OT::NumericalSample inputSample_;

  OT::Indices cluster_;

  OT::NumericalSample means_;
};

}

#endif
