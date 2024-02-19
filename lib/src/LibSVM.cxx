//             -*- C++ -*-
/**
 *  @brief LibSVM wrapper
 *
 *  Copyright 2014-2024 Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "otsvm/LibSVM.hxx"
#include "otsvm/NormalRBF.hxx"
#include "otsvm/PolynomialKernel.hxx"
#include "otsvm/SigmoidKernel.hxx"
#include "otsvm/LinearKernel.hxx"

#include <openturns/Log.hxx>
#include <openturns/SpecFunc.hxx>
#include <openturns/LinearFunction.hxx>

#include "svm.h"


using namespace OT;

namespace OTSVM
{

class LibSVMImplementation
{
public:
  /* Libsvm parameter */
  svm_parameter parameter_;

  /* Libsvm problem */
  svm_problem problem_;

  /* Libsvm model */
  svm_model* p_model_ = nullptr;

  /* Libsvm node */
  svm_node* p_node_ = nullptr;
};


CLASSNAMEINIT(LibSVM)

void LibSVM::SVMLog(const char * msg)
{
  LOGDEBUG(OSS() << "LibSVM: " << msg);
}

/* Constructor */
LibSVM::LibSVM()
  : PersistentObject()
{
  p_implementation_ = new LibSVMImplementation;
  
  // default parameters
  p_implementation_->parameter_.svm_type = C_SVC;  //-s svm_type : set type of SVM (default 0) 0=C-SVC, 1=nu-SVC, 2=one-class SVM, 3=epsilon-SVR, 4=nu-SVR
  p_implementation_->parameter_.kernel_type = RBF; //-t kernel_type : set type of kernel function (default 2) 0=linear: u'*v, 1=polynomial: (gamma*u'*v + coef0)^degree, 2=radial basis function: exp(-gamma*|u-v|^2), 3=sigmoid: tanh(gamma*u'*v + coef0), 4=precomputed kernel (kernel values in training_set_file)
  p_implementation_->parameter_.degree = 3;        //-d degree : set degree in kernel function (default 3)
  p_implementation_->parameter_.gamma = 0.0;        //-g gamma : set gamma in kernel function (default 1/k)
  p_implementation_->parameter_.coef0 = 0.0;         //-r coef0 : set coef0 in kernel function (default 0)
  p_implementation_->parameter_.nu = 0.5;          //-n nu : set the parameter nu of nu-SVC, one-class SVM, and nu-SVR (default 0.5)
  p_implementation_->parameter_.cache_size = 100;  //-m cachesize : set cache memory size in MB (default 100)
  p_implementation_->parameter_.C = 1.0;             //-c cost : set the parameter C of C-SVC, epsilon-SVR, and nu-SVR (default 1)
  p_implementation_->parameter_.eps = 1e-3;        //-e epsilon : set tolerance of termination criterion (default 0.001)
  p_implementation_->parameter_.p = 0.1;           //-p epsilon : set the epsilon in loss function of epsilon-SVR (default 0.1)
  p_implementation_->parameter_.shrinking = 1;     //-h shrinking: whether to use the shrinking heuristics, 0 or 1 (default 1)
  p_implementation_->parameter_.probability = 0;   //-b probability_estimates: whether to train a SVC or SVR model for probability estimates, 0 or 1 (default 0)
  p_implementation_->parameter_.nr_weight = 0;     //-wi weight: set the parameter C of class i to weight*C, for C-SVC (default 1)
  p_implementation_->parameter_.weight_label = 0;
  p_implementation_->parameter_.weight = 0;


  p_implementation_->parameter_.degree = ResourceMap::GetAsUnsignedInteger( "LibSVM-DegreePolynomialKernel" );
  p_implementation_->parameter_.coef0 = ResourceMap::GetAsScalar( "LibSVM-ConstantPolynomialKernel" );
  p_implementation_->parameter_.cache_size = ResourceMap::GetAsUnsignedInteger( "LibSVM-CacheSize" );
  p_implementation_->parameter_.shrinking = ResourceMap::GetAsUnsignedInteger( "LibSVM-Shrinking" );

  p_implementation_->parameter_.eps = ResourceMap::GetAsScalar("LibSVM-Epsilon");
  svm_set_print_string_function(&SVMLog);

  p_implementation_->problem_.x = 0;
  p_implementation_->problem_.y = 0;

}


