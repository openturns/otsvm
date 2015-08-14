// SWIG file LibSVM.i
// Author : $LastChangedBy: dutka $
// Date : $LastChangedDate: 2008-10-15 17:56:07 +0200 (Wed, 15 Oct 2008) $
// Id : $Id: LibSVM.i 972 2008-10-15 15:56:07Z dutka $

%{
#include "LibSVM.hxx"
%}

%include LibSVM.hxx
namespace OTSVM { %extend LibSVM { LibSVM(const LibSVM & other) { return new OTSVM::LibSVM(other); } } }
