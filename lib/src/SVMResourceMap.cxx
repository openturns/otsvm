//                                               -*- C++ -*-
/**
 *  @brief Custom ResourceMap keys
 *
 *  Copyright 2014-2022 Phimeca
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
  // openturns<1.15
#ifndef OPENTURNS_VERSION
#define AddAsScalar SetAsScalar
#define AddAsUnsignedInteger SetAsUnsignedInteger
#define AddAsBool SetAsBool
#define AddAsScalar SetAsScalar
#endif
  ResourceMap::AddAsUnsignedInteger("LibSVM-DegreePolynomialKernel", 3);
  ResourceMap::AddAsScalar("LibSVM-ConstantPolynomialKernel", 0);
  ResourceMap::AddAsUnsignedInteger("LibSVM-CacheSize", 100);
  ResourceMap::AddAsScalar("LibSVM-Epsilon", 1e-3);
  ResourceMap::AddAsUnsignedInteger("LibSVMRegression-NumberOfFolds", 3);
  ResourceMap::AddAsUnsignedInteger("LibSVM-Shrinking", 1);


}


}