/* Virtual Constructor */
LibSVM * LibSVM::clone() const
{
  return new LibSVM(*this);
}

/* Kernel parameter accessor */
void LibSVM::setGamma(const Scalar gamma)
{
  p_implementation_->parameter_.gamma = gamma;
}

/* Tradeoff factor accessor */
void LibSVM::setTradeoffFactor(const Scalar tradeoffFactor)
{
  p_implementation_->parameter_.C = tradeoffFactor;
}

/* Number of support vectors accessor */
UnsignedInteger LibSVM::getNumberSupportVector()
{
  return p_implementation_->p_model_->l;
}

/* Libsvm model accessor */
void LibSVM::setModel(svm_model* model)
{
  p_implementation_->p_model_ = model;
}

SVMKernel LibSVM::getKernel() const
{
  switch(getKernelType())
  {
    case Polynomial:
      return PolynomialKernel(getDegree(), getGamma(), getPolynomialConstant());
      break;
    case NormalRbf:
      return NormalRBF(1.0 / (std::sqrt(2.0 * getGamma())));
      break;
    case Sigmoid:
      return SigmoidKernel(getGamma(), getConstant());
      break;
    case Linear:
      return LinearKernel();
      break;
    default:
      throw InvalidArgumentException(HERE) << "LibSVM: unknown kernel type";
  }
}

/* Support vectors accessor */
Sample LibSVM::getSupportVector(const UnsignedInteger dim)
{
  Sample res( getNumberSupportVector(), dim );


  for ( UnsignedInteger l = 0 ; l < getNumberSupportVector() ; l++ )
  {
    Point node(dim);
    UnsignedInteger j = 0;
    svm_node* i = getNode(l);
    while(i -> index != -1)
    {
      node[j] = i -> value;
      ++ i;
      j ++;
    }
    res[l] = node;
  }

  return res;
}

/* Constant accessor */
Scalar LibSVM:: getConstant() const
{
  return -p_implementation_->p_model_->rho[0];
}

/* Epsilon parameter accessor */
void LibSVM::setEpsilon(const Scalar epsilon)
{
  p_implementation_->parameter_.eps = epsilon;
}

void LibSVM::setNu(const OT::Scalar nu)
{
  p_implementation_->parameter_.nu = nu;
}

void LibSVM::setP(const OT::Scalar p)
{
  p_implementation_->parameter_.p = p;
}


/* Coefficient support vector accessor */
Point LibSVM::getSupportVectorCoef( )
{
  Point res(getNumberSupportVector());
  for(UnsignedInteger j = 0 ; j < getNumberSupportVector(); ++ j)
    res[j] = p_implementation_->p_model_->sv_coef[0][j];
  return res;
}

/* KernelType accessor */
LibSVM::KernelType LibSVM::getKernelType() const
{
  switch (p_implementation_->parameter_.kernel_type)
  {
    case LINEAR:
      return Linear;
    case POLY:
      return Polynomial;
    case RBF:
      return NormalRbf;
    case SIGMOID:
      return Sigmoid;
    default:
      throw InvalidArgumentException(HERE) << "LibSVM: kernel type not available.";
  }
}

void LibSVM::setKernelType(const UnsignedInteger kernelType)
{
  switch (kernelType)
  {
    case Linear:
    {
      p_implementation_->parameter_.kernel_type = LINEAR;
      break;
    }
    case Polynomial:
    {
      p_implementation_->parameter_.kernel_type = POLY;
      break;
    }
    case NormalRbf:
    {
      p_implementation_->parameter_.kernel_type = RBF;
      break;
    }
    case Sigmoid:
    {
      p_implementation_->parameter_.kernel_type = SIGMOID;
      break;
    }
    default:
      throw InvalidArgumentException(HERE) << "LibSVM: kernel type not available.";
  }
}

