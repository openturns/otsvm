// SWIG file ExponentialRBF.i
// @author schueller
// @date   2012-01-02 11:44:01 +0100 (Mon, 02 Jan 2012)
// Id      ExponentialRBF.i 2287 2012-01-02 10:44:01Z schueller

%{
#include "ExponentialRBF.hxx"
%}

%include ExponentialRBF.hxx
namespace OTSVM{ %extend ExponentialRBF { ExponentialRBF(const ExponentialRBF & other) { return new OTSVM::ExponentialRBF(other); } } }
