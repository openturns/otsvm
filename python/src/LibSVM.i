// SWIG file LibSVM.i

%{
#include "otsvm/LibSVM.hxx"
%}

%include otsvm/LibSVM.hxx
namespace OTSVM { %extend LibSVM { LibSVM(const LibSVM & other) { return new OTSVM::LibSVM(other); } } }
