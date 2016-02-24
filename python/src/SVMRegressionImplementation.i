// SWIG file SVMRegressionImplementation.i

%{
#include "otsvm/SVMRegressionImplementation.hxx"
%}

%template(SVMRegressionImplementationdInterfaceObject)         OT::TypedInterfaceObject<OTSVM::SVMRegressionImplementation>;

%include otsvm/SVMRegressionImplementation.hxx
namespace OTSVM { %extend SVMRegressionImplementation { SVMRegressionImplementation(const SVMRegressionImplementation & other) { return new OTSVM::SVMRegressionImplementation(other); } } }
