// SWIG file SigmoidKernel.i

%{
#include "otsvm/SigmoidKernel.hxx"
%}

%include SigmoidKernel_doc.i

%copyctor OTSVM::SigmoidKernel;

%include otsvm/SigmoidKernel.hxx
