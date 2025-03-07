//-----------------------------------------------------------------------------
// Adler 32 and Adler 64

#ifndef _RYGEHASH_H_
#define _RYGEHASH_H_

//-----------------------------------------------------------------------------
// Platform-specific functions and macros

// Microsoft Visual Studio

#if defined(_MSC_VER) && (_MSC_VER < 1600)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

// Other compilers

#else	// defined(_MSC_VER)

#include <stdint.h>

#endif // !defined(_MSC_VER)

//-----------------------------------------------------------------------------

uint64_t rshash64        ( const void * key, int len, uint64_t seed );
uint64_t rbhash64        ( const void * key, int len, int64_t seed );
uint64_t rwhash64       ( const void * key, int len, int64_t seed);

inline void rshash64_test ( const void * key, int len, uint32_t seed, void * out )
{
  *(uint64_t*)out = rshash64(key,len,seed);
}

inline void rbhash64_test ( const void * key, int len, uint32_t seed, void * out )
{
  *(uint64_t*)out = rbhash64(key,len,seed);
}

inline void rwhash64_test ( const void * key, int len, uint32_t seed, void * out )
{
  *(uint64_t*)out = rwhash64(key,len,seed);
}
//-----------------------------------------------------------------------------

#endif // _RYGEHASH_H_

