
#ifndef __BITS_H__
#define __BITS_H__

// Bitwise operations

// You can use also preprocessing (storing 2^16 or 2^8 sized tables with the answers) instead of the techniques below

// For GCC: __builtin_popcount - counts the number of 1s
// no underlying x86 machine instruction, but uses the table-based lookup method

// Number of 1s in n
int BitCount(long n) {
	int num = 0;
	
	for (int i = 0; i < 32; i++) {
		if (n & (1 << i)) { 
			num++;
		}
	}
	return num;
}

// Number of 1s in n
int BitCount2(long n) {
	int num = 0;
	
	if (n) {
		do {
			num++; 
		} while (n &= n - 1);
	}
	return num;
}

// Parity of the number of 1s in n
int BitParity(long n) {
	int num = 0;
	
	for (int i = 0; i < 32; i++) {
		if (n & (1 << i)) {
			num ^= 1;
		}
	}
	return num;
}

// Parity of the number of 1s in n
int BitParity2(long n) {
	int num = 0;
	
	if (n) {
		do {
			num ^= 1; 
		} while (n &= n - 1);
	}
	return num;
}

// Parity of the number of 1s in n
int BitParity3(long n) {
	n = ((0xFFFF0000 & n) >> 16) ^ (n & 0xFFFF);
	n = ((0xFF00 & n) >> 8) ^ (n & 0xFF);
	n = ((0xF0 & n) >> 4) ^ (n & 0xF);
	n = ((12 & n) >> 2) ^ (n & 3);
	n = ((2 & n) >> 1) ^ (n & 1);
	return n;
}

// For GCC
// __builtin_ctz (count trailing zeros) and __builtin_clz (count leading zeros)
// (undefined for a zero argument)
// uses BSF (bit scan forward) and BSR (bit scan reverse) underlying 386 CPU instructions

// The rightmost (lowest significant) 1 of n
inline int Low1(long n) {
	return n ^ (n & (n - 1)); // n & ~(n - 1); ((n ^ (n - 1)) & n)? 
}

// The leftmost (highest significant) 1 of n
int High1(long n) {
	long num = 0;
	
	if (!n) return -1;

	if (0xFFFF0000 & n) {
		n = (0xFFFF0000 & n)>>16;
		num += 16;
	}
	
	if (0xFF00 & n) {
		n = (0xFF00 & n) >> 8;
		num += 8;
	}
	
	if (0xF0 & n) {
		n = (0xF0 & n) >> 4;
		num += 4;
	}
	
	if (12 & n) {
		n = (12 & n) >> 2;
		num += 2;
	}
	
	if (2 & n) {
		n = (2 & n) >> 1;
		num += 1;
	}
	return 1 << num;
}

// The index of the leftmost (highest significant) 1 of n
int IndexHigh1(long n) {
	n = n | (n >> 1);
	n = n | (n >> 2);
	n = n | (n >> 4);
	n = n | (n >> 8);
	n = n | (n >> 16);
	return BitCount2(n) - 1;
}

// Is n a power of two?
bool IsTwoPower(long n) {
	return (n & (n - 1)) == 0 ;
}

long ReverseBits(long x) {
	x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
	x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
	x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
	x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
	x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16);
	return x;
}

// All k-element subsets of {0, 1, …, N-1}
void kSubsets(int k, int N) {
	int s = (1 << k) - 1;
	
	while (!(s & 1 << N)) {
		// do stuff with s
		int lo = s & ~(s - 1);       // lowest one bit
		int lz = (s + lo) & ~s;      // lowest zero bit above lo
		s |= lz;                     // add lz to the set
		s &= ~(lz - 1);              // reset bits below lz
		s |= (lz / lo / 2) - 1;      // put back right number of bits at end
	}
}

// All the subsets of a subset (in reverse order): i = (i - 1) & superset
// x ? y : -y, where x is 0 or 1 is equivalent to: (-x ^ y) + x

#endif // __BITS_H__
