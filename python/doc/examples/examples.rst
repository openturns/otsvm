Examples
========

Regression
----------

The objective of this Use Case is to create a SVM Regression algorithm in order to create a metamodel.


Otsvm enables :
 - to set lists of tradeoff factors and kernel parameter with the methods setTradeoffFactor, setKernelParameter.
 - to select the kernel type in this list : Linear Kernel, Polynomial Kernel, Sigmoid Kernel, RBF kernel.
 - to compute the algorithm on an input and output samples.
 - to compute the algorithm on an experiment plane and a function.
 - to compute the algorithm on an input and output samples and an isoprobabilistic distribution.


We recommend for users to use the RBF Kernel ( the gaussian kernel ). Moreover, it is important to understand that the selection of parameters ( kernel parameter and tradeoff factor ) is primary. If you don't know 
what to take as parameters, you must take a wide range values, for example :math:`tradeoff \in \{10^-5,10^-3,10^-1...10^3 \}`
:math:`kernel\ parameter \in \{10^-15, 10^-13...,10^3 \}`. Usually, the
algorithm always converges, but this can take a long while, mostly if you have
a lot of parameters to test.


.. literalinclude:: ../t_example1.py

Classification
--------------

The objective of this Use Case is to create a SVM Classification algorithm in order to build a metamodel that separates datas in 2 classes.

Otsvm enables to :
 - to set lists of tradeoff factors and kernel parameter with the methods setTradeoffFactor, setKernelParameter.
 - to select the kernel type in this list : Linear Kernel, Polynomial Kernel, Sigmoid Kernel, RBF kernel.
 - to compute the algorithm on an input and output samples.

.. literalinclude:: ../t_example2.py
