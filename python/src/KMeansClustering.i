// SWIG file KMeansClustering.i
// Author : $LastChangedBy: dutka $
// Date : $LastChangedDate: 2008-10-15 17:56:07 +0200 (Wed, 15 Oct 2008) $
// Id : $Id: KMeansClustering.i 972 2008-10-15 15:56:07Z dutka $

%{
#include "KMeansClustering.hxx"
%}

%include KMeansClustering.hxx
namespace OTSVM { %extend KMeansClustering { KMeansClustering(const KMeansClustering & other) { return new OTSVM::KMeansClustering(other); } } }
