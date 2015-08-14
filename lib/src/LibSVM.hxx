//                                               -*- C++ -*-
/**
 *  @file  LibSVM.hxx
 *  @brief LibSVM wrapper
 *
 *  Copyright 2005-2015 EDF-EADS-Phimeca
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

#ifndef OTSVM_LIBSVM
#define OTSVM_LIBSVM



#include "PersistentObject.hxx"
#include "svm.h"
#include "NumericalPoint.hxx"
#include "NumericalMathFunction.hxx"
#include "OTSVMprivate.hxx"

namespace OTSVM
{

class OTSVM_API LibSVM : public OT::PersistentObject
{
  CLASSNAME;

public:

  enum KernelType { Linear = LINEAR, Polynomial = POLY, Sigmoid = SIGMOID, NormalRbf = RBF };
  enum SvmType { CSupportClassification = C_SVC, EpsilonSupportRegression = EPSILON_SVR};

  /* Constructor */
  LibSVM();
  
  /* Virtual Constructor */
  virtual LibSVM * clone() const;

  /* Kernel parameter accessor */
  void setKernelParameter(const OT::NumericalScalar kernelParameter);

  /* Tradeoff factor accessor */
  void setTradeoffFactor(const OT::NumericalScalar tradeoffFactor);

  /* Number of support vectors accessor */
  OT::UnsignedInteger getNumberSupportVector();

  /* Libsvm Model accessor */
  void setModel(svm_model* model);

  /* Coefficient support vector accessor */
  OT::NumericalPoint getSupportVectorCoef();

  /* Epsilon parameter accessor */
  void setEpsilon(const OT::NumericalScalar epsilon);

  /* Kernel parameter accessor */
  void setGamma(const OT::NumericalScalar kernel);

  void setNu(const OT::NumericalScalar nu);

  void setP(const OT::NumericalScalar p);

  /* KernelType accessor */
  KernelType getKernelType();
  void setKernelType(const OT::UnsignedInteger kernelType);

  /* SvmType accessor */
  void setSvmType(const OT::UnsignedInteger svmType);

  /* Support vectors accessor */
  OT::NumericalSample getSupportVector( const OT::UnsignedInteger dim );

  /* Node accessor */
  svm_node* getNode(const OT::UnsignedInteger index);

  /* Constant accessor */
  OT::NumericalScalar getConstant();

  /* Gamma accessor */
  OT::NumericalScalar getGamma();

  /* Degree accessor */
  OT::UnsignedInteger getDegree();
  void setDegree(const OT::UnsignedInteger degree);

  /* Coefficient accessor */
  OT::NumericalScalar getPolynomialConstant();

  /* Output component accessor */
  OT::NumericalScalar getOutput(const OT::UnsignedInteger index);

  /* Perform Train method */
  void performTrain();

  /* Perform Error method */
  OT::NumericalScalar computeError();

  /* Perform Accuracy method */
  OT::NumericalScalar computeAccuracy();

  template <typename T> T * Allocation(const OT::UnsignedInteger size) const;

  void normalize(const OT::NumericalSample & data, OT::NumericalMathFunction & transformation, OT::NumericalMathFunction & inverseTransformation) const;

  /* Convert data to libsvm format */
  void convertData(const OT::NumericalSample & inputSample, const OT::NumericalSample & outputSample);

  OT::NumericalScalar runCrossValidation();
  
  /* Destroy the libsvm problem */
  void destroy();

  /* Destroy the libsvm model and nodes */
  void destroyModel();

  /* Associate a point with a class */
  OT::UnsignedInteger getLabel(const OT::NumericalPoint & vector) const;

  /* Grade a point as if it were associated to a class */
  OT::UnsignedInteger getLabelValues(const OT::NumericalPoint & vector, const OT::SignedInteger outC) const;

  OT::NumericalScalar predict(const OT::NumericalPoint & inP) const;

  void setWeight(const OT::NumericalPoint & weight, const OT::NumericalPoint & label);

  static void SVMLog(const char*);

  OT::NumericalMathFunction getInputTransformation() const;
  
protected:

  /* Libsvm parameter */
  svm_parameter parameter_;

  /* Libsvm problem */
  svm_problem problem_;

  /* Libsvm model */
  svm_model* p_model_;

  /* Libsvm node */
  svm_node* p_node_;

  /* data normalization */
  OT::NumericalMathFunction inputTransformation_;
  
};


}


#endif

