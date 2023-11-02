// SWIG file KMeansClustering.i

%{
#include "otsvm/KMeansClustering.hxx"
%}

%include KMeansClustering_doc.i

%copyctor OTSVM::KMeansClustering;

%include otsvm/KMeansClustering.hxx
