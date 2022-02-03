cmake_minimum_required(VERSION 3.8)
project(VisApp VERSION 0.3.0 LANGUAGES CXX)

# main is for users to use
add_executable(main main.cpp my_kd_tree.cpp utils.cpp)
target_compile_features(main PUBLIC cxx_std_17)

# we test the performance bottelneck at time_cost
add_executable(test_performance ./test/test_performance.cpp my_kd_tree.cpp utils.cpp)
target_compile_features(test_performance PUBLIC cxx_std_17)

add_executable(test_function ./test/test_function.cpp my_kd_tree.cpp utils.cpp)
target_compile_features(test_function PUBLIC cxx_std_17)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
