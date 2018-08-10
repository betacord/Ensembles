#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/DecisionSystem/DecisionSystem.h"
#include "../include/Validators/Bootstrap/Bootstrap.h"
#include "../include/Shared/Metrics.h"

using testing::Eq;

TEST(Bootstrap, BestKIsGood) {

    DecisionSystem<int, std::string> decisionSystem("c3_full.txt", ';', 4);

    Bootstrap<int, std::string, float> bootstrap(decisionSystem);

    std::tuple<unsigned long int, double> bestScore = bootstrap.getBestK(2, 4, &(Metrics<int, float>::euclidean));
}