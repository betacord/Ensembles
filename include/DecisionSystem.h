#ifndef ENSEMBLES_DECISIONSYSTEM_H
#define ENSEMBLES_DECISIONSYSTEM_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>


template <typename T>
class DecisionSystem {

private:
    std::vector<std::vector<T>> ds;
    long int decisionCol;

    void readTxtFile(std::string, char);
    void addRow(std::vector<T>);
    std::vector<T> split(const std::string &str, char);

public:
    DecisionSystem(std::string, char, int);
    std::vector<std::vector<T>> getAll();
    T get(int, int);
    long int objectCount();
    long int predictorCount();
};


template <typename T>
DecisionSystem<T>::DecisionSystem(std::string fileName, char delimitter, int decisionCol) : decisionCol(decisionCol) {

    this->readTxtFile(fileName, delimitter);
}

template <typename T>
void DecisionSystem<T>::readTxtFile(std::string fileName, char delimitter) {

    std::ifstream input(fileName);

    for (std::string line; std::getline(input, line);) {
        std::vector<T> v = this->split(line, delimitter);

        this->addRow(v);
    }
}

template <typename T>
void DecisionSystem<T>::addRow(std::vector<T> row) {

    ds.push_back(row);
}

template <typename T>
std::vector<T> DecisionSystem<T>::split(const std::string &str, char delimitter) {

    std::vector<T> elems;
    std::stringstream ss(str);
    std::string number;

    while(std::getline(ss, number, delimitter)) {
        elems.push_back(std::stof(number));
    }

    return elems;
}

template <typename T>
std::vector<std::vector<T>> DecisionSystem<T>::getAll() {

    return this->ds;
}

template <typename T>
long int DecisionSystem<T>::objectCount() {

    return ds.size();
}

template <typename T>
long int DecisionSystem<T>::predictorCount() {

    return ds[0].size() - 1;
}

template<typename T>
T DecisionSystem<T>::get(int row, int col) {

    return this->ds[row][col];
}


#endif //ENSEMBLES_DECISIONSYSTEM_H
