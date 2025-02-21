
#ifndef __ERATOSTHENESSIEVE_H__
#define __ERATOSTHENESSIEVE_H__

template <typename T, int MAXSIZE = 100000000/2/8+1>
int getTheNumber(T n) {
	T i = 0, j = 0, nr = 1;
	char[] p = new char[MAXSIZE]; //(p[i>>3]&(1<<(i&7))) == 0 if 2*i + 1 is prime
	
	for (i = 1; ((i * i) << 1) + (i << 1) <= n; i += 1) {     
		if ((p[i >> 3] & (1 << (i & 7))) == 0) {
			for (j = ((i * i) << 1) + (i << 1); (j << 1) + 1 <= n; j += (i << 1) + 1) {
				p[j >> 3] |= (1 << (j & 7));
			}
		}
	}
	
	for (i = 1; 2 * i + 1 <= n; ++i) {
		if ((p[i >> 3] & (1 << (i & 7))) == 0) {
			nr++;
		}
	}
	return nr;
}

#endif // __ERATOSTHENESSIEVE_H__