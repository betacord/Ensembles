#ifndef ENSEMBLES_KNN_H
#define ENSEMBLES_KNN_H

#include <iostream>
#include <string>
#include <vector>

#include "DecisionSystem.h"
#include "Metrics.h"
#include "KnnScore.h"


template <typename T, typename V, typename U>
class Knn {

private:
    DecisionSystem<T, V> *ds;

    std::vector<U> calculateDistance(std::vector<T>, std::vector<std::vector<T>>, U (*metric)(std::vector<T>, std::vector<T>));
    std::vector<U> getFirstKElements(std::vector<U>, unsigned long int);
    V getDecision(std::vector<std::vector<U>>, std::vector<V>);
    bool checkUniqueDistances(std::vector<U>);
    V classifyObject(std::vector<T>, U (*metric)(std::vector<T>, std::vector<T>), unsigned long int);

public:
    Knn(std::string, char, int);
    KnnScore<V> fit(DecisionSystem<T, V>, U (*metric)(std::vector<T>, std::vector<T>), unsigned long int);
};


template <typename T, typename V, typename U>
Knn<T, V, U>::Knn(std::string fileName, char delimitter, int decisionCol) {

    this->ds = new DecisionSystem<T, V>(fileName, delimitter, decisionCol);

    std::vector<T> test { 2, 4, 2, 1 };
}

template<typename T, typename V, typename U>
std::vector<U> Knn<T, V, U>::calculateDistance(std::vector<T> testObject, std::vector<std::vector<T>> trainObjects,
                                            U (*metric)(std::vector<T>, std::vector<T>)) {

    std::vector<U> results;

    for (std::vector<T> object : trainObjects) {
        results.push_back(metric(testObject, object));
    }

    return results;
}

template<typename T, typename V, typename U>
std::vector<U> Knn<T, V, U>::getFirstKElements(std::vector<U> vec, unsigned long int k) {

    std::vector<U> result(vec);

    std::sort(result.begin(), result.end(), [](const T lhs, const T rhs )
    {
        return lhs < rhs;
    });

    result.resize(k);

    return result;
}

template<typename T, typename V, typename U>
V Knn<T, V, U>::getDecision(std::vector<std::vector<U>> distances, std::vector<V> decisions) {

    std::vector<U> sums;
    U minVal = U();
    unsigned long int minId = 0;

    for (std::vector<U> distance : distances) {
        T sum = 0;

        for (T n : distance) {
            sum += n;
        }

        sums.push_back(sum);
    }

    if (!this->checkUniqueDistances(sums)) {
        return V();
    }

    minVal = sums[0];

    for (int i = 0; i < sums.size(); i++) {
        if (sums[i] < minVal) {
            minVal = sums[i];
            minId = i;
        }
    }

    return decisions[minId];
}

template<typename T, typename V, typename U>
bool Knn<T, V, U>::checkUniqueDistances(std::vector<U> distances) {

    std::vector<U> uniqueDistances(distances);

    std::sort(uniqueDistances.begin(), uniqueDistances.end());
    uniqueDistances.erase(std::unique(uniqueDistances.begin(), uniqueDistances.end()), uniqueDistances.end());

    return uniqueDistances.size() > 1;
}

template<typename T, typename V, typename U>
V Knn<T, V, U>::classifyObject(std::vector<T> testObject, U (*metric)(std::vector<T>, std::vector<T>), unsigned long int k) {

    std::vector<std::vector<U>> distances;
    std::vector<V> decisionClasses = this->ds->getDecisionClasses();

    for (V decisionClass : decisionClasses) {
        std::vector<U> distance = this->calculateDistance(testObject, this->ds->getObjectsByDecisionClass(decisionClass), metric);
        distances.push_back(this->getFirstKElements(distance, k));
    }

    return this->getDecision(distances, decisionClasses);
}

template<typename T, typename V, typename U>
KnnScore<V> Knn<T, V, U>::fit(DecisionSystem<T, V> testSystem, U (*metric)(std::vector<T>, std::vector<T>), unsigned long int k) {

    std::vector<V> classifiedDecisions;

    for (long int i = 0; i < testSystem.getObjectCount(); i++) {
        classifiedDecisions.push_back(this->classifyObject(testSystem.getObjectById(i), metric, k));
    }

    return KnnScore<V>(classifiedDecisions, testSystem.getDecisionVector());
}


#endif //ENSEMBLES_KNN_H
