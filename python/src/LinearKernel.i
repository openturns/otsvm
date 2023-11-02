// SWIG file LinearKernel.i

%{
#include "otsvm/LinearKernel.hxx"
%}

%include LinearKernel_doc.i

%copyctor OTSVM::LinearKernel;

%include otsvm/LinearKernel.hxx
