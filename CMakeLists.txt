cmake_minimum_required(VERSION 3.10)
project(ensembles)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(ensembles src/main.cpp include/DecisionSystem.h tests/DecisionSystemTests.cpp include/Knn.h include/Metrics.h tests/MetricsTests.cpp include/SharedMethods.h tests/KnnTests.cpp include/KnnScore.h)

target_link_libraries(ensembles gtest gtest_main)
