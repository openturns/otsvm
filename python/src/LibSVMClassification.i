// SWIG file LibSVMDriver.i

%{
#include "otsvm/LibSVMClassification.hxx"
%}

%include otsvm/LibSVMClassification.hxx
namespace OTSVM { %extend LibSVMClassification { LibSVMClassification(const LibSVMClassification & other) { return new OTSVM::LibSVMClassification(other); } } }
