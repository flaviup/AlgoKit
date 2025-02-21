
#ifndef __PRIMALITYTESTS_H__
#define __PRIMALITYTESTS_H__

#include <cstdlib>
#include <algorithm> // for std::swap used by SolovayStrassenTest

/* Calculates (a * b) % c taking into account that (a * b) might overflow */
long long mulmod(long long a, long long b, long long c) {
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
long long modulo(long long a, long long b, long long c) {
	long long x = 1, y = a;
    
	while (b > 0) {
        if ((b & 1) == 1) {
            x = mulmod(x, y, c); // (x * y) % c;
        }
        y = mulmod(y, y, c); // (y * y) % c; // squaring the base
        b >>= 1;
    }
    return x % c;
}

/* Fermat's test for checking primality, the more iterations the better is accuracy */
bool FermatTest(long long p, int iterations) {
	if (p < 2) {
        return false;
    }
    
	for (int i = 0; i < iterations; i++) {
        // choose a random integer between 1 and p-1 ( inclusive )
        long long a = rand() % (p - 1) + 1; 
        // modulo is the function we developed above for modular exponentiation.
        if (modulo(a, p - 1, p) != 1) { 
            return false; /* p is definitely composite */
        }
    }
    return true; /* p is probably prime */
}

/* Miller-Rabin primality test, iterations signifies the accuracy of the test */
bool MillerRabinTest(long long p, int iterations) {
    if (p < 2) {
        return false;
    }
    if (p != 2 && (p & 1) == 0) {
        return false;
    }
    long long s = p - 1;
    
	while ((s & 1) == 0) {
        s >>= 1;
    }
    
	for (int i = 0; i < iterations; i++) {
        long long a = rand() % (p - 1) + 1, temp = s;
        long long mod = modulo(a, temp, p);
        
		while (temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = mulmod(mod, mod, p);
            temp <<= 1;
        }
        
		if (mod != p - 1 && (temp & 1) == 0) {
            return false;
        }
    }
    return true;
}

/* Calculates Jacobian(a / n) n > 0 and n is odd */
int calculateJacobian(long long a, long long n) {
    if (!a) { 
		return 0; // (0 / n) = 0
	}
    int ans = 1;
    long long temp = 0;
    
	if (a < 0) {
        a = -a;    // (a / n) = (-a / n) * (-1 / n)
        if (n % 4 == 3) { 
			ans = -ans; // (-1 / n) = -1 if n = 3 ( mod 4 ) 
		}
    }

    if (a == 1) {
		return ans; // (1 / n) = 1
	}

	while (a) {
        if (a < 0) {
            a = -a;    // (a / n) = (-a / n) * (-1 / n)
            if (n % 4 == 3) {
				ans = -ans;    // (-1 / n) = -1 if n = 3 ( mod 4 )
			}
        }
        while ((a & 1) == 0){
            a >>= 1;
            
			if (n % 8 == 3 || n % 8 == 5) {
				ans = -ans;
			}
        }
        std::swap(a, n);
        
		if (a % 4 == 3 && n % 4 == 3) {
			ans = -ans;
		}
        a = a % n; // because (a / p) = (a % p / p ) and a % pi = (a % n) % pi if n % pi = 0
        
		if (a > (n >> 1)) {
			a = a - n;
		}
    }
    
	if (n == 1) {
		return ans;
	}
    return 0; 
}

/* Iterations determine the accuracy of the test */
bool SolovayStrassenTest(long long p, int iterations) {
    if (p < 2) {
		return false;
	}
    
	if (p != 2 && (p & 1) == 0) {
		return false;
	}
    
	for (int i = 0; i < iterations; i++) {
        long long a = rand() % (p - 1) + 1;
        long long jacobian = (p + calculateJacobian(a, p)) % p;
        long long mod = modulo(a, (p - 1) >> 1, p);
        
		if(!jacobian || mod != jacobian) { 
            return false;
        }
    }
    return true;
}

#endif // __PRIMALITYTESTS_H__
