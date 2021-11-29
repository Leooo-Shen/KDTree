# Project: Kd-tree

Idea contributed by Andreas Döring, andreas.doering@tum.de.

## Motivation

A kd-tree is a special kind of binary tree that can store points from a k-dimensional space. It can be used for efficient (space partitioning) search, meaning that at every level, the space will be divided along one dimension by comparing against one dimension of the point. At the next level the space is divided along another dimension. You can find an abstract overview [here](https://www.ri.cmu.edu/pub_files/pub1/moore_andrew_1991_1/moore_andrew_1991_1.pdf), a less abstract overview with a kd-tree of dimension 2 [here](https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf). These resources also explain how some search strategies can be implemented.

## Sprint 1

Create a kd-tree data structure to store data with dimensionality k = 2, hence creating a 2D-tree. Optionally you can choose to go for k = 3 or k being variable.

### Definion of "done"

* Kd-tree can be constructed
* Points can be added and deleted
* Points can be read in from file

## Sprint 2

Implement and test at least two different search strategies such as KNN search, range search or finding the minimum. This should be done using classes. Refer to the references for examples. The structure could look something like this:
```
kd-tree
|   README.md
|   main.cpp
|───build
|───data
|      points.csv
|───src
|      kd-tree.cpp
|      kd-tree.h
|      kd-search.cpp
|      kd-search.h
|      CMakeLists.txt
|───test
|      kd-tree-test.cpp
|      kd-search-test.cpp
|      CMakeLists.txt
```

### Definion of "done"

* Two search strategies are implemented
* Tests are implemented as well

## Sprint 3

Optimize for speed and memory consumption.

### Definion of "done"

* Calculation time should be logged
* Memory consumption should be logged
* At least two performance aspects are studied and their effect and improvement approach should be presented in a short report
