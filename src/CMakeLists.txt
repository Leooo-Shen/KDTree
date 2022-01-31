cmake_minimum_required(VERSION 3.8)
project(VisApp VERSION 0.3.0 LANGUAGES CXX)

# main is for users to use
add_executable(main main.cpp my_kd_tree.cpp utils.cpp)
target_compile_features(main PUBLIC cxx_std_17)

# we test the performance bottelneck at time_cost
add_executable(time_cost ../test/time_cost.cpp my_kd_tree.cpp utils.cpp)
target_compile_features(time_cost PUBLIC cxx_std_17)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
