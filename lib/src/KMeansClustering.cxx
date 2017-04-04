#include "otsvm/KMeansClustering.hxx"
#include <openturns/Uniform.hxx>


using namespace OT;

namespace OTSVM
{

CLASSNAMEINIT(KMeansClustering);

KMeansClustering::KMeansClustering(): PersistentObject()
{
}

KMeansClustering* KMeansClustering::clone() const
{
  return new KMeansClustering(*this);
}

KMeansClustering::KMeansClustering(const Sample & dataIn, UnsignedInteger k)
  : PersistentObject()
  , k_(k)
  , inputSample_(dataIn)
{
}

void KMeansClustering::run()
{
  const UnsignedInteger dimension = inputSample_.getDimension();
  const UnsignedInteger size = inputSample_.getSize();
  UnsignedInteger tempj = 0;
  UnsignedInteger count = 0;
  UnsignedInteger change = 0;
  Point min;
  Point max;
  Point temp;
  Point temp2;
  Scalar distance = 0;
  Scalar distancemin = 0;
  Indices cluster( size );
  Sample means( k_ , dimension );

  min = inputSample_.getMin();
  max = inputSample_.getMax();

  for( UnsignedInteger i = 0 ; i < dimension ; i++ )
  {
    Uniform uniform(min[i], max[i]);
    for( UnsignedInteger j = 0 ; j < k_ ; j++)
    {
      means( j , i ) = uniform.getRealization()[0];
    }
  }

  while( change == 0 )
  {
    for( UnsignedInteger i = 0 ; i < size ; i++ )
    {
      distancemin = ( inputSample_[i] - means[0] ).norm();

      for( UnsignedInteger j = 1 ; j < k_ ; j++ )
      {
        distance = ( inputSample_[i] - means[j] ).norm();

        if( distance < distancemin )
        {
          distancemin = distance;
          tempj = j;
        }
        distance = 0;
      }
      cluster[i] = tempj;
      tempj = 0;
    }

    change = 0;

    for( UnsignedInteger i = 0 ; i < k_ ; i++ )
    {
      temp = means[i];
      means[i] *= 0;
      for( UnsignedInteger j = 0 ; j < size ; j++ )
      {
        if( cluster[j] == i )
        {
          means[i] += inputSample_[j];
          count ++;
        }
      }
      temp2 = means[i];

      if( count > 0 )
      {
        temp2 /= count ;
      }
      else
      {
        means[i] = temp;
      }

      means[i] = temp2;

      count = 0;
      if(temp == means[i])
      {
        change = 1;
      }
    }
  }

  cluster_ = cluster;
  means_ = means;

}

Indices KMeansClustering::getCluster()
{
  return cluster_;
}

Sample KMeansClustering::getMeans()
{
  return means_;
}

}


