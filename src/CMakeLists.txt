
cmake_minimum_required(VERSION 3.8)
project(VisApp VERSION 0.1.0 LANGUAGES CXX)
add_executable(main main.cpp my_kd_tree.cpp utils.cpp searchNN.cpp)
target_compile_features(main PUBLIC cxx_std_17)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
