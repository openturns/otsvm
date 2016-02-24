// SWIG file KMeansClustering.i

%{
#include "otsvm/KMeansClustering.hxx"
%}

%include otsvm/KMeansClustering.hxx
namespace OTSVM { %extend KMeansClustering { KMeansClustering(const KMeansClustering & other) { return new OTSVM::KMeansClustering(other); } } }
