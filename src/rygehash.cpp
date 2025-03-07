#include "rygehash.h"
#include <cstdint>
#include <cstring>
#include <stdint.h>
#include <libc.h>

typedef int64_t word_t;

inline int64_t twist(int64_t hash, int64_t word) {
    int w = sizeof(word) * 8;

    word *= 0x9908b0dfUL;
    word ^= word >> 15;
    word += word >> 17;

    hash = 1812433253UL * (hash ^ (hash >> (w-2))) + word;
    return hash;
}

uint64_t rshash64( const void * key, int len, uint64_t seed)
{
    int64_t hash = seed;
    // Warm up hash
    // for(int i=0; i<16; i++) hash = twist(hash, i);

    // Align with wordsize
    int wordsize = sizeof(word_t);
    int alignment = (len % wordsize) > 0 ? 1 : 0;
    int words = len/wordsize + alignment;
    void * buffer = calloc(words, wordsize);
    memcpy(buffer, key, len);

    word_t * data = (word_t *) buffer;

    for (int index = 0; index < words; ++index)
    {
        hash = twist(hash, index + data[index]);
    }

    free(buffer);

    return twist(hash, len);
}

// blocksize of 16 workes really well! Also, uint works really well.
#define BLOCKSIZE 16 
uint64_t rbhash64( const void * key, int len, int64_t seed)
{
    int64_t hash = seed;
    int64_t block[BLOCKSIZE];

    // Align with wordsize
    int wordsize = sizeof(word_t);
    int alignment = (len % wordsize) > 0 ? 1 : 0;
    int words = len/wordsize + alignment;

    void * buffer = calloc(words, wordsize);
    memcpy(buffer, key, len);

    word_t * data = (word_t *) buffer;

    for(int i=0; i<BLOCKSIZE;i++){ 
        seed = twist(seed, i);
        block[i]=seed;
    }

    for(int j=0; j<words; j+=BLOCKSIZE) {
        for(int i=0; i+j<words && i<BLOCKSIZE; i++) {
            block[i] = (block[i] * 65521) + data[i+j];
        }
        for(int i=0;i<BLOCKSIZE;i++) 
            hash = twist(hash, block[i]);
    }

    free(buffer);

    return twist(hash, len);
}


uint64_t rwhash64( const void * key, int len, int64_t seed)
{
    int64_t hash = seed;
    // for(int i=0; i<16;i++) hash = twist(hash, i);

    // Align with wordsize
    int wordsize = sizeof(word_t);
    int alignment = (len % wordsize) > 0 ? 1 : 0;
    int words = 1 + len/wordsize + alignment;
    void * buffer = calloc(words, wordsize);
    memcpy(buffer, key, len);

    int8_t * data = (int8_t*) buffer;
    for(int i=0; i<len; i++) {
        word_t word = ((word_t *) (&data[i]))[0];
        hash = twist(hash, word);
    }

    free(buffer);

    return twist(hash, len);
}