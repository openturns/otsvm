// SWIG file LibSVM.i

%{
#include "otsvm/LibSVM.hxx"
%}

%include LibSVM_doc.i

%copyctor OTSVM::LibSVM;

%include otsvm/LibSVM.hxx
