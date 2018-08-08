#ifndef ENSEMBLES_SHAREDMETHODS_H
#define ENSEMBLES_SHAREDMETHODS_H

template <typename V>
class SharedMethods {

public:
    static bool compareElems(V, V);
};


template<typename V>
bool SharedMethods<V>::compareElems(V i, V j) {

    return (i == j);
}


#endif //ENSEMBLES_SHAREDMETHODS_H
