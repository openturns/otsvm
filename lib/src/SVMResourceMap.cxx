//                                               -*- C++ -*-
/**
 *  @brief Custom ResourceMap keys
 *
 *  Copyright 2005-2016 EDF-EADS-Phimeca
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
#include <unistd.h>
#include <string.h>
#include <openturns/OTthread.hxx>
#include <openturns/OTconfig.hxx>
#include <openturns/OSS.hxx>
#include <openturns/Exception.hxx>
#include <openturns/Log.hxx>

using namespace OT;

namespace OTSVM
{

CLASSNAMEINIT(SVMResourceMap)

static pthread_mutex_t SVMResourceMap_InstanceMutex_;

SVMResourceMap_init::SVMResourceMap_init()
{
  static pthread_once_t SVMResourceMap_InstanceMutex_once = PTHREAD_ONCE_INIT;
  int rc = pthread_once( &SVMResourceMap_InstanceMutex_once, SVMResourceMap::Initialize );
  if (rc != 0)
  {
    perror("SVMResourceMap_init::SVMResourceMap_init once Initialization failed");
    exit(1);
  }
}

void SVMResourceMap::Initialize()
{
  pthread_mutexattr_t attr;
  pthread_mutexattr_init( &attr );
  pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
  int rc = pthread_mutex_init( &SVMResourceMap_InstanceMutex_, &attr );
  if (rc != 0)
  {
    perror("ResourceMap::Initialize mutex initialization failed");
    exit(1);
  }
  ResourceMap::SetAsUnsignedInteger("LibSVM-DegreePolynomialKernel", 3);
  ResourceMap::SetAsScalar("LibSVM-ConstantPolynomialKernel", 0);
  ResourceMap::SetAsUnsignedInteger("LibSVM-CacheSize", 100);
  ResourceMap::SetAsScalar("LibSVM-Epsilon", 1e-3);
  ResourceMap::SetAsUnsignedInteger("LibSVMRegression-NumberOfFolds", 3);
  ResourceMap::SetAsUnsignedInteger("LibSVM-Shrinking", 1);
  
  
}


}

