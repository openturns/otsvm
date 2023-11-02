// SWIG file PolynomialKernel.i

%{
#include "otsvm/PolynomialKernel.hxx"
%}

%include PolynomialKernel_doc.i

%copyctor OTSVM::PolynomialKernel;

%include otsvm/PolynomialKernel.hxx
