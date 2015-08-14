// SWIG file NormalRBF.i
// @author schueller
// @date   2012-01-02 11:44:01 +0100 (Mon, 02 Jan 2012)
// Id      NormalRBF.i 2287 2012-01-02 10:44:01Z schueller

%{
#include "NormalRBF.hxx"
%}

%include NormalRBF.hxx
namespace OTSVM{ %extend NormalRBF { NormalRBF(const NormalRBF & other) { return new OTSVM::NormalRBF(other); } } }
