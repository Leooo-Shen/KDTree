# Performance Analysis Report

We record the time and memory consumptions of core functions at `time_cost.cpp`.

## Experiment dataset 
Generated 2-d sample data. Loaded with our code as `std::vector<double>`.

### Size of dataset
- small: 1 thousand 
- middle: 1 million
- large: 10 million (177.9 MB)

## Hardware Info


## Results

### Time cost with small dataset
- Time cost in loading data from csv: 0.000878ss
- Time cost in constructing kd-tree: 0.000878s
- Time cost in finding minimum: 6e-5s
- Time cost in finding nearest neighbor: 0.000164s
- Total time: 4.9e-05s
### Time cost with middle dataset

### Time cost with large dataset
- Time cost in loading data from csv: 14.6284s
- Time cost in constructing kd-tree: 41.7008s
- Time cost in finding minimum: 0.000795s
- Time cost in finding nearest neighbor: 0.000659s
- Total time: 

### Memory consumption

## Diagrams


## Analysis
1. The slowest part of the code is to construct kd-tree from loaded data, which 

load data from csv file, then convert to `std::vector<double>`, which takes up to 


