// SWIG file LibSVMDriver.i

%{
#include "otsvm/SVMClassification.hxx"
%}

%include otsvm/SVMClassification.hxx
namespace OTSVM { %extend SVMClassification { SVMClassification(const SVMClassification & other) { return new OTSVM::SVMClassification(other); } } }
