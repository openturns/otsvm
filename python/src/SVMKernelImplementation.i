// SWIG file SVMKernelImplementation.i
// @author schueller
// @date   2012-01-02 11:44:01 +0100 (Mon, 02 Jan 2012)
// Id      SVMKernelImplementation.i 2287 2012-01-02 10:44:01Z schueller

%{
#include "SVMKernelImplementation.hxx"
%}

%include SVMKernelImplementation.hxx
namespace OTSVM{ %extend SVMKernelImplementation { SVMKernelImplementation(const SVMKernelImplementation & other) { return new OTSVM::SVMKernelImplementation(other); } } }
