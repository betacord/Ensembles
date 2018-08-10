#ifndef ENSEMBLES_BOOTSTRAP_H
#define ENSEMBLES_BOOTSTRAP_H

#include <iostream>
#include <ctime>
#include <algorithm>
#include <unordered_map>

#include "../../DecisionSystem/DecisionSystem.h"
#include "../../Classifiers/Knn/Knn.h"


template<typename T, typename V, typename U>
class Bootstrap {

private:
    DecisionSystem<T, V> *ds;

    std::vector<unsigned long int> getTrainingIds();
    std::vector<unsigned long int> getTestIds(std::vector<unsigned long int>);

public:
    Bootstrap(DecisionSystem<T, V>);
    std::tuple<unsigned long int, double> getBestK(unsigned long int, unsigned long int, U (*metric)(std::vector<T>, std::vector<T>));
};


template<typename T, typename V, typename U>
Bootstrap<T, V, U>::Bootstrap(DecisionSystem<T, V> decisionSystem) {

    this->ds = new DecisionSystem<T, V>(decisionSystem);
}

template<typename T, typename V, typename U>
std::vector<unsigned long int> Bootstrap<T, V, U>::getTrainingIds() {

    std::vector<unsigned long int> samples = {};
    unsigned long int objectCount = this->ds->getObjectCount();

    srand(time(NULL));

    for (unsigned long int i = 0; i < objectCount; i++) {
        samples.push_back(rand() % objectCount);
    }

    return SharedMethods<unsigned long int>::getUniqueElements(samples);
}

template<typename T, typename V, typename U>
std::vector<unsigned long int> Bootstrap<T, V, U>::getTestIds(std::vector<unsigned long int> trainingIds) {

    std::vector<unsigned long int> samples = {};

    for (unsigned long int i = 0; i < this->ds->getObjectCount(); i++) {
        if (std::find(trainingIds.begin(), trainingIds.end(), i) != trainingIds.end() == false) {
            samples.push_back(i);
        }
    }

    return samples;
}

template<typename T, typename V, typename U>
std::tuple<unsigned long int, double> Bootstrap<T, V, U>::getBestK(unsigned long int minK, unsigned long int maxK, U (*metric)(std::vector<T>, std::vector<T>)) {

    std::vector<unsigned long int> trainingObjectsId = SharedMethods<unsigned long int>::getUniqueElements(this->getTrainingIds());
    std::vector<unsigned long int> testObjectsId = this->getTestIds(trainingObjectsId);

    DecisionSystem<T, V> trainingSystem = this->ds->getDecisionSystemByIds(trainingObjectsId);
    DecisionSystem<T, V> testSystem = this->ds->getDecisionSystemByIds(testObjectsId);

    std::unordered_map<unsigned long int, double> scores = {};

    for (unsigned long int i = 0; i < (maxK - minK + 1); i++) {
        Knn<T, V, U> knn(trainingSystem);
        unsigned long int currentK = i + minK;
        double tpr = knn.fit(testSystem, metric, currentK).getGlobalTPR();
        scores.insert({currentK, tpr});
    }

    double maxTpr = 0;

    for (auto& score : scores) {
        if (score.second > maxTpr) {
            return std::make_tuple(score.first, score.second);
        }
    }

    return std::make_tuple(0, 0);
}


#endif //ENSEMBLES_BOOTSTRAP_H
