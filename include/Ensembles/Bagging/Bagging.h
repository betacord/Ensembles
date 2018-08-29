#ifndef ENSEMBLES_BAGGING_H
#define ENSEMBLES_BAGGING_H

#include <vector>

#include "../../DecisionSystem/DecisionSystem.h"
#include "../../Validators/Bootstrap/Bootstrap.h"
#include "../../Classifiers/Knn/KnnScore.h"

template<typename T, typename V, typename U>
class Bagging {

private:
    DecisionSystem<T, V> *ds;

public:
    explicit Bagging(DecisionSystem<T, V>*);
    std::tuple<unsigned long int, KnnScore<V>> findBestK(unsigned int, unsigned long int, unsigned long int, U (*metric)(std::vector<T>*, std::vector<T>*));
};


template<typename T, typename V, typename U>
Bagging<T, V, U>::Bagging(DecisionSystem<T, V> *decisionSystem) {

    this->ds = decisionSystem;
}

template<typename T, typename V, typename U>
std::tuple<unsigned long int, KnnScore<V>> Bagging<T, V, U>::findBestK(unsigned int iterations, unsigned long int minK, unsigned long int maxK, U (*metric)(std::vector<T> *, std::vector<T> *)) {

    std::vector<unsigned long int> scores(maxK - minK + 1);
    unsigned long int currentBestK;

    Bootstrap<T, V, U> bootstrap(this->ds);

    DecisionSystem<T, V> masterTrainingSet = bootstrap.getTrainingSet();
    DecisionSystem<T, V> masterTestSet = bootstrap.getTestSet();

    for (unsigned int i = 0; i < iterations; i++) {
        Bootstrap<T, V, U> tmpBootstrap(&masterTrainingSet);

        currentBestK = std::get<0>(tmpBootstrap.getBestK(minK, maxK, metric));
        scores[currentBestK - minK]++;
    }

    unsigned long int bestK = std::distance(scores.begin(), std::max_element(scores.begin(), scores.end())) + minK;

    Knn<T, V, U> knn(&masterTrainingSet);

    return std::make_tuple(bestK, knn.fit(&masterTestSet, metric, bestK));
}


#endif //ENSEMBLES_BAGGING_H
