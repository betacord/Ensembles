cmake_minimum_required(VERSION 3.10)
project(ensembles)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(ensembles src/main.cpp include/DecisionSystem/DecisionSystem.h tests/DecisionSystemTests.cpp include/Classifiers/Knn/Knn.h include/Shared/Metrics.h tests/MetricsTests.cpp include/Shared/SharedMethods.h tests/KnnTests.cpp include/Classifiers/Knn/KnnScore.h include/Validators/Bootstrap/Bootstrap.h tests/BootstrapTests.cpp include/Validators/Bagging/Bagging.h tests/BaggingTests.cpp)

target_link_libraries(ensembles gtest gtest_main)
