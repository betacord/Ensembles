#ifndef ENSEMBLES_SHAREDMETHODS_H
#define ENSEMBLES_SHAREDMETHODS_H

#include <iostream>
#include <unordered_map>
#include <sstream>

template <typename V>
class SharedMethods {

public:
    static bool compareElems(V, V);
    static std::vector<V> getUniqueElements(std::vector<V>*);
    static unsigned long int getIdOfMaxValueFromMap(std::unordered_map<unsigned long int, V> map);
};


template<typename V>
bool SharedMethods<V>::compareElems(V i, V j) {

    return (i == j);
}

template<typename V>
std::vector<V> SharedMethods<V>::getUniqueElements(std::vector<V> *elements) {

    std::vector<V> uniqueElements(*elements);

    std::sort(uniqueElements.begin(), uniqueElements.end());
    uniqueElements.erase(std::unique(uniqueElements.begin(), uniqueElements.end()), uniqueElements.end());

    return uniqueElements;
}

template<typename V>
unsigned long int SharedMethods<V>::getIdOfMaxValueFromMap(std::unordered_map<unsigned long, V> map) {

    V maxValue = V();

    for (unsigned long int i = 0; i < map.size(); i++) {
        if (map[i] > maxValue) {
            return i;
        }
    }

    return 0;
}


#endif //ENSEMBLES_SHAREDMETHODS_H
