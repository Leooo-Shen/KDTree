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
|      generated_values_small.csv
|      generated_values_middle.csv
|      generated_values_large.csv
|───include  
|      my_kd_tree.h
|      node.h
|      rect.h
|      utils.h
|───src
|      main.cpp
|      my_kd_tree.cpp
|      searchNN.cpp
|      utils.cpp
|      CMakeLists.txt
|───test
|      test_function.cpp
|      test_performance.cpp
|───performance_analysis
|      performance_analysis.md
```

## Descriptions
To compile to code, first go to the build folder: `cd build`

Then use cmake to compile: `cmake ../src/` then `make`

This will generate 3 executable files in the build folder: "main", "test_function", "test_performance".

* main: it includes the main functionality of our code with user interface.
* test_function: it tests the code functions
* test_performance: it records run time for performance analysis


## Sprint Targets 
### Sprint 1

* Kd-tree can be constructed
* Points can be added 
* Points can be read in from file

### Sprint 2

* Implement 2 search strategies: find the minimum, KNN search (some bug detected in sprint3)
* Use classes 
* Add a delete_tree functions that recursively delete the constructed tree
* Add some test functions


### Sprint 3

* Log the calculation time and memory comsumption
* Analyze the bottleneck of code performance
* Add detailed comments to improve the code readability
* Try to use smart pointers to deal with memory leakage issues (under construction)
