"""
Classification
--------------
"""

# %%
# The objective of this Use Case is to create a SVM Classification algorithm
# in order to build a metamodel that separates data in 2 classes.
#
# otsvm enables to:
#
# - set lists of tradeoff factors and kernel parameter with the methods setTradeoffFactor, setKernelParameter.
# - select the kernel type in this list : Linear Kernel, Polynomial Kernel, Sigmoid Kernel, RBF kernel.
# - run the algorithm on an input and output samples.
#

# %%
import openturns as ot
import otsvm
import os

# this example uses a csv file with the datas for the classification
# we retrieve the sample from the file sample.csv
try:
    path = os.path.abspath(os.path.dirname(__file__))
except NameError:
    # in notebook
    path = os.getcwd()
dataInOut = ot.Sample.ImportFromCSVFile(os.path.join(path, "sample.csv"), ",")

# we create dataIn and dataOut
size = dataInOut.getSize()
dataIn = dataInOut.getMarginal([1, 2])
dataOut = [int(dataInOut[i, 0]) for i in range(size)]

# list of C parameter
cp = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]
# list of gamma parameter in kernel function
gamma = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]

# create the Classification Problem
algo = otsvm.SVMClassification(dataIn, dataOut)
algo.setKernelType(otsvm.LibSVM.NormalRbf)
algo.setTradeoffFactor(cp)
algo.setKernelParameter(gamma)

# compute the classification
algo.run()
print("#######################")
print("Results with Samples I/O")
print("Accuracy(p.c.)=", algo.getAccuracy())
