// SWIG file LibSVMClassification.i

%{
#include "otsvm/LibSVMClassification.hxx"
%}

%include LibSVMClassification_doc.i

%copyctor OTSVM::LibSVMClassification;

%include otsvm/LibSVMClassification.hxx
