#ifndef ASD_LAB6_HASH_GENERATOR_H
#define ASD_LAB6_HASH_GENERATOR_H

#include <random>

#define COEF_OF_FULLNESS 2

namespace Generator {
    template<class K>
    K &gen_key() {
        K key;
        std::random_device rd;
        std::mt19937 gen(rd());
        static char charset[] = "0123456789"
                                "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const unsigned int ChSize = sizeof(charset) - 1;
        std::uniform_int_distribution<int> dist_for_keys(0, ChSize);
        for (const auto &c: charset) {
            key += charset[dist_for_keys(gen)];
        }
        return key;
    }

    template<class D>
    D &gen_data() {
        D data;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist_for_data(0, 10000);
        return data;
    }

    size_t gen_size(size_t elements) {
        bool isPrime(size_t n);
        size_t findNextPrime(size_t value);
        size_t table_length = static_cast<size_t>(static_cast<double>(elements) / COEF_OF_FULLNESS);
        table_length = findNextPrime(table_length);
        return table_length;
    }

    bool isPrime(size_t n) {
        if (n <= 1) {
            return false;
        }

        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }

    size_t findNextPrime(size_t value) {
        size_t prime = value + 1;

        while (!isPrime(prime)) {
            ++prime;
        }

        return prime;
    }
}
#endif //ASD_LAB6_HASH_GENERATOR_H
