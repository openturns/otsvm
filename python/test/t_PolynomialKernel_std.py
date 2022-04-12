#! /usr/bin/env python

from openturns import *
from otsvm import *

kernel = PolynomialKernel(3, 2, 1)
x = Point(2, 2)
y = Point(2, 1)

print(" kernel ([2 2],[1 1]) = ", repr(kernel(x, y)))
print(" dkernel/dx_i([2 2],[1 1]) = ", repr(kernel.partialGradient(x, y)))
print(" d2kernel/(dx_i*dx_j)([2 2],[1 1]) = ", repr(
    kernel.partialHessian(x, y)))

x[0] = 0
x[1] = 5
y[0] = 0
y[1] = 3

print(" kernel ([0 5],[0 3]) = ", repr(kernel(x, y)))
print(" dkernel/dx_i([0 5],[0 3]) = ", repr(kernel.partialGradient(x, y)))
print(" d2kernel/(dx_i*dx_j)([0 5],[0 3]) = ", repr(
    kernel.partialHessian(x, y)))

kernel2 = PolynomialKernel(1, 2, 1)

print(" kernel2 ([0 5],[0 3]) = ", repr(kernel2(x, y)))
print(" dkernel2/dx_i([0 5],[0 3]) = ", repr(kernel2.partialGradient(x, y)))
print(" d2kernel2/(dx_i*dx_j)([0 5],[0 3]) = ", repr(
    kernel2.partialHessian(x, y)))
