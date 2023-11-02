// SWIG file LibSVM.i

%{
#include "otsvm/LibSVM.hxx"
%}

%copyctor OTSVM::LibSVM;

%include otsvm/LibSVM.hxx