/* Node accessor */
svm_node* LibSVM::getNode(const UnsignedInteger index)
{
  return p_implementation_->p_model_ -> SV[index];
}

/* SvmType accessor */
void LibSVM::setSvmType(const UnsignedInteger svmType)
{
  switch (svmType)
  {
    case CSupportClassification:
    {
      p_implementation_->parameter_.svm_type = C_SVC;
      break;
    }
    case EpsilonSupportRegression:
    {
      p_implementation_->parameter_.svm_type = EPSILON_SVR;
      break;
    }
    default:
      throw InvalidArgumentException(HERE) << "LibSVM: svmType not available.";
  }
}

/*kernelParameter accessor */
void LibSVM::setKernelParameter(const Scalar kernelParameter)
{
  if (fabs(kernelParameter) < 1e-25)
  {
    throw InvalidArgumentException(HERE) << "Kernel parameter too small: " << kernelParameter;
  }
  p_implementation_->parameter_.gamma = 1.0 / (2.0 * kernelParameter * kernelParameter);
}

/* Gamma accessor */
Scalar LibSVM::getGamma() const
{
  return p_implementation_->parameter_.gamma;
}

/* Degree accessor */
UnsignedInteger LibSVM::getDegree() const
{
  return p_implementation_->parameter_.degree;
}
void LibSVM::setDegree(const UnsignedInteger Degree)
{
  p_implementation_->parameter_.degree = Degree;
}

/* Coefficient accessor */
Scalar LibSVM::getPolynomialConstant() const
{
  return p_implementation_->parameter_.coef0;
}

/* Output component accessor */
Scalar LibSVM::getOutput(const UnsignedInteger index)
{
  return p_implementation_->problem_.y[index];
}


/* Perform train  */
void LibSVM::performTrain()
{
  setModel(svm_train( &p_implementation_->problem_, &p_implementation_->parameter_ ));
}


Scalar LibSVM::runCrossValidation()
{
  UnsignedInteger size = p_implementation_->problem_.l;
  Point target(size);

  // launch validation
  srand (1);
  const UnsignedInteger nFolds = ResourceMap::GetAsUnsignedInteger("SVMRegression-NumberOfFolds");
  svm_cross_validation(&p_implementation_->problem_, &p_implementation_->parameter_, nFolds, const_cast<double *>(target.data()));

  Scalar totalError = 0.0;
  for (UnsignedInteger i = 0; i < size; ++ i)
  {
    totalError += (p_implementation_->problem_.y[i] - target[i]) * (p_implementation_->problem_.y[i] - target[i]) / size;
  }

  LOGDEBUG(OSS() << "LibSVM::runCrossValidation gamma=" << p_implementation_->parameter_.gamma << " C=" << p_implementation_->parameter_.C << " err=" << totalError);

  return totalError;
}


Scalar LibSVM::computeError()
{
  Scalar totalerror = 0;

  for ( UnsignedInteger k = 0 ; k < (UnsignedInteger)p_implementation_->problem_.l ; k++ )
  {
    const Scalar slack = p_implementation_->problem_.y[k] - svm_predict(p_implementation_->p_model_, p_implementation_->problem_.x[k]);
    totalerror += slack * slack;
  }
  totalerror = std::sqrt(totalerror) / p_implementation_->problem_.l;

  return totalerror;
}

Scalar LibSVM::computeAccuracy()
{
  UnsignedInteger totalerror = 0;
  for (UnsignedInteger k = 0 ; k < (UnsignedInteger)p_implementation_->problem_.l ; ++ k)
    if (p_implementation_->problem_.y[k] != svm_predict(p_implementation_->p_model_, p_implementation_->problem_.x[k]))
      ++ totalerror;
  return totalerror;
}

