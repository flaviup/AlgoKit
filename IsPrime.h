
#ifndef __ISPRIME_H__
#define __ISPRIME_H__

template <typename T>
bool IsPrime(T p) {
	if (p < T(2)) {
		return false;
	}
	
	if (p == T(2)) {
		return true;
	} else if ((p & T(1)) == T(0)) {
		return false;
	}

	for (T i = 3; i * i <= p; i += 2) {
		if (p % i == T(0)) {
			return false;
		}
	}
	return true;
}

#endif // __ISPRIME_H__
