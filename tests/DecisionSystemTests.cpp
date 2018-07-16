#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/DecisionSystem.h"

using testing::Eq;


TEST(DecisionSystem, AllRowsHasBeenReadCorrectly) {

    DecisionSystem<float> ds("data.txt", ';', 3);

    ASSERT_EQ(5, ds.objectCount());
}

TEST(DecisionSystem, AllPredictorsHasBeenReadCorrectly) {

    DecisionSystem<float> ds("data.txt", ';', 3);

    ASSERT_EQ(3, ds.predictorCount());
}

TEST(DecisionSystem, LastElementInDecisionSystemIs20) {

    DecisionSystem<float> ds("data.txt", ';', 3);

    ASSERT_EQ(20, ds.get(4, 3));
}

TEST(DecisionSystem, FirstElementInDecisionSystemIs20) {

    DecisionSystem<float> ds("data.txt", ';', 3);

    ASSERT_EQ(1, ds.get(0, 0));
}


