#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/Metrics.h"
#include "../include/Knn.h"
#include "../include/DecisionSystem.h"

using testing::Eq;


TEST(Knn, TPRForClass2IsCorrectly) {

    Knn<int, std::string, float> knnClassifier("c3.txt", ';', 4);

    DecisionSystem<int, std::string> test("c3_test.txt", ';', 4);

    ASSERT_EQ(1, knnClassifier.fit(test, &(Metrics<int, float>::euclidean), 2).getTPR("2"));
}

TEST(Knn, TPRForClass4IsCorrectly) {

    Knn<int, std::string, float> knnClassifier("c3.txt", ';', 4);

    DecisionSystem<int, std::string> test("c3_test.txt", ';', 4);

    ASSERT_EQ(0.5, knnClassifier.fit(test, &(Metrics<int, float>::euclidean), 2).getTPR("4"));
}