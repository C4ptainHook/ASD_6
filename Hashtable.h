#ifndef ASD_LAB6_HASH_HASHTABLE_H
#define ASD_LAB6_HASH_HASHTABLE_H
#include <iostream>
#include <memory>
#include "DList.h"
#include "Murmurhash.h"
#include "Generator.h"

template<class K, class D>
struct Token {
    K key;
    D data;
public:
    Token(K,D);
};

template<class K, class D>
Token<K,D>::Token(K _key, D _data) {
key = _key;
data = _data;
}

class HashT {
    size_t sizeof_table;
    size_t elements_counter;
    std::unique_ptr<Dlist<Token<std::string, int>>[]> table;
public:
    explicit HashT(size_t num_of_el) {
        sizeof_table = Generator::gen_size(num_of_el);
        elements_counter = num_of_el;
        table = std::make_unique<Dlist<Token<std::string, int>>[]>(sizeof_table);
    }
    friend size_t Generator::gen_size(size_t elements);
    size_t How_many_el() const {return elements_counter;}
};
#endif //ASD_LAB6_HASH_HASHTABLE_H
