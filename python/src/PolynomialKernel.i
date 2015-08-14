// SWIG file PolynomialKernel.i
// @author schueller
// @date   2012-01-02 11:44:01 +0100 (Mon, 02 Jan 2012)
// Id      PolynomialKernel.i 2287 2012-01-02 10:44:01Z schueller

%{
#include "PolynomialKernel.hxx"
%}

%include PolynomialKernel.hxx
namespace OTSVM { %extend PolynomialKernel { PolynomialKernel(const PolynomialKernel & other) { return new OTSVM::PolynomialKernel(other); } } }
