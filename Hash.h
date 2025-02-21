
#ifndef __HASH_H__
#define __HASH_H__

#include <cstdlib>
#include <ctime>

// Hash functions (for table lookup)

// Additive hash
unsigned int Add_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0;

	for (int i = 0; i < len; i++) {
		h += p[i];
	}
	return h;
}

// Xor hash
unsigned int Xor_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0;
	
	for (int i = 0; i < len; i++) {
		h ^= p[i];
	}
	return h;
}

// Rotating hash
unsigned int Rotating_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0;
	
	for (int i = 0; i < len; i++ ) {
		h = ( h << 4 ) ^ ( h >> 28 ) ^ p[i];
	}
	return h;
}

// Bernstein hash
unsigned int Bernstein_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0;
	 
	for (int i = 0; i < len; i++) {
		h = 33 * h + p[i];
	}
	return h;
}

// Modified Bernstein hash (using ^ instead of +)
unsigned int ModifiedBernstein_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0;
	 
	for (int i = 0; i < len; i++) {
		h = 33 * h ^ p[i];
	}
	return h;
}

// Shift-Add-Xor hash
unsigned int ShiftAddXor_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0;
	 
	for (int i = 0; i < len; i++) {
		h ^= (h << 5) + (h >> 2) + p[i];
	}
	return h;
}

// FNV(Fowler/Noll/Vo) hash
unsigned int FNV_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 2166136261;
	 
	for (int i = 0; i < len; i++) {
		h = (h * 16777619) ^ p[i];
	}
	return h;
}

// One-at-a-Time hash (Bob Jenkins)
unsigned int Oat_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0;
	
	for (int i = 0; i < len; i++) {
		h += p[i];
		h += (h << 10);
		h ^= (h >> 6);
	}
	h += (h << 3);
	h ^= (h >> 11);
	h += (h << 15);
	return h;
}

// JSW (Julienne Walker) hash (http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx)
unsigned int JSW_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 16777551;
	unsigned char tab[256] = {};
	srand(time(NULL));

	for (int i = 0; i < sizeof(tab) / sizeof(tab[0]); i++) {
		tab[i] = (unsigned char)(rand() & 0xFF);
	}
	 
	for (int i = 0; i < len; i++) {
		h = (h << 1 | h >> 31) ^ tab[p[i]];
	}
	return h;
}

// ELF hash
unsigned int ELF_hash(void* key, int len) {
	unsigned char* p = (unsigned char*)key;
	unsigned int h = 0, g;

	for (int i = 0; i < len; i++) {
		h = (h << 4) + p[i];
		g = h & 0xf0000000L;
		
		if (g != 0) {
			h ^= g >> 24;
		}
		h &= ~g;
	}
	return h;
}

// Bob Jenkins hash

#define hashsize(n) (1U << (n))
#define hashmask(n) (hashsize(n) - 1)
#define mix(a,b,c) \
{ \
	a -= b; a -= c; a ^= (c >> 13); \
	b -= c; b -= a; b ^= (a << 8); \
	c -= a; c -= b; c ^= (b >> 13); \
	a -= b; a -= c; a ^= (c >> 12); \
	b -= c; b -= a; b ^= (a << 16); \
	c -= a; c -= b; c ^= (b >> 5); \
	a -= b; a -= c; a ^= (c >> 3); \
	b -= c; b -= a; b ^= (a << 10); \
	c -= a; c -= b; c ^= (b >> 15); \
}

unsigned int Jenkins_hash(unsigned char* k, unsigned int length, unsigned int initval) {
	unsigned int a, b;
	unsigned int c = initval;
	unsigned int len = length;
	a = b = 0x9e3779b9;
	
	while (len >= 12) {
		a += (k[0] + ((unsigned int)k[1] << 8) + ((unsigned int)k[2] << 16) + ((unsigned int)k[3] << 24));
		b += (k[4] + ((unsigned int)k[5] << 8 ) + ((unsigned int)k[6] << 16) + ((unsigned int)k[7] << 24));
		c += (k[8] + ((unsigned int)k[9] << 8 ) + ((unsigned int)k[10] << 16) + ((unsigned int)k[11] << 24));
		mix(a, b, c);
		k += 12;
		len -= 12;
	}
	c += length;

	switch (len) {
	case 11: c += ((unsigned int)k[10] << 24);
	case 10: c += ((unsigned int)k[9] << 16);
	case 9 : c += ((unsigned int)k[8] << 8);
		/* First byte of c reserved for length */
	case 8 : b += ((unsigned int)k[7] << 24);
	case 7 : b += ((unsigned int)k[6] << 16);
	case 6 : b += ((unsigned int)k[5] << 8);
	case 5 : b += k[4];
	case 4 : a += ((unsigned int)k[3] << 24);
	case 3 : a += ((unsigned int)k[2] << 16);
	case 2 : a += ((unsigned int)k[1] << 8);
	case 1 : a += k[0];
	}
	mix(a, b, c);
	return c;
}

#endif // __HASH_H__
