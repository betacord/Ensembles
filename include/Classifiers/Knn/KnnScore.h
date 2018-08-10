#ifndef ENSEMBLES_KNNSCORE_H
#define ENSEMBLES_KNNSCORE_H

#include <iostream>

#include "../../Shared/SharedMethods.h"

template <typename V>
class KnnScore {

private:
    std::vector<V> classifiedDecisions;
    std::vector<V> realDecisions;

    unsigned long int getTrueClassified(V);
    unsigned long int getFalseClassified(V);
    unsigned long int getGrabbedObjects(V);
    unsigned long int getCountOfObjects(V);

public:
    KnnScore(std::vector<V>, std::vector<V>);
    double getTPR(V);
    double getGlobalTPR();
    double getAccuracy(V);
    double getCoverage(V);
};


template<typename V>
KnnScore<V>::KnnScore(std::vector<V> classified, std::vector<V> real) : classifiedDecisions(classified), realDecisions(real) {

}

template<typename V>
unsigned long int KnnScore<V>::getTrueClassified(V decisionClass) {

    unsigned long int trueClassified = 0;

    for (unsigned long int i = 0; i < this->realDecisions.size(); i++) {
        if (this->classifiedDecisions[i] == decisionClass) {
            if (this->classifiedDecisions[i] != V() && this->classifiedDecisions[i] == this->realDecisions[i]) {
                trueClassified++;
            }
        }
    }

    return trueClassified;
}

template<typename V>
unsigned long int KnnScore<V>::getFalseClassified(V decisionClass) {

    unsigned long int falseClassified = 0;

    for (unsigned long int i = 0; i < this->realDecisions.size(); i++) {
        if (this->classifiedDecisions[i] == decisionClass) {
            if (this->classifiedDecisions[i] != V() && this->classifiedDecisions[i] != this->realDecisions[i]) {
                falseClassified++;
            }
        }
    }

    return falseClassified;
}

template<typename V>
unsigned long int KnnScore<V>::getGrabbedObjects(V decisionClass) {

    unsigned long int grabbedObjects = 0;

    for (unsigned long int i = 0; i < this->classifiedDecisions.size(); i++) {
        if (this->classifiedDecisions[i] == decisionClass) {
            grabbedObjects++;
        }
    }

    return grabbedObjects;
}

template<typename V>
unsigned long int KnnScore<V>::getCountOfObjects(V decisionClass) {

    unsigned long int count = 0;

    for (V realDecision : this->realDecisions) {
        if (realDecision == decisionClass) {
            count++;
        }
    }

    return count;
}

template<typename V>
double KnnScore<V>::getTPR(V decisionClass) {

    unsigned long int trueClassified = this->getTrueClassified(decisionClass);
    unsigned long int falseClassified = this->getFalseClassified(decisionClass);

    return (double)trueClassified / (trueClassified + falseClassified);
}

template<typename V>
double KnnScore<V>::getGlobalTPR() {

    std::vector<V> uniqueDecisions = SharedMethods<V>::getUniqueElements(this->realDecisions);

    unsigned long int globalTrueClassified = 0;
    unsigned long int globalFalseClassified = 0;

    for (V decisionClass : uniqueDecisions) {
        globalTrueClassified += this->getTrueClassified(decisionClass);
        globalFalseClassified += this->getFalseClassified(decisionClass);
    }

    return (double)globalTrueClassified / (globalTrueClassified + globalFalseClassified);
}

template<typename V>
double KnnScore<V>::getAccuracy(V decisionClass) {

    unsigned long int trueClassified = this->getTrueClassified(decisionClass);
    unsigned long int grabbedObjects = this->getGrabbedObjects(decisionClass);

    return (double)trueClassified / grabbedObjects;
}

template<typename V>
double KnnScore<V>::getCoverage(V decisionClass) {

    unsigned long int grabbedObjects = this->getGrabbedObjects(decisionClass);
    unsigned long int countOfObjects = this->getCountOfObjects(decisionClass);

    return (double)grabbedObjects / countOfObjects;
}


#endif //ENSEMBLES_KNNSCORE_H
