// SWIG file RationalKernel.i

%{
#include "otsvm/RationalKernel.hxx"
%}

%include otsvm/RationalKernel.hxx
namespace OTSVM { %extend RationalKernel { RationalKernel(const RationalKernel & other) { return new OTSVM::RationalKernel(other); } } }
