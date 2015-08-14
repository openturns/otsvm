// SWIG file LibSVMDriver.i
// Author : $LastChangedBy: dutka $
// Date : $LastChangedDate: 2008-10-15 17:56:07 +0200 (Wed, 15 Oct 2008) $
// Id : $Id: LibSVMDriver.i 972 2008-10-15 15:56:07Z dutka $

%{
#include "LibSVMClassification.hxx"
%}

%include LibSVMClassification.hxx
namespace OTSVM { %extend LibSVMClassification { LibSVMClassification(const LibSVMClassification & other) { return new OTSVM::LibSVMClassification(other); } } }
