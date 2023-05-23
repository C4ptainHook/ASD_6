#ifndef ASD_LAB6_HASH_MURMURHASH_H
#define ASD_LAB6_HASH_MURMURHASH_H

void SetAffinity ( int cpu );
#include <cstdint>
#include <string>

#define	FORCE_INLINE __attribute__((always_inline))

FORCE_INLINE uint32_t rotl32 ( uint32_t x, int8_t r ){ return (x << r) | (x >> (32 - r)); }
FORCE_INLINE uint64_t rotl64 ( uint64_t x, int8_t r ){ return (x << r) | (x >> (64 - r)); }
FORCE_INLINE uint32_t rotr32 ( uint32_t x, int8_t r ){ return (x >> r) | (x << (32 - r)); }
FORCE_INLINE uint64_t rotr64 ( uint64_t x, int8_t r ){ return (x >> r) | (x << (64 - r)); }
FORCE_INLINE unsigned long long int rdtsc(){ unsigned long long int x; __asm__ volatile ("rdtsc" : "=A" (x)); return x; }

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)
#define	ROTR32(x,y)	rotr32(x,y)
#define ROTR64(x,y)	rotr64(x,y)
#define BIG_CONSTANT(x) (x##LLU)
//#define _stricmp strcasecmp

#endif //ASD_LAB6_HASH_MURMURHASH_H

#ifdef __cplusplus
extern "C" {
#endif

uint32_t MurmurHash2        ( const void * key, int len, uint32_t seed );
uint32_t MurmurHash2A       ( const void * key, int len, uint32_t seed );
uint32_t MurmurHashNeutral2 ( const void * key, int len, uint32_t seed );
uint32_t MurmurHashAligned2 ( const void * key, int len, uint32_t seed );
uint64_t MurmurHash64A      ( const void * key, int len, uint64_t seed );
uint64_t MurmurHash64B      ( const void * key, int len, uint64_t seed );

uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed )
{
    const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (len/8);

    while(data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch(len & 7)
    {
        case 7: h ^= ((uint64_t) data2[6]) << 48;
        case 6: h ^= ((uint64_t) data2[5]) << 40;
        case 5: h ^= ((uint64_t) data2[4]) << 32;
        case 4: h ^= ((uint64_t) data2[3]) << 24;
        case 3: h ^= ((uint64_t) data2[2]) << 16;
        case 2: h ^= ((uint64_t) data2[1]) << 8;
        case 1: h ^= ((uint64_t) data2[0]);
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

#ifdef __cplusplus
}
#endif


