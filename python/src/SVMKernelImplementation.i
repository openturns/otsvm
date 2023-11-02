// SWIG file SVMKernelImplementation.i

%{
#include "otsvm/SVMKernelImplementation.hxx"
%}

%include SVMKernelImplementation_doc.i

%copyctor OTSVM::SVMKernelImplementation;

%include otsvm/SVMKernelImplementation.hxx
