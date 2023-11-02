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
 */

#include "otsvm/SVMResourceMap.hxx"
#include <openturns/ResourceMap.hxx>
#include <mutex>

using namespace OT;

namespace OTSVM
{

SVMResourceMap_init::SVMResourceMap_init()
{
  static std::once_flag flag;
  std::call_once(flag, [&]()
  {
    ResourceMap::AddAsUnsignedInteger("LibSVM-DegreePolynomialKernel", 3);
    ResourceMap::AddAsScalar("LibSVM-ConstantPolynomialKernel", 0);
    ResourceMap::AddAsUnsignedInteger("LibSVM-CacheSize", 100);
    ResourceMap::AddAsScalar("LibSVM-Epsilon", 1e-3);
    ResourceMap::AddAsUnsignedInteger("LibSVMRegression-NumberOfFolds", 3);
    ResourceMap::AddAsUnsignedInteger("LibSVM-Shrinking", 1);
  });
}

}

