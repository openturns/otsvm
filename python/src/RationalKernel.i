// SWIG file RationalKernel.i

%{
#include "otsvm/RationalKernel.hxx"
%}

%include RationalKernel_doc.i

%copyctor OTSVM::RationalKernel;

%include otsvm/RationalKernel.hxx
