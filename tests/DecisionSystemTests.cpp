#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/DecisionSystem.h"

using testing::Eq;


TEST(DecisionSystem, AllRowsHasBeenReadCorrectly) {

    DecisionSystem<float, std::string> ds("data.txt", ';', 4);

    ASSERT_EQ(5, ds.getObjectCount());
}

TEST(DecisionSystem, AllPredictorsHasBeenReadCorrectly) {

    DecisionSystem<float, std::string> ds("data.txt", ';', 4);

    ASSERT_EQ(3, ds.getPredictorCount());
}

TEST(DecisionSystem, LastElementInDecisionSystemIs20) {

    DecisionSystem<float, std::string> ds("data.txt", ';', 4);

    ASSERT_EQ(20, ds.get(4, 3));
}

TEST(DecisionSystem, FirstElementInDecisionSystemIs20) {

    DecisionSystem<float, std::string> ds("data.txt", ';', 4);

    ASSERT_EQ(1, ds.get(0, 0));
}

TEST(DecisionSystem, DecisionClassesInC3Are2And4) {

    DecisionSystem<float, std::string> ds("c3.txt", ';', 4);

    std::vector<std::string> decisionClasses {"2", "4"};

    ASSERT_EQ(ds.getDecisionClasses(), decisionClasses);
}

TEST(DecisionSystem, FirstObjectIs1_3_1_1) {

    DecisionSystem<float, std::string> ds("c3.txt", ';', 4);

    std::vector<float> objectElements {1, 3, 1, 1};

    ASSERT_EQ(ds.getObjectById(0), objectElements);
}

TEST(DecisionSystem, TestingObjectsByDecisionClass2) {

    DecisionSystem<float, std::string> ds("c3.txt", ';', 4);

    std::vector<std::vector<float>> objectElements {{1, 3, 1, 1}, {10, 3, 2, 1}, {2, 3, 1, 1}};

    ASSERT_EQ(ds.getObjectsByDecisionClass("2"), objectElements);
}

TEST(DecisionSystem, TestingObjectsByDecisionClass4) {

    DecisionSystem<float, std::string> ds("c3.txt", ';', 4);

    std::vector<std::vector<float>> objectElements {{10, 9, 7, 1}, {3, 5, 2, 2}, {2, 3, 1, 1}};

    ASSERT_EQ(ds.getObjectsByDecisionClass("4"), objectElements);
}


