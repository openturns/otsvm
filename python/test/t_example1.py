


#create a function, here we create the Sobol function
dimension = 3
meanTh = 1.0
a = Point(dimension)
inputVariables = Description(dimension)
outputVariables = Description(1)
outputVariables[0] = "y"
formula = Description(1)
formula[0] = "1.0"
covTh = 1.0
for i in range(dimension):
    a[i] = 0.5*i
    covTh = covTh * (1.0 + 1.0 / (3.0 * (1.0 + a[i])**2))
    inputVariables[i] = "xi" + str(i)
    formula[0] = formula[0] + " * ((abs(4.0 * xi" +str(i) + " -2.0) + " + 
    str(a[i]) + ") / (1.0 + " + str(a[i]) + "))"
covTh = covTh -1.0
model = Function(inputVariables, outputVariables, formula)

#create the input distribution
RandomGenerator.SetSeed(0)
marginals = DistributionCollection(dimension)
for i in range(dimension):
  marginals[i] = Uniform(0.0, 1.0)
distribution = ComposedDistribution(marginals)

#create lists of kernel parameters and tradeoff factors
tradeoff = [0.01,0.1,1,10,100,1000]
kernel = [0.001,0.01,0.1,1,10,100]

#first example : create the problem with an input and output samples:
#first, we create samples
dataIn = distribution.getSample(250)
dataOut = model(dataIn)
#second, we create our svm regression object, we must select the third parameter 
#in an enumerate in the list { NormalRBF, Linear, Sigmoid, Polynomial }
Regression = SVMRegression(dataIn, dataOut, LibSVM.NormalRBF)
#third, we set kernel parameter and tradeoff factor
Regression.setTradeoffFactor(tradeoff)
Regression.setKernelParameter(kernel)
# Perform the algorithm
Regression.run()
# Stream out the results
SVMRegressionResult = Regression.getResult()
# get the residual error
residual = result.getResiduals()
# get the relative error
relativeError = result.getRelativeErrors()

#second example : create the problem with an experiment plane:
#first, we create the plane
myPlane = MonteCarloExperiment(distribution, 250)
myExperiment = Experiment(myPlane, "example")
#second, we create our svm regression object, the first parameter is the function
Regression2 = SVMRegression(model, myExperiment, 
LibSVM.Linear)
#third, we set kernel parameter and tradeoff factor
Regression2.setTradeoffFactor(tradeoff)
Regression2.setKernelParameter(kernel)
# Perform the algorithm
Regression2.run()
# Stream out the results
SVMRegressionResult = Regression2.getResult()
# get the residual error
residual = result.getResiduals()
# get the relative error
relativeError = result.getRelativeErrors()

#third example : create the problem with an isoprobabilistic distribution
#first, we create our distribution
marginals = DistributionCollection(dimension)
for i in range(dimension):
  marginals[i] = Uniform(0.0, 1.0)
distribution = ComposedDistribution(marginals)
#second, we create input and output samples
dataIn = distribution.getSample(250)
dataOut = model(dataIn)
#third, we create our svm regression
Regression3 = SVMRegression(dataIn,dataOut,distribution,
LibSVM.Polynomial) 
#and to finish, we set kernel parameter and tradeoff factor
Regression3.setTradeoffFactor(tradeoff)
Regression3.setKernelParameter(kernel)
# Perform the algorithm
Regression3.run()
# Stream out the results
SVMRegressionResult = Regression3.getResult()
# get the residual error
residual = result.getResiduals()
# get the relative error
relativeError = result.getRelativeErrors()

#fourth example is here to present you the SVMResourceMap class. 
#Users can fix others parameters like the degree and the constant of the 
#Polynomial Kernel,the cacheSize, the number of folds or the epsilon
#first, we create samples
dataIn = distribution.getSample(250)
dataOut = model(dataIn)
#second, we create our svm regression object
#here, we select the Polynomial Kernel but by default his degree is 3. We want a 
#degree of 2
ResourceMap.Set("LibSVM-DegreePolynomialKernel","2")
#now the degree of the Polynomial kernel is 2
Regression = SVMRegression(dataIn, dataOut, LibSVM.Polynomial)
#third, we set kernel parameter and tradeoff factor
Regression.setTradeoffFactor(tradeoff)
Regression.setKernelParameter(kernel)
# Perform the algorithm
Regression.run()
# Stream out the results
SVMRegressionResult = Regression.getResult()
# get the residual error
residual = result.getResiduals()
# get the relative error
relativeError = result.getRelativeErrors()
