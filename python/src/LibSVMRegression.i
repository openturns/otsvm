// SWIG file LibSVMRegression.i

%{
#include "otsvm/LibSVMRegression.hxx"
%}

%include LibSVMRegression_doc.i

%copyctor OTSVM::LibSVMRegression;

%include otsvm/LibSVMRegression.hxx
