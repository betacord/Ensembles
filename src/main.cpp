#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/Knn.h"
#include "../include/Metrics.h"


int main(int argc, char* argv[]) {

//    Knn<float, std::string> knnClassifier("data.txt", ';', 4);
//    std::cout << knnClassifier.classifyObject({1, 2, 1, 1}, &(Metrics::euclidean), 2);

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return 0;
}