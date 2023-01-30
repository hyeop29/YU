#ifndef MERGESORT_PARTITION2
#include "DATA.h"

void merge(int low, int mid, int high, int S[], int U[]) {
	int i, j, k;
	i = low;
	j = mid + 1;
	k = low;
	/* 2개의 파티션에서만 비교대상이 남아 있을 때 */
	while (i <= mid && j <= high) {
		if (S[i] <= S[j]) {
			U[k] = S[i];
			i++;
		}
		else {
			U[k] = S[j];
			j++;
		}
		k++;
	}
	/* 1개의 파티션만 남겨질 경우 */
	if (i > mid) {
		for (j; j <= high; j++) {
			U[k] = S[j];
			k++;
		}
	}
	else {
		for (i; i <= mid; i++) {
			U[k] = S[i];
			k++;
		}
	}
	/* 정렬이 완료된 U배열을 S배열로 넘겨준다 */
	for (low; low <= high; low++) {
		S[low] = U[low];
	}
}

/* 파티션 2개 */
void mergesort(int low, int high, int S[], int U[]) {
	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		mergesort(low, mid, S, U);
		mergesort(mid + 1, high, S, U);
		merge(low, mid, high, S, U);
	}
}
#endif