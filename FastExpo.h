
#ifndef __FASTEXPO_H__
#define __FASTEXPO_H__

/* Calculates (a * b) with fast exponentiation algorithm */
long long FastMul(long long a, long long b) {
    long long x = 0, y = a;
    
	while (b > 0) {
        if ((b & 1) == 1) {
            x += y;
        }
        y <<= 1;
        b >>= 1;
    }
    return x;
}

/* Calculates (a * b) % c taking into account that (a * b) might overflow */
long long MulMod(long long a, long long b, long long c) {
    long long x = 0, y = a % c;
    
	while (b > 0) {
        if ((b & 1) == 1) {
            x = (x + y) % c;
        }
        y = (y << 1) % c;
        b >>= 1;
    }
    return x % c;
}

/* Calculates (a to the power of b) % c */
long long Modulo(long long a, long long b, long long c) {
	long long x = 1, y = a;
    
	while (b > 0) {
        if ((b & 1) == 1) {
            x = MulMod(x, y, c); // (x * y) % c;
        }
        y = MulMod(y, y, c); // (y * y) % c; // squaring the base
        b >>= 1;
    }
    return x % c;
}

#endif // __FASTEXPO_H__
