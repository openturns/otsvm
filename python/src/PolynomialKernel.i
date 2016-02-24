// SWIG file PolynomialKernel.i

%{
#include "otsvm/PolynomialKernel.hxx"
%}

%include otsvm/PolynomialKernel.hxx
namespace OTSVM { %extend PolynomialKernel { PolynomialKernel(const PolynomialKernel & other) { return new OTSVM::PolynomialKernel(other); } } }
