#ifndef ASD_LAB6_HASH_HASHTABLE_H
#define ASD_LAB6_HASH_HASHTABLE_H
#include <iostream>
#include <memory>
#include "DList.h"
#include "Murmurhash.h"
#include "Generator.h"

template<class K=std::string, class D=int>
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
    size_t How_many_el() const {return elements_counter;}
    friend void fill_the_table(HashT& obj);
};

void fill_the_table(HashT& _table) {
    const uint64_t SEED = 0;
    for (size_t i = 0; i < _table.elements_counter; ++i) {
        Token mint(Generator::gen_key<std::string>(),Generator::gen_data<int>());
        uint64_t idx_temp = MurmurHash64A(&mint.key,mint.key.size(), SEED);
        size_t idx_fin = idx_temp % _table.sizeof_table;
        _table.table[idx_fin].push_front(mint);
    }
}
#endif //ASD_LAB6_HASH_HASHTABLE_H
