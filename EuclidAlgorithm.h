
#ifndef __EUCLIDALGORITHM_H__
#define __EUCLIDALGORITHM_H__

template <typename T>
T euclid(T a, T b) {
	T c;
	
	while (b) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

template <typename T>
T gcd(T a, T b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

// Extended Euclidean algorithm
// a * x + b * y = d = gcd(a, b)
// also: n * x + b * y = cmmdc(n, b), where n is the modulus
template <typename T>
void euclid(T a, T b, T& d, T& x, T& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		T x0, y0;
		euclid(b, a % b, d, x0, y0);
		x = y0;
		y = x0 - (a / b) * y0;
	}
}

#endif // __EUCLIDALGORITHM_H__
