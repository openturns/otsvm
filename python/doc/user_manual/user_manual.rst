User manual
===========

.. currentmodule:: otsvm


The Libsvm library provides efficient algorithms to produce a model by Support Vector Machine.

Introduction to support vector machine
--------------------------------------

A support vector machine is a concept in statistics and computer science for a
set of related supervised learning methods that analyze data and recognize
patterns, used for classification and regression analysis.
The standard SVM takes a set of input data and predicts, for each given input,
which of two possible classes forms the input. Given a set of training
examples, each marked as belonging to one of two categories, a SVM training
algorithm builds a model that assigns new examples into one category or
the other.

More formally, a SVM constructs a hyperplane in a high or infinite-dimensional
space, which can be used for classification or regression. A good separation
is achived by the hyperplane that has the largest distance to the nearest
training data point of any class.

Whereas the original problem may be stated in a finite dimensional space,
it often happens that the sets to discriminate are not linearly separable in
that space. For this reason, it was proposed that the original
finite-dimensional space be mapped into a much higher-dimensional space,
presumably making the separation easier in that space. To keep the
computational load reasonable, the mappings used by SVM schemes are designed to
ensure that dot products may be computed easily in terms of the variables in
the original space, by defining them in terms of a kernel function
:math:`K(x,y)` selected to suit the problem.

Linear SVM
----------

Given some training data :math:`D`, a set of n points of the form

.. math::

    D\ =\ \{(x_{i},y_{i})\ |\ x_{i} \in \mathbb{R}^{p},\ y_{i} \in \{-1,1\}\}^{n}_{i=1}

where the :math:`y_i` is either 1 or -1, indicating the class to which the point
:math:`x_i` belongs. Each :math:`x_{i}` is a p-dimensional real vector.
We want to find the maximum-margin hyperplane that divides the points having
:math:`y_i=1` from those having :math:`y_i=-1`.


Any hyperplane can be written as the set of points :math:`x` satisfying
:math:`w \cdot x - b = 0` where :math:`cdot` denotes the dot product and
:math:`w` the normal vector to the hyperplane.
We want to choose :math:`w` and :math:`b` to maximize the margin, or distance
between the parallel hyperplanes that are as far apart as possible while still
separating the data. These hyperplanes can be described by the equations

.. math::

    w \cdot x - b = 1

and

.. math::

    w \cdot x - b = -1

The distance between these two hyperplanes is :math:`\frac{2}{||w||}`, so we
want to minimize :math:`||w||`. As we also have to prevent data points from
falling into the margin, we add the following constraint : for each i either

.. math::

    y_{i}(w \cdot x_{i} - b)\geq 1\quad for\ all\ 1\leq i\leq n

So we get the optimization problem :

.. math::

    Min\ ||w||
    subject\ to\ ( for\ any\ i=1,...,n )
    y_{i}(w \cdot x_{i} - b)\geq 1

Primal form
-----------

The optimization problem presented in the preceding section is difficult to
solve because it depends on :math:`||w||`, which involves a
square root. It is possible to alter the equation by substituing :math:`||w||`
with :math:`\frac{1}{2}||w||^{2}`
without changing the solution. This is a quadratic programming optimization problem:

.. math::

    Min\ \frac{1}{2}||w||^{2}
    subject\ to\ ( for\ any\ i=1,...,n )
    y_{i}(w \cdot x_{i} - b)\geq 1

By introducing Lagrange multipliers :math:`\alpha`, the previous constrained problem can be expressed as

.. math::

    \underset{w,b}{\text{min}}\ \underset{\alpha \geq 0}{\text{max}}\{\frac{1}{2}||w||^{2}-\sum_{i=1}^n \alpha_{i}[y_{i}(w \cdot x_{i} - b)-1]\}

This problem can now be solved by standard quadratic programming techniques and
programs. The stationary Karush-Kuhn-Tucker condition implies that the solution
can be expressed as a linear combination of the training vectors
:math:`w = \sum_{i=1}^n \alpha_i y_i x_i`.

Only a few :math:`\alpha_i` will be greater than zero. The corresponding
:math:`x_i` are exactly the support vectors, which lie on the margin and
satisfy :math:`y_i (w\cdot x_i -b)=1`.

Dual form
---------

Using the fact that :math:`||w||^2 = w \cdot w` and substituing
:math:`w = \sum_{i=1}^n \alpha_i x_i y_i`, one can show that the dual of the
SVM reduces to the following optimization problem:

.. math::

    Max\ L(\alpha) = \sum_{i=1}^n \alpha_i - \frac{1}{2} \sum_{i,j} \alpha_i \alpha_j y_i y_j x_i^T x_j = \sum_{i=1}^n \alpha_i - \frac{1}{2} \sum_{i,j} \alpha_i \alpha_j y_i y_j k(x_i,x_j)

    subject\ to\ ( for\ any\ i = 1,...,n  )
    \alpha_i \geq 0

and to the constraint from the minimization in b

.. math::

    \sum_{i=1}^n \alpha_i y_i =0


:math:`w` can be computed thanks to the :math:`\alpha` terms: :math:`w=\sum_i \alpha_i y_i x_i`


Soft margin
-----------

If there exists no hyperplane that can split the "yes" and "no" examples, the
soft margin method will choose a hyperplane that splits the examples as cleanly
as possible, while still maximizing the distance to the nearest cleanly split
examples. The method introduces slack variables, :math:`\xi_i`, which measure the
degree of misclassification of the data :math:`x_i`

.. math::

    y_i(w \cdot x_i - b) \geq 1 - \xi_i \quad 1 \leq i \leq n


The objective function is then increased by a function which penalizes non-zero
:math:`\xi_i` and the optimization becomes a trade off between a large margin
and a small error penalty. If the penalty function is linear, the optimization
problem becomes:

