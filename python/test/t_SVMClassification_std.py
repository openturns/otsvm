#! /usr/bin/env python

import openturns as ot
import openturns.testing as ott
import otsvm
import os

# we retrieve the sample from the file sample.csv
path = os.path.abspath(os.path.dirname(__file__))
dataInOut = ot.Sample.ImportFromCSVFile(os.path.join(path, "sample.csv"), ",")
size = len(dataInOut)
dataIn = dataInOut.getMarginal([1, 2])
dataOut = [int(dataInOut[i, 0]) for i in range(size)]

# list of C parameter
cp = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]
# list of gamma parameter in kernel function
gamma = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]

# create the Problem
algo = otsvm.SVMClassification(dataIn, dataOut)
algo.setKernelType(otsvm.LibSVM.NormalRbf)
algo.setTradeoffFactor(cp)
algo.setKernelParameter(gamma)
print(algo)

# compute the classification
algo.run()

# check accuracy
accuracy = algo.getAccuracy()
print(accuracy)
ott.assert_almost_equal(accuracy, 100.0)

for i in range(10):
    x = dataIn[i]
    c = dataOut[i]
    print(f"x={x} c={c} classify={algo.classify(x)} grade={algo.grade(x, c)} predict={algo.predict(x)}")

algo.setWeight([1.0] * size)

algo.runKMeans(2)
accuracy = algo.getAccuracy()
print(accuracy)
assert accuracy > 99.8, "accuracy"

if ot.PlatformInfo.HasFeature("libxml2"):
    study = ot.Study()
    fname = "study_classif.xml"
    study.setStorageManager(ot.XMLStorageManager(fname))
    study.add("algo", algo)
    study.save()
    study = ot.Study()
    study.setStorageManager(ot.XMLStorageManager(fname))
    study.load()
    algo = otsvm.SVMClassification()
    study.fillObject("algo", algo)
    accuracy = algo.getAccuracy()
    os.remove(fname)
