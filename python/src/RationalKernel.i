// SWIG file RationalKernel.i
// @author schueller
// @date   2012-01-02 11:44:01 +0100 (Mon, 02 Jan 2012)
// Id      RationalKernel.i 2287 2012-01-02 10:44:01Z schueller

%{
#include "RationalKernel.hxx"
%}

%include RationalKernel.hxx
namespace OTSVM { %extend RationalKernel { RationalKernel(const RationalKernel & other) { return new OTSVM::RationalKernel(other); } } }
