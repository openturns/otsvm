// SWIG file SVMKernelImplementation.i

%{
#include "otsvm/SVMKernelImplementation.hxx"
%}

%include otsvm/SVMKernelImplementation.hxx
namespace OTSVM{ %extend SVMKernelImplementation { SVMKernelImplementation(const SVMKernelImplementation & other) { return new OTSVM::SVMKernelImplementation(other); } } }
