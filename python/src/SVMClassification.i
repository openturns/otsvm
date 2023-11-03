// SWIG file SVMClassification.i

%{
#include "otsvm/SVMClassification.hxx"
%}

%include SVMClassification_doc.i

%copyctor OTSVM::SVMClassification;

%include otsvm/SVMClassification.hxx
