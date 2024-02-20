#! /usr/bin/env python

import os
import openturns as ot
import otsvm

model = ot.SymbolicFunction(["E", "F", "L", "I"], ["F*L^3/(3*E*I)"])
dim = model.getInputDimension()

R = ot.IdentityMatrix(dim)
mean = [50.0, 1.0, 10.0, 5.0]
distribution = ot.Normal(mean, [1.0] * dim, R)


dataIn = distribution.getSample(250)
dataOut = model(dataIn)

algo = otsvm.SVMRegression(dataIn, dataOut, otsvm.LibSVM.NormalRbf)
algo.run()
result = algo.getResult()

metamodel = result.getMetaModel()

fileName = "myStudy.xml"

if ot.PlatformInfo.HasFeature("libxml2"):
    # save
    study = ot.Study()
    study.setStorageManager(ot.XMLStorageManager(fileName))
    study.add("metamodel", metamodel)
    study.save()

    # load
    study = ot.Study()
    study.setStorageManager(ot.XMLStorageManager(fileName))
    study.load()
    loadedMetamodel = ot.Function()
    study.fillObject("metamodel", loadedMetamodel)

    os.remove(fileName)

    x = mean
    assert metamodel(x) == loadedMetamodel(x)
    assert metamodel.gradient(x) == loadedMetamodel.gradient(x)
    assert metamodel.hessian(x) == loadedMetamodel.hessian(x)

    # save
    study = ot.Study()
    study.setStorageManager(ot.XMLStorageManager(fileName))
    study.add("algo", algo)
    study.save()

    # load
    study = ot.Study()
    study.setStorageManager(ot.XMLStorageManager(fileName))
    study.load()
    loadedAlgo = otsvm.SVMRegression()
    study.fillObject("algo", loadedAlgo)
    assert algo.getKernelParameter() == loadedAlgo.getKernelParameter()
