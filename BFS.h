
#ifndef __BFS_H__
#define __BFS_H__

#include <memory>

void BF() {
	for (i = 0; i < N; i++) {
		G[i] = (int *) malloc((Deg[i] + 1)*sizeof(int));
		G[i][Deg[i]] = -1;
		Deg[i] = 0;
	}
	int Q[N], ql, qr, *p;
	char U[N];
	memset(U, 0, sizeof(U));
	U[Q[ql = qr = 0] = n] = 1;

	for (; ql <= qr; ql++)
		for (p = G[Q[ql]]; *p != -1; p++)
			if (!U[*p]) U[Q[++qr] = *p] = 1;
}

#endif // __BFS_H__
