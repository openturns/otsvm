"""
Regression
----------
"""

# %%
# The objective of this example is to create a SVM Regression algorithm in order to create a metamodel.
#
# otsvm enables to:
#
# - set lists of tradeoff factors and kernel parameter with the methods setTradeoffFactor, setKernelParameter.
# - select the kernel type in this list : Linear Kernel, Polynomial Kernel, Sigmoid Kernel, RBF kernel.
# - compute the algorithm on an input and output samples.
# - compute the algorithm on an experiment plane and a function.
# - compute the algorithm on an input and output samples and an isoprobabilistic distribution.
#
# We recommend for users to use the RBF Kernel (the Gaussian kernel).
# Moreover, it is important to understand that the selection of parameters (kernel parameter and tradeoff factor) is primary.
# If you don't know  what to take as parameters, you must take a wide range values,
# for example :math:`tradeoff \in \{10^-5,10^-3,10^-1...10^3 \}` :math:`kernel\ parameter \in \{10^-15, 10^-13...,10^3 \}`.
# Usually, the algorithm always converges, but this can take a long while, mostly if you have a lot of parameters to test.

# %%
import openturns as ot
import otsvm

# create a function, here we create the Sobol function
dimension = 3
meanTh = 1.0
a = ot.Point(dimension)
inputVariables = ot.Description(dimension)
formula = "1.0"
covTh = 1.0
for i in range(dimension):
    a[i] = 0.5 * i
    covTh = covTh * (1.0 + 1.0 / (3.0 * (1.0 + a[i]) ** 2))
    inputVariables[i] = "xi" + str(i)
    formula += (
        " * ((abs(4.0 * xi"
        + str(i)
        + " -2.0) + "
        + str(a[i])
        + ") / (1.0 + "
        + str(a[i])
        + "))"
    )
covTh = covTh - 1.0
model = ot.SymbolicFunction(inputVariables, ot.Description(1, formula))

# create the input distribution
ot.RandomGenerator.SetSeed(0)
marginals = ot.DistributionCollection(dimension)
for i in range(dimension):
    marginals[i] = ot.Uniform(0.0, 1.0)
distribution = ot.ComposedDistribution(marginals)

# create lists of kernel parameters and tradeoff factors
tradeoff = [0.01, 0.1, 1, 10, 100, 1000]
kernel = [0.001, 0.01, 0.1, 1, 10, 100]

# first example : create the problem with an input and output samples:
# first, we create samples
dataIn = distribution.getSample(250)
dataOut = model(dataIn)
# second, we create our svm regression object, we must select the third parameter
# in an enumerate in the list { NormalRBF, Linear, Sigmoid, Polynomial }
algo = otsvm.LibSVMRegression(dataIn, dataOut, otsvm.LibSVM.NormalRbf)
# third, we set kernel parameter and tradeoff factor
algo.setTradeoffFactor(tradeoff)
algo.setKernelParameter(kernel)
# Perform the algorithm
algo.run()
# Stream out the results
result = algo.getResult()
# get the residual error
residual = result.getResiduals()
# get the relative error
relativeError = result.getRelativeErrors()
print(f"residual={residual} error={relativeError}")

# second example : create the problem with an experiment plane:
# first, we create the plane
myExperiment = ot.MonteCarloExperiment(distribution, 250)
dataIn = myExperiment.generate()
dataOut = model(dataIn)
# second, we create our svm regression object, the first parameter is the
# function
algo2 = otsvm.LibSVMRegression(dataIn, dataOut, otsvm.LibSVM.Linear)
# third, we set kernel parameter and tradeoff factor
algo2.setTradeoffFactor(tradeoff)
algo2.setKernelParameter(kernel)
# Perform the algorithm
algo2.run()
# Stream out the results
result = algo2.getResult()
# get the residual error
residual = result.getResiduals()
# get the relative error
relativeError = result.getRelativeErrors()
print(f"residual={residual} error={relativeError}")

# third example is here to present you the SVMResourceMap class.
# Users can fix others parameters like the degree and the constant of the
# Polynomial Kernel,the cacheSize, the number of folds or the epsilon
# first, we create samples
dataIn = distribution.getSample(250)
dataOut = model(dataIn)
# second, we create our svm regression object
# here, we select the Polynomial Kernel but by default his degree is 3. We want a
# degree of 2
ot.ResourceMap.Set("LibSVM-DegreePolynomialKernel", "2")
# now the degree of the Polynomial kernel is 2
algo = otsvm.LibSVMRegression(dataIn, dataOut, otsvm.LibSVM.Polynomial)
# third, we set kernel parameter and tradeoff factor
algo.setTradeoffFactor(tradeoff)
algo.setKernelParameter(kernel)
# Perform the algorithm
# algo.run()
## Stream out the results
# result = algo.getResult()
# print(result)
## get the residual error
# residual = result.getResiduals()
## get the relative error
# relativeError = result.getRelativeErrors()
