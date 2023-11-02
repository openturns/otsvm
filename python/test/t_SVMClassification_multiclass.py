#! /usr/bin/env python

import openturns as ot
import openturns.testing as ott
import otsvm
import os

# we retrieve the sample from the file sample.csv
path = os.path.abspath(os.path.dirname(__file__))
dataInOut = ot.Sample.ImportFromCSVFile(os.path.join(path, "multiclass.csv"), ",")

dataIn = ot.Sample(148, 4)
dataOut = ot.Indices(148, 0)

# we build the input Sample and the output Sample because we must separate
# dataInOut
for i in range(148):
    a = dataInOut[i]
    b = ot.Point(4)
    b[0] = a[1]
    b[1] = a[2]
    b[2] = a[3]
    b[3] = a[4]
    dataIn[i] = b
    dataOut[i] = int(a[0])


# list of C parameter
cp = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]
# list of gamma parameter in kernel function
gamma = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]

# create the Problem
algo = otsvm.LibSVMClassification(dataIn, dataOut)
algo.setKernelType(otsvm.LibSVM.NormalRbf)
algo.setTradeoffFactor(cp)
algo.setKernelParameter(gamma)

# compute the classification
algo.run()

# check accuracy
accuracy = algo.getAccuracy()
print(accuracy)
ott.assert_almost_equal(accuracy, 97.2973, 1e-2)

testv = [0.0555554, -0.25, 0.118644, -4.03573e-08]

# predict
classif = algo.classify(testv)
print(classif)
ott.assert_almost_equal(classif, 2)

# grade
grade1 = algo.grade(testv, 1)
print(grade1)
ott.assert_almost_equal(grade1, 0.0)
grade2 = algo.grade(testv, 2)
print(grade2)
ott.assert_almost_equal(grade2, 2.0)
grade3 = algo.grade(testv, 3)
print(grade3)
ott.assert_almost_equal(grade3, 1.0)
