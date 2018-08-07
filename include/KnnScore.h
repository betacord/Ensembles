#ifndef ENSEMBLES_KNNSCORE_H
#define ENSEMBLES_KNNSCORE_H

#include <iostream>


template <typename V>
class KnnScore {

private:
    std::vector<V> classifiedDecisions;
    std::vector<V> realDecisions;

public:
    KnnScore(std::vector<V>, std::vector<V>);
    float getTPR(V);
};


template<typename V>
KnnScore<V>::KnnScore(std::vector<V> classified, std::vector<V> real) : classifiedDecisions(classified), realDecisions(real) {

}

template<typename V>
float KnnScore<V>::getTPR(V decisionClass) {

    unsigned long int trueClassified = 0;
    unsigned long int falseClassified = 0;

    for (long int i = 0; i < this->realDecisions.size(); i++) {
        if (this->classifiedDecisions[i] == decisionClass) {

            if (this->classifiedDecisions[i] != V() && this->classifiedDecisions[i] == this->realDecisions[i]) {
                trueClassified += 1;
            }

            if (this->classifiedDecisions[i] != V() && this->classifiedDecisions[i] != this->realDecisions[i]) {
                falseClassified += 1;
            }
        }
    }

    return (float)trueClassified / (trueClassified + falseClassified);
}


#endif //ENSEMBLES_KNNSCORE_H
