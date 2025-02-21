
#ifndef __BINARYSEARCH_H__
#define __BINARYSEARCH_H__

#include <cassert>

template <class T>
int BinarySearch(const T* a, int n, const T& v) {
	assert(a != NULL);
	assert(n > 0);
	int low = 0;
	int high = n - 1;

	while (low < high) {
		int mid = low + ((high - low) >> 1);
		
		if (a[mid] < v) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}
	return low;
	/*if (!(v < a[low]) && !(a[low] < v)) {
		return low;
	}
	return -1;*/
}

template <class T>
int binary_search(T* a, int N, T val)
{
	int i = 0, step = 0;
	for (step = 1; step < N; step <<= 1);
	for (i = 0; step; step >>= 1) {
		if (i + step < N && !(val < a[i + step])) {
			i += step;
		}
	}
	return i;
	/*if (!(val < a[i]) && !(a[i] < val)) {
		return i;
	}
	return -1;*/
}

#endif // __BINARYSEARCH_H__