template <typename T> T * LibSVM::Allocation(const UnsignedInteger size) const
{
  return (T *)malloc( size * sizeof(T) );
}


/* normalize the sample */
void LibSVM::normalize(const Sample &data, Function & transformation, Function & inverseTransformation) const
{
  UnsignedInteger dimension = data.getDimension();
  Point mean(data.computeMean());
  Point stdev(data.computeStandardDeviation());
  SquareMatrix linear(dimension);
  SquareMatrix linearInv(dimension);
  for (UnsignedInteger j = 0; j < dimension; ++ j)
  {
    linearInv(j, j) = 1.0;
    linear(j, j) = 1.0;
    if (fabs(stdev[j]) > SpecFunc::MinScalar)
    {
      linear(j, j) /= stdev[j];
      linearInv(j, j) *= stdev[j];
    }
  }
  Point zero(dimension);
  transformation = LinearFunction(mean, zero, linear);
  inverseTransformation = LinearFunction(zero, mean, linearInv);
}


OT::Function LibSVM::getInputTransformation() const
{
  return inputTransformation_;
}



/* Create the problem with libsvm format */
void LibSVM::convertData(const Sample & inputSample, const Sample & outputSample)
{
  const UnsignedInteger size = inputSample.getSize();
  const UnsignedInteger inputDimension = inputSample.getDimension();

  Function inputInverseTransformation;
  normalize(inputSample, inputTransformation_, inputInverseTransformation);

  // write in/out into problem data
  p_implementation_->problem_.l = size;
  p_implementation_->problem_.y = Allocation<double>(size);
  p_implementation_->problem_.x = Allocation<struct svm_node *>(size);
  p_implementation_->p_node_ = Allocation<struct svm_node>(size * (inputDimension + 1));
  for (UnsignedInteger j = 0; j < size; ++ j)
  {
    p_implementation_->problem_.x[j] = & p_implementation_->p_node_[j * (inputDimension + 1)];
    p_implementation_->problem_.y[j] = outputSample[j][0];
    for (UnsignedInteger i = 0; i < inputDimension; ++i)
    {
      p_implementation_->p_node_[j * (inputDimension + 1) + i].index = i + 1;
      p_implementation_->p_node_[j * (inputDimension + 1) + i].value = inputTransformation_(inputSample[j])[i];
    }
    p_implementation_->p_node_[j * (inputDimension + 1) + inputDimension].index = - 1;
  }
}

void LibSVM::destroy()
{
  if (p_implementation_->problem_.x)
  {
    free(p_implementation_->problem_.x);
    p_implementation_->problem_.x = 0;
  }
  if (p_implementation_->problem_.y)
  {
    free(p_implementation_->problem_.y);
    p_implementation_->problem_.y = 0;
  }
}

void LibSVM::destroyModel()
{
  if (p_implementation_->p_model_)
  {
    svm_free_model_content(p_implementation_->p_model_);
    p_implementation_->p_model_ = 0;
  }
  if (p_implementation_->p_node_)
  {
    free(p_implementation_->p_node_);
    p_implementation_->p_node_ = 0;
  }
}

UnsignedInteger LibSVM::getLabel(const Point & vector) const
{
  const UnsignedInteger size = vector.getSize();
  svm_problem prob;
  svm_node* node;

  prob.x = Allocation<struct svm_node *>(1);
  node = Allocation<struct svm_node>(size + 1);

  prob.x[0] = & node[0];
  for(UnsignedInteger j = 0; j < size; j++)
  {
    node[j].index = j + 1;
    node[j].value = inputTransformation_(vector)[j];
  }
  node[size].index = -1;

  UnsignedInteger res = svm_predict(p_implementation_->p_model_, prob.x[0]);

  free(prob.x);
  free(node);

  return res;

}

