#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/DecisionSystem/DecisionSystem.h"
#include "../include/Shared/Metrics.h"
#include "../include/Validators/Bagging/Bagging.h"

TEST(Bagging, BestKAndGlobalTPRAreGood) {

    DecisionSystem<float, std::string> decisionSystem("iris.data.csv", ',', 4);

    Bagging<float, std::string, float> bagging(&decisionSystem);

    auto bestScores = bagging.findBestK(50, 5, 40, (Metrics<float, float>::euclidean));

    unsigned long int bestK = std::get<0>(bestScores);
    double bestScore = std::get<1>(bestScores).getGlobalTPR();
}

