#ifndef ENSEMBLES_DECISIONSYSTEM_H
#define ENSEMBLES_DECISIONSYSTEM_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "../Shared/SharedMethods.h"


template <typename T, typename V>
class DecisionSystem {

private:
    std::vector<std::vector<T>> ds;
    std::vector<V> decisionVec;
    unsigned long int decisionCol;

    void readTxtFile(const std::string &, char);
    void addRow(std::vector<T>*);
    std::vector<T> split(const std::string &str, char);
    V getDecisionByObjectId(unsigned long int);

public:
    DecisionSystem(std::string, char, unsigned long int);
    DecisionSystem(std::vector<std::vector<T>>, std::vector<V>*, unsigned long int);
    std::vector<std::vector<T>> getAll();
    T get(unsigned long int, unsigned long int);
    unsigned long int getObjectCount();
    unsigned long int getPredictorCount();
    std::vector<T> getPredictor(unsigned long int);
    std::vector<V> getDecisionVector();
    std::vector<V> getDecisionClasses();
    std::vector<std::vector<T>> getObjectsByDecisionClass(V);
    std::vector<T> getObjectById(unsigned long int);
    std::vector<std::vector<T>> getObjectsById(std::vector<unsigned long int>*);
    std::vector<V> getDecisionsById(std::vector<unsigned long int>*);
    DecisionSystem<T, V> getDecisionSystemByIds(std::vector<unsigned long int>*);
};


template <typename T, typename V>
DecisionSystem<T, V>::DecisionSystem(std::string fileName, char delimitter, unsigned long int decisionCol) : decisionCol(decisionCol) {

    this->readTxtFile(fileName, delimitter);
}

template <typename T, typename V>
void DecisionSystem<T, V>::readTxtFile(const std::string &fileName, char delimitter) {

    std::ifstream input(fileName);

    for (std::string line; std::getline(input, line);) {
        std::vector<T> v = this->split(line, delimitter);

        this->addRow(&v);
    }
}

template<typename T, typename V>
DecisionSystem<T, V>::DecisionSystem(std::vector<std::vector<T>> objects, std::vector<V> *decisions, unsigned long int decisionCol)
    : decisionCol(decisionCol) {

        for (unsigned long int i = 0; i < objects.size(); i++) {
            this->ds.push_back(objects[i]);
        }

        this->decisionVec = std::vector<V>(*decisions);
}

template <typename T, typename V>
void DecisionSystem<T, V>::addRow(std::vector<T> *row) {

    ds.push_back(*row);
}

template <typename T, typename V>
std::vector<T> DecisionSystem<T, V>::split(const std::string &str, char delimitter) {

    std::vector<T> elems;
    std::stringstream ss(str);
    std::string number;

    unsigned long int i = 0;

    while (std::getline(ss, number, delimitter)) {
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
T DecisionSystem<T, V>::get(unsigned long int row, unsigned long int col) {

    return this->ds[row][col];
}

template<typename T, typename V>
std::vector<T> DecisionSystem<T, V>::getPredictor(unsigned long int index) {

    std::vector<T> result;
    result.reserve(this->ds.size());

    for (unsigned long int i = 0; i < this->ds.size(); i++) {
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
std::vector<T> DecisionSystem<T, V>::getObjectById(unsigned long int objectId) {

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

    for (unsigned long int i = 0; i < this->ds.size(); i++) {
        if (getDecisionByObjectId(i) == decisionClass) {
            result.push_back(this->getObjectById(i));
        }
    }

    return result;
}

template<typename T, typename V>
std::vector<std::vector<T>> DecisionSystem<T, V>::getObjectsById(std::vector<unsigned long int> *ids) {

    std::vector<std::vector<T>> objects = {};

    for (unsigned long int i : *ids) {
        objects.push_back(this->getObjectById(i));
    }

    return objects;
}

template<typename T, typename V>
std::vector<V> DecisionSystem<T, V>::getDecisionsById(std::vector<unsigned long int> *ids) {

    std::vector<V> decisions = {};

    for (unsigned long int i : *ids) {
        decisions.push_back(this->getDecisionByObjectId(i));
    }

    return decisions;
}

template<typename T, typename V>
DecisionSystem<T, V> DecisionSystem<T, V>::getDecisionSystemByIds(std::vector<unsigned long int> *objectsId) {

    std::vector<std::vector<T>> objects = this->getObjectsById(objectsId);
    std::vector<V> decisions = this->getDecisionsById(objectsId);

    DecisionSystem<T, V> decisionSystem(objects, &decisions, this->decisionCol);

    return decisionSystem;
}


#endif //ENSEMBLES_DECISIONSYSTEM_H
