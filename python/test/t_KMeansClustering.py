#! /usr/bin/env python

import openturns as ot
import openturns.testing as ott
import otsvm

# Instantiate one distribution object
dimension = 2
meanPoint = ot.Point([0.5, -0.5])
sigma = ot.Point([2.0, 3.0])
R = ot.CorrelationMatrix(dimension)
for i in range(1, dimension):
    R[i, i - 1] = 0.5

# Create a collection of distribution
aCollection = []

aCollection.append(ot.Normal(meanPoint, sigma, R))
meanPoint += ot.Point(meanPoint.getDimension(), 1.0)
aCollection.append(ot.Normal(meanPoint, sigma, R))
meanPoint += ot.Point(meanPoint.getDimension(), 1.0)
aCollection.append(ot.Normal(meanPoint, sigma, R))

# Instantiate one distribution object
distribution = ot.Mixture(aCollection)

size = 500
sample = distribution.getSample(size)
sample_split = [sample]
meanPoint[0] = 10
meanPoint[1] = 10

# Create a collection of distribution
aCollection = []

aCollection.append(ot.Normal(meanPoint, sigma, R))
meanPoint += ot.Point(meanPoint.getDimension(), 1.0)
aCollection.append(ot.Normal(meanPoint, sigma, R))
meanPoint += ot.Point(meanPoint.getDimension(), 1.0)
aCollection.append(ot.Normal(meanPoint, sigma, R))

# Instantiate one distribution object
distribution = ot.Mixture(aCollection)

sample2 = distribution.getSample(size)
sample.add(sample2)
sample_split.append(sample2)

meanPoint[0] = 3
meanPoint[1] = 12

# Create a collection of distribution
aCollection = []

aCollection.append(ot.Normal(meanPoint, sigma, R))
meanPoint += ot.Point(meanPoint.getDimension(), 1.0)
aCollection.append(ot.Normal(meanPoint, sigma, R))
meanPoint += ot.Point(meanPoint.getDimension(), 1.0)
aCollection.append(ot.Normal(meanPoint, sigma, R))

# Instantiate one distribution object
distribution = ot.Mixture(aCollection)

sample3 = distribution.getSample(size)
sample.add(sample3)
sample_split.append(sample3)

kmeans = otsvm.KMeansClustering(sample, 3)
kmeans.run()

result = kmeans.getCluster()
print("result=", result)

sample_split_result = [
    ot.Sample(0, dimension),
    ot.Sample(0, dimension),
    ot.Sample(0, dimension),
]

accuracy = 0.0
for i in range(len(sample)):
    ci = result[i]
    sample_split_result[ci].add(sample[i])

    # here the first cluster is mapped to the 2nd sample
    mapci = {0: 1, 1: 0, 2: 2}
    if sample[i] in sample_split[mapci[ci]]:
        accuracy += 1.0 / len(sample)
ott.assert_almost_equal(accuracy, 0.98333333)

draw = False
if draw:
    cloud1 = ot.Cloud(sample_split_result[0], "blue", "fsquare", "Normal Cloud")
    cloud2 = ot.Cloud(sample_split_result[1], "red", "fsquare", "Normal Cloud")
    cloud3 = ot.Cloud(sample_split_result[2], "green", "fsquare", "Normal Cloud")
    graph = ot.Graph("", "x1", "x2", True, "topright", 1.0)
    graph.add(cloud1)
    graph.add(cloud2)
    graph.add(cloud3)
    ot.Show(graph)
