// SWIG file SVMRegression.i

%{
#include "otsvm/SVMRegression.hxx"
%}

%include SVMRegression_doc.i

%copyctor OTSVM::SVMRegression;

%include otsvm/SVMRegression.hxx
