#ifndef ENSEMBLES_DECISIONSYSTEM_H
#define ENSEMBLES_DECISIONSYSTEM_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "SharedMethods.h"


template <typename T, typename V>
class DecisionSystem {

private:
    std::vector<std::vector<T>> ds;
    std::vector<V> decisionVec;
    unsigned long int decisionCol;

    void readTxtFile(std::string, char);
    void addRow(std::vector<T>);
    std::vector<T> split(const std::string &str, char);
    V getDecisionByObjectId(unsigned long int);

public:
    DecisionSystem(std::string, char, int);
    std::vector<std::vector<T>> getAll();
    T get(int, int);
    unsigned long int getObjectCount();
    unsigned long int getPredictorCount();
    std::vector<T> getPredictor(long int);
    std::vector<V> getDecisionVector();
    std::vector<V> getDecisionClasses();
    std::vector<std::vector<T>> getObjectsByDecisionClass(V);
    std::vector<T> getObjectById(long int);
};


template <typename T, typename V>
DecisionSystem<T, V>::DecisionSystem(std::string fileName, char delimitter, int decisionCol) : decisionCol(decisionCol) {

    this->readTxtFile(fileName, delimitter);
}

template <typename T, typename V>
void DecisionSystem<T, V>::readTxtFile(std::string fileName, char delimitter) {

    std::ifstream input(fileName);

    for (std::string line; std::getline(input, line);) {
        std::vector<T> v = this->split(line, delimitter);

        this->addRow(v);
    }
}

template <typename T, typename V>
void DecisionSystem<T, V>::addRow(std::vector<T> row) {

    ds.push_back(row);
}

template <typename T, typename V>
std::vector<T> DecisionSystem<T, V>::split(const std::string &str, char delimitter) {

    std::vector<T> elems;
    std::stringstream ss(str);
    std::string number;

    long int i = 0;

    while(std::getline(ss, number, delimitter)) {
        if (i == this->decisionCol) {
            this->decisionVec.push_back(number);
        } else {
            elems.push_back(std::stof(number));
        }

        i++;
    }

    return elems;
}

template <typename T, typename V>
std::vector<std::vector<T>> DecisionSystem<T, V>::getAll() {

    return this->ds;
}

template <typename T, typename V>
unsigned long int DecisionSystem<T, V>::getObjectCount() {

    return this->ds.size();
}

template <typename T, typename V>
unsigned long int DecisionSystem<T, V>::getPredictorCount() {

    return this->ds[0].size() - 1;
}

template<typename T, typename V>
T DecisionSystem<T, V>::get(int row, int col) {

    return this->ds[row][col];
}

template<typename T, typename V>
std::vector<T> DecisionSystem<T, V>::getPredictor(long int index) {

    std::vector<T> result;
    result.reserve(this->ds.size());

    for (int i = 0; i < this->ds.size(); i++) {
        result.push_back(this->ds[i][index]);
    }

    return result;
}

template<typename T, typename V>
std::vector<V> DecisionSystem<T, V>::getDecisionVector() {

    return this->decisionVec;
}

template<typename T, typename V>
std::vector<V> DecisionSystem<T, V>::getDecisionClasses() {

    std::vector<V> uniqueDecisions(this->decisionVec);

    std::sort(uniqueDecisions.begin(), uniqueDecisions.end());
    uniqueDecisions.erase(std::unique(uniqueDecisions.begin(), uniqueDecisions.end()), uniqueDecisions.end());

    return uniqueDecisions;
}

template<typename T, typename V>
std::vector<T> DecisionSystem<T, V>::getObjectById(long int objectId) {

    std::vector<T> result = this->ds[objectId];

//    result.erase(result.begin(), result.begin() + 1);

    return result;
}

template<typename T, typename V>
V DecisionSystem<T, V>::getDecisionByObjectId(unsigned long int objectId) {

    return this->decisionVec[objectId];
}

template<typename T, typename V>
std::vector<std::vector<T>> DecisionSystem<T, V>::getObjectsByDecisionClass(V decisionClass) {

    std::vector<std::vector<T>> result;

    for (long int i = 0; i < this->ds.size(); i++) {
        if (getDecisionByObjectId(i) == decisionClass) {
            result.push_back(this->getObjectById(i));
        }
    }

    return result;
}


#endif //ENSEMBLES_DECISIONSYSTEM_H
