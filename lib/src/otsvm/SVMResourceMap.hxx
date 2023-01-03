//                                               -*- C++ -*-
/**
 *  @brief Custom ResourceMap keys
 *
 *  Copyright 2014-2023 Phimeca
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 *  Chih-Chung Chang and Chih-Jen Lin, LIBSVM : a library for support vector machines.
 *  ACM Transactions on  Intelligent Systems and Technology, 2:27:1--27:27, 2011. Software
 *  available at http://www.csie.ntu.edu.tw/~cjlin/libsvm
 *
 */
#ifndef OTSVM_RESOURCEMAP
#define OTSVM_RESOURCEMAP

#include <openturns/Object.hxx>
#include "otsvm/OTSVMprivate.hxx"

namespace OTSVM
{

class OTSVM_API SVMResourceMap
{

public:

  static void Initialize();

protected:

private:

};


struct OTSVM_API SVMResourceMap_init
{
  SVMResourceMap_init();
};
static SVMResourceMap_init __SVMResourceMap_initializer;

}
#endif

