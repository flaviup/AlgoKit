
// BubbleSort
// InsertionSort
// SelectionSort
// MergeSort
// QuickSort
// ShellSort
// RadixSort
// HeapSort

#ifndef __SORTING_H__
#define __SORTING_H__

const int MAXDIM = 1000;
int N = MAXDIM, A[MAXDIM], B[MAXDIM];

void MergeSort(int l, int r) {
	int m = (l + r) >> 1, i, j, k;
	
	if (l == r) return;
	
	MergeSort(l, m);
	MergeSort(m + 1, r);

	for (i=l, j=m+1, k=l; i<=m || j<=r; )
		if (j > r || (i <= m && A[i] < A[j]))
			B[k++] = A[i++];
		else
			B[k++] = A[j++];

	for (k = l; k <= r; k++)
		A[k] = B[k];
}

int Partition(int a[], int first, int last) {
	/*int pivot = first;
	
	while (first < last) {
		if (a[first] <= a[last]) {
			a[pivot]^=a[first]^=a[pivot]^=a[first];
			++pivot;
		}
		++first;
	}
	a[pivot]^=a[last]^=a[pivot]^=a[last];
	return pivot;*/

	int x = a[first];
	int i = first, j = last;
	
	while (i < j) {
		while (a[i] < x) ++i;
		while (a[j] > x) --j;
		
		if (i < j) {
			a[i]^=a[j]^=a[i]^=a[j];
		}
	}
	return i;
}

void QuickSort(int a[], int first, int last) {
	if (first < last) {
		int pivot = Partition(a, first, last);
		QuickSort(a, first, pivot - 1);
		QuickSort(a, pivot + 1, last);
	}
}

void ShellSort(int a[], int n) {
	int i, h = 1;
	
	while (h <= n / 9) {
		h = 3 * h + 1;
	}
	
	while (h > 0) {
		for (i = h; i < n; i++) {
			int j, save = a[i];
			
			for (j = i; j >= h && a[j - h] > save; j -= h) {
				a[j] = a[j - h];
			}
			a[j] = save;
		}
		h /= 3;
	}
}

#endif // __SORTING_H__
