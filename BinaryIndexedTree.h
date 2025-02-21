

// Binary Indexed Tree: O(n)-space complexity, O(logN) time complexity for both operations
// Problem definition:
// We have a vector of numbers and we have the following 2 operations:
// 1 - INCREMENT/DECREMENT an element from vector
// 2 - compute the SUM of a SUBSEQUENCE from the vector

#ifndef __BINARYINDEXEDTREE_H__
#define __BINARYINDEXEDTREE_H__

#define zeros(x) ((x ^ (x - 1)) & x) // the right-most 1 digit: =2^k, where k is the number of trailing binary 0s of x

// V[x] += quantity
// BIT[x]: sum of elements V[x-2^k+1...x], where k = the number of trailing binary 0s of x 
void Add(int BIT[], int x, int quantity) {
	for (int i = x; i <= N; i += zeros(i)) {
		BIT[i] += quantity;
	}
}

// Sum of V[L...U] = Compute(U) - Compute(L - 1)
int Compute(int BIT[], int x) {
	int ret = 0;
	
	for (int i = x; i > 0; i -= zeros(i)) {
		ret += BIT[i];
	}
	return ret;
}

#endif // __BINARYINDEXEDTREE_H__
