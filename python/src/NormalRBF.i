// SWIG file NormalRBF.i

%{
#include "otsvm/NormalRBF.hxx"
%}

%include otsvm/NormalRBF.hxx
namespace OTSVM{ %extend NormalRBF { NormalRBF(const NormalRBF & other) { return new OTSVM::NormalRBF(other); } } }