UnsignedInteger LibSVM::getLabelValues(const Point & vector, const SignedInteger outC) const
{
  const UnsignedInteger size = vector.getSize();
  svm_problem prob;
  svm_node* node;

  prob.x = Allocation<struct svm_node *>(1);
  node = Allocation<struct svm_node>(size + 1);

  prob.x[0] = & node[0];
  for(UnsignedInteger j = 0; j < size; j++)
  {
    node[j].index = j + 1;
    node[j].value = inputTransformation_(vector)[j];
  }
  node[size].index = -1;

  const UnsignedInteger numberclass = svm_get_nr_class(p_implementation_->p_model_);
  double *dec_values = Allocation < double > ( numberclass * ( numberclass - 1 ) / 2);
  Point vote(numberclass);
  UnsignedInteger pos = 0;

  svm_predict_values(p_implementation_->p_model_, prob.x[0], dec_values);

  for (UnsignedInteger i = 0; i < numberclass; ++ i)
  {
    for(UnsignedInteger j = i + 1; j < numberclass; ++ j)
    {
      if(dec_values[pos++] > 0)
        ++ vote[i];
      else
        ++ vote[j];
    }
  }

  UnsignedInteger res = 0;
  for (UnsignedInteger i = 0; i < numberclass; ++ i)
    if((SignedInteger)p_implementation_->p_model_->label[i] == outC)
      res = i;

  free(dec_values);
  return vote[res];
}


Scalar LibSVM::predict(const Point & inP) const
{
  UnsignedInteger inputDimension = inP.getDimension();
  struct svm_node *x = Allocation<struct svm_node>(inputDimension + 1);
  for (UnsignedInteger i = 0; i < inputDimension; ++ i)
  {
    x[i].index = i + 1;
    x[i].value = inputTransformation_(inP)[i];
  }
  x[inputDimension].index = -1;

  double res = 0.0;
  if (svm_get_svm_type(p_implementation_->p_model_) == ONE_CLASS ||
      svm_get_svm_type(p_implementation_->p_model_) == EPSILON_SVR ||
      svm_get_svm_type(p_implementation_->p_model_) == NU_SVR)
  {
    svm_predict_values(p_implementation_->p_model_, x, &res);

    if (svm_get_svm_type(p_implementation_->p_model_) == ONE_CLASS)
      res = (res > 0) ? 1 : -1;
  }
  else
  {
    // multiclass
    int i;
    int nr_class = svm_get_nr_class(p_implementation_->p_model_);
    std::vector<double>dec_values(nr_class * (nr_class - 1) / 2);
    svm_predict_values(p_implementation_->p_model_, x, dec_values.data());

    std::vector<int> vote(nr_class);
    for (i = 0; i < nr_class; i++)
      vote[i] = 0;
    int pos = 0;
    for (i = 0; i < nr_class; i++)
      for (int j = i + 1; j < nr_class; j++)
      {
        if (dec_values[pos++] > 0)
          ++vote[i];
        else
          ++vote[j];
      }

    int vote_max_idx = 0;
    for (i = 1; i < nr_class; i++)
      if (vote[i] > vote[vote_max_idx])
        vote_max_idx = i;

    std::vector<int> labels(nr_class);
    svm_get_labels(p_implementation_->p_model_, labels.data());
    int label = labels[vote_max_idx];

    res = (double)label;
    res = dec_values[0] * labels[0];
  }
  free(x);
  return res;
}


void LibSVM::setWeight(const Point & weight, const Point & label)
{
  const UnsignedInteger size = weight.getSize();

  p_implementation_->parameter_.nr_weight = size;
  p_implementation_->parameter_.weight = Allocation < double > ( size );
  p_implementation_->parameter_.weight_label = Allocation < int > ( size );

  for(UnsignedInteger i = 0; i < size; i ++)
  {
    p_implementation_->parameter_.weight[i] = weight[i];
    p_implementation_->parameter_.weight_label[i] = label[i];
  }
}


}

