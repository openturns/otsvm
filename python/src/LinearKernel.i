// SWIG file LibSVMDriver.i

%{
#include "otsvm/LinearKernel.hxx"
%}

%include otsvm/LinearKernel.hxx

namespace OTSVM { %extend LinearKernel { LinearKernel(const LinearKernel & other) { return new OTSVM::LinearKernel(other); } } }
