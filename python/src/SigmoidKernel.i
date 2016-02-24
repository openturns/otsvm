// SWIG file SigmoidKernel.i

%{
#include "otsvm/SigmoidKernel.hxx"
%}

%include otsvm/SigmoidKernel.hxx

namespace OTSVM { %extend SigmoidKernel { SigmoidKernel(const SigmoidKernel & other) { return new OTSVM::SigmoidKernel(other); } } }