.. math::

    \underset{w,b,\xi}{\text{min}}\{\frac{1}{2} ||w||^2 + C\sum_{i=1}^n \xi_i \}
    subject to (for any i=1,...,n)
    y_i ( w \cdot x_i - b) \geq 1 - \xi_i \quad \xi_i \geq 0

This constaint with the objective of minimizing :math:`||w||` can be solved
using Lagrange multipliers as done above. One has then to solve the problem:

.. math::

    \underset{w,b,\xi}{\text{min}}\ \underset{\alpha,\beta}{\text{max}}\{\frac{1}{2} ||w||^2 + C\sum_{i=1}^n \xi_i - \sum_{i=1}^n \alpha_i[y_i(w \cdot x_i - b)-1 +\xi_i]- \sum_{i=1}^n \beta_i\xi_i \}
    with \alpha_i , \beta_i \geq 0

The dual form becomes:

.. math::

    \underset{\alpha_i}{\text{max}}\ \{L(\alpha) = \sum_{i=1}^n \alpha_i - \frac{1}{2} \sum_{i,j} \alpha_i \alpha_j y_i y_j k(x_i,x_j)\}
    subject to (for any i=1,...,n)
    0 \leq \alpha_i \leq C
    and
    \sum_{i=1}^n \alpha_i y_i = 0

Nonlinear SVM
-------------

The algorithm is formally similar, except that every dot product is replaced by
a nonlinear kernel function. This allows the algorithm to fit the
maximum-margin hyperplane in a transformed feature space.
The transformation may be nonlinear and the transformed space high dimensional,
thus though the classifier is a hyperplane in the high-dimensional feature
space, it may be nonlinear in the original input space.

Some common kernels include:
  - Polynomial : :math:`k(x_i,x_j)=(x_i\cdot x_j+c)^d`
  - Gaussian Radial Basis Function : :math:`k(x_i,x_j)=exp(-\gamma ||x_i-x_j||^2)`
  - Hyperbolic tangent : :math:`k(x_i,x_j)=tanh(\gamma x_i\cdot x_j + c)`

The kernel is related to the transform :math:`\varphi(x_i)` by the equation

.. math::

    k(x_i,x_j)=\varphi(x_i)\cdot\varphi(x_j)

The value :math:`w` is also in the transformed space, with :math:`w=\sum_i\alpha_i y_i\varphi(x_i)`.

The effectiveness of SVM depends on the selection of kernel, the kernel's
parameters, and soft margin parameter C. A common choice is a Gaussian kernel,
which has a single parameter :math:`\gamma`. Best combination of C and
:math:`\gamma` is selected by a grid search with exponentially growing
sequences of C and :math:`\gamma`. Each combination of parameter choices is
checked using cross validation, and the parameters with best cross-validation
accuracy are picked.
The final model, which is used for testing and for classifying data, is then
trained on the whole training set using the selected parameters.

Classification
--------------

Given training vectors :math:`x_i` in two classes and a vector :math:`y\in{-1,1}`,
C-SVC (the algorithm that we use for classification) solves the following dual
problem:

.. math::

    min_{\alpha} \frac{1}{2} \alpha^TQ\alpha-e^T\alpha
    0\leq \alpha_i \leq C
    y^T\alpha=0

where e is the vector of all ones, :math:`C>0` is the upper bound, Q is an
l by l positive semidefinite matrix :math:`Q_{ij}=y_iy_jK(x_i,x_j)`
and :math:`K(x_i,x_j)` is the kernel. The decision function is

.. math::

    sign(\sum_{i=1}^l y_i\alpha_iK(x_i,x)+b)

For some classification problems, numbers of data in different classes are
unbalanced. We can use different penalty parameters in the SVM formulation,
the dual of C-SVC becomes:

.. math::

    min_{\alpha} \frac{1}{2} \alpha^TQ\alpha-e^T\alpha
    0\leq \alpha_i \leq C_+,\ if\ y_i=1
    0\leq \alpha_i \leq C_-,\ if\ y_i=-1
    y^T\alpha=0

where :math:`C_+` and :math:`C_-` depending on :math:`y_i` and :math:`y_j`
and of weights that we can fix for each class.

Regression
----------

Up to now, we presented SVM for classification. We can use too for regression.
This is similar to the nonlinear case. We replace the soft margin by 
a :math:`\varepsilon`-insensitive loss function which is defined like:

.. math::

    |y-f(x)|_\varepsilon = max(0,|y-f(x)|-\varepsilon)

where f(x) is the loss function and :math:`\varepsilon` a precision parameter.

We get this optimization problem if we introduce the slack variables :math:`\xi\ and\ \xi_i`:

.. math::

    min_w \{\frac{||w||^2}{2}+C\sum_{i=1}^n(\xi_i+\xi_i^*) \}
    subject to (for any i=1,...,n)
    l_i-wx_i+b\leq \varepsilon+\xi_i
    wx_i-b-l_i\leq \varepsilon +\xi_i^*
    \xi_i,\xi_i^* \geq 0

with C which is a control parameter like in soft margin. 

To solve this problem, we introduce a new time Lagrange multipliers and we
will get this regression function:

.. math::

  f(x)=\sum_{i=1}^n(\alpha_i-\alpha_i^*)K(x_i,x)-b



Choose a kernel
---------------

.. autosummary::
    :toctree: _generated/
    :template: class.rst_t

    NormalRBF
    ExponentialRBF
    LinearKernel
    PolynomialKernel
    RationalKernel
    SigmoidKernel

Classification
--------------

.. autosummary::
    :toctree: _generated/
    :template: class.rst_t

    LibSVMClassification

Regression
----------

.. autosummary::
    :toctree: _generated/
    :template: class.rst_t

    LibSVMRegression
