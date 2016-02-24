// SWIG file LibSVMDriver.i

%{
#include "otsvm/SVMRegression.hxx"
%}

%include otsvm/SVMRegression.hxx
namespace OTSVM { %extend SVMRegression { SVMRegression(const SVMRegression & other) { return new OTSVM::SVMRegression(other); } } }
