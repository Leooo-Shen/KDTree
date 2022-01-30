# Project: Kd-tree

## Motivation

A kd-tree is a special kind of binary tree that can store points from a k-dimensional space. It can be used for efficient (space partitioning) search, meaning that at every level, the space will be divided along one dimension by comparing against one dimension of the point. At the next level the space is divided along another dimension. You can find an abstract overview [here](https://www.ri.cmu.edu/pub_files/pub1/moore_andrew_1991_1/moore_andrew_1991_1.pdf), a less abstract overview with a kd-tree of dimension 2 [here](https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf). These resources also explain how some search strategies can be implemented.

## Code structure

```
kd-tree
|   README.md
|   main.cpp
|───build
|───data
|      generated_values.csv
|───src
|      main.cpp
|      node.cpp
|      my_kd_tree.cpp
|      my_kd_tree.h
|      searchNN.cpp
|      searchNN.h
|      utils.cpp
|      utils.h
|      CMakeLists.txt
|───test
|      kd-tree-test.cpp
|      kd-search-test.cpp
|      CMakeLists.txt
```

## Descriptions
To use the 


## Sprint Targets 
### Sprint 1

* Kd-tree can be constructed
* Points can be added 
* Points can be read in from file

### Sprint 2

* Implement 2 search strategies: find the minimum, KNN search
* Use classes 
* Add a free_memory function to delete the whole tree 
* Add some test functions


### Sprint 3

* Log the calculation time
* Analyze the bottleneck of code performance
* Add detailed comments to improve the code readability
