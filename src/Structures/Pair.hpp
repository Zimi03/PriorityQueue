//
// Created by grzegorz on 23.05.24.
//

#ifndef HASH_TABLES_PAIR_HPP
#define HASH_TABLES_PAIR_HPP
#include "iostream"
#include "../Tools/Utils.hpp"

template <typename K, typename V>
struct  Pair {
public:
    K key;
    V value;

    Pair(const Pair &para){
        key = para.key;
        value = para.value;
    };

//    Pair(int size){
//        key = Utils::generateNumber(size * 5);
//        value = Utils::generateNumber(size);
//    };
//
//    Pair(Pair* &data, int size){
//        int index = Utils::generateNumber(size);
//        key = data[index].key;
//        value = data[index].value;
//    }

    Pair(K key_, V val) : key(key_), value(val) {};
    Pair() = default;
    ~Pair() = default;


    friend std::ostream& operator<<(std::ostream& os, const Pair<K, V>& p) {
        os << "{K: " << p.key << " |V: " << p.value << "}";
        return os;
    }

    bool operator==(const Pair<K, V>& other) const {
        return key == other.key;
    }

    bool operator!=(const Pair<K, V>& other) const {
        return !(*this == other);
    }

    friend bool operator<(const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
        return lhs.key < rhs.key;
    }

    friend int operator%(const Pair<K, V>& lhs, int mod) {
        return lhs.key % mod;
    }

    // Operator /
    friend int operator/(const Pair<K, V>& lhs, int div) {
        return lhs.key/div;
    }
};

template class Pair<PriorityValueOrder, int>;

#endif //HASH_TABLES_PAIR_HPP
