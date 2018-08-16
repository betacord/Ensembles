#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

#include "../include/Shared/Metrics.h"

using testing::Eq;


TEST(Metrics, EuclideanMetricIsCalculatedCorrectly) {

    std::vector<int> test = { 2, 4, 2, 1 };
    std::vector<int> train = { 1, 3, 1, 1 };

    float distance = Metrics<int, float>::euclidean(&test, &train);

    ASSERT_EQ((float)sqrt(3.0), distance);
}