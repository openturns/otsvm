// SWIG file LibSVMDriver.i

%{
#include "otsvm/LibSVMRegression.hxx"
%}

%include otsvm/LibSVMRegression.hxx

namespace OTSVM { %extend LibSVMRegression { LibSVMRegression(const LibSVMRegression & other) { return new OTSVM::LibSVMRegression(other); } } }
