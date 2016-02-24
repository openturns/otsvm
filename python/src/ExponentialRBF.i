// SWIG file ExponentialRBF.i

%{
#include "otsvm/ExponentialRBF.hxx"
%}

%include otsvm/ExponentialRBF.hxx
namespace OTSVM{ %extend ExponentialRBF { ExponentialRBF(const ExponentialRBF & other) { return new OTSVM::ExponentialRBF(other); } } }
