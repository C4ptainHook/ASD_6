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
    Token()=default;
    Token(K,D);
};

template<class K, class D>
Token<K,D>::Token(K _key, D _data) {
key = _key;
data = _data;
}

template<class TData>
class HashT {
public:
    size_t sizeof_table;
    size_t elements_counter;
    std::unique_ptr<Dlist<Token<std::string, int>>[]> table;
public:
    static const uint64_t SEED;
    explicit HashT(size_t num_of_el) {
        sizeof_table = Generator::gen_size(num_of_el);
        elements_counter = num_of_el;
        table = std::make_unique<Dlist<Token<std::string, int>>[]>(sizeof_table);
    }
    size_t How_many_el() const {return elements_counter;}
    template <class TKey, class TFindData>
    friend TFindData& find(const HashT<TFindData>& _table, const TKey& key_to_search);
    void add();
    template<typename U>
    friend void fill_the_table(HashT<TData>&);
};

template<class TData>
const uint64_t HashT<TData>::SEED = 0;

template<class TData>
void HashT<TData>::add() {
    Token<> tok;
    std::string k;
    std::cout<<"Enter key of element\n";
    std::getline(std::cin, tok.key);
    std::cout<<"\nEnter data of element\n";
    std::cin>>tok.data;
    uint64_t idx_temp = MurmurHash64A(tok.key.data(),tok.key.size(), HashT::SEED);
    size_t idx_fin = idx_temp % this->sizeof_table;
    this->table[idx_fin].push_front(tok);
}

template<class TKey, class TData>
TData& find(const HashT<TData>& _table, const TKey& key_to_search) {
    std::string key = key_to_search;
    uint64_t idx_temp = MurmurHash64A(key.data(), key.size(), HashT<TData>::SEED);
    size_t idx_fin = idx_temp % _table.sizeof_table;
    typename Dlist<Token<std::string, int>>::iterator it;
    for (it = _table.table[idx_fin].begin(); it != _table.table[idx_fin].end(); ++it) {
        if ((*it).key == key_to_search) {
            return (*it).data;
        }
    }
    throw std::runtime_error("No such element in the list!");
}

template<class TData>
void fill_the_table(HashT<TData>& _table) {
    for (size_t i = 0; i < _table.elements_counter; ++i) {
        Token mint(Generator::gen_key<std::string>(),Generator::gen_data<int>());
        uint64_t idx_temp = MurmurHash64A(&mint.key,mint.key.size(), HashT<TData>::SEED);
        size_t idx_fin = idx_temp % _table.sizeof_table;
        _table.table[idx_fin].push_front(mint);
    }
}
#endif //ASD_LAB6_HASH_HASHTABLE_H
