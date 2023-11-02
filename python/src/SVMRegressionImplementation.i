// SWIG file SVMRegressionImplementation.i

%{
#include "otsvm/SVMRegressionImplementation.hxx"
%}

%template(SVMRegressionImplementationdInterfaceObject)         OT::TypedInterfaceObject<OTSVM::SVMRegressionImplementation>;

%copyctor OTSVM::SVMRegressionImplementation;

%include otsvm/SVMRegressionImplementation.hxx
