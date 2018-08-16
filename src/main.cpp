#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/Classifiers/Knn/Knn.h"
#include "../include/Shared/Metrics.h"
#include "../include/Validators/Bootstrap/Bootstrap.h"


int main(int argc, char* argv[]) {

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return 0;
}