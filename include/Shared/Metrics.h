#ifndef ENSEMBLES_METRICS_H
#define ENSEMBLES_METRICS_H

#include <iostream>
#include <vector>
#include <cmath>

template <typename T, typename U>
class Metrics {

public:
    static U euclidean(std::vector<T> *, std::vector<T> *);
};


template<typename T, typename U>
U Metrics<T, U>::euclidean(std::vector<T> *test, std::vector<T> *train) {

    T score = 0;

    for (unsigned long int i = 0; i < test->size(); i++) {
        score +=  pow(test->at(i) - train->at(i), 2);
    }

    return sqrt(score);
}

#endif //ENSEMBLES_METRICS_H
