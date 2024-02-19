#! /usr/bin/env python

import openturns as ot
import openturns.testing as ott
import otsvm
import os

kernels = [
    otsvm.NormalRBF(2.0),
    otsvm.ExponentialRBF(2.0),
    otsvm.LinearKernel(),
    otsvm.PolynomialKernel(3.0, 2.0, 1.0),
    otsvm.RationalKernel(2.0),
    otsvm.SigmoidKernel(1.0, 0.0),
]

V = []
x = [2.0] * 2
y = [1.0] * 2
V.append([x, y])
x = [0.0, 5.0]
y = [0.0, 3.0]
V.append([x, y])

for kernel in kernels:
    print(kernel)
    for v in V:
        x, y = v
        print("x,y=", x, y)
        print("kernel=", kernel)
        kxy = kernel(x, y)
        print(f"kernel(x,y)={kxy:.5g}")
        kxydx = kernel.partialGradient(x, y)
        print("dkernel/dx_i(x,y)=", repr(kxydx))

        # check gradient by finite diff
        kxydxfd = [0.0] * 2
        h = 1e-7
        for j in range(2):
            xh = list(x)
            xh[j] += h
            kxyh = kernel(xh, y)
            kxydxfd[j] = (kxyh - kxy) / h
        print("fdkernel/dx_i(x,y)=", repr(kxydxfd))
        ott.assert_almost_equal(kxydx, kxydxfd)

        kxydx2 = kernel.partialHessian(x, y)
        print("d2kernel/(dx_i*dx_j)(x,y)=", repr(kxydx2))

    # parameter accessor
    param = kernel.getParameter()
    kernel.setParameter(param)

    # serialization
    if ot.PlatformInfo.HasFeature("libxml2"):
        study = ot.Study()
        fname = "study_kernel.xml"
        study.setStorageManager(ot.XMLStorageManager(fname))
        study.add("kernel", kernel)
        study.save()
        study = ot.Study()
        study.setStorageManager(ot.XMLStorageManager(fname))
        study.load()
        kernel = otsvm.SVMKernel()
        study.fillObject("kernel", kernel)
        print(kernel)
        os.remove(fname)
