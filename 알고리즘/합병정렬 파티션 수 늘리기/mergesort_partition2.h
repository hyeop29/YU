#ifndef MERGESORT_PARTITION2
#include "DATA.h"

void merge(int low, int mid, int high, int S[], int U[]) {
	int i, j, k;
	i = low;
	j = mid + 1;
	k = low;
	/* 2���� ��Ƽ�ǿ����� �񱳴���� ���� ���� �� */
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
	/* 1���� ��Ƽ�Ǹ� ������ ��� */
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
	/* ������ �Ϸ�� U�迭�� S�迭�� �Ѱ��ش� */
	for (low; low <= high; low++) {
		S[low] = U[low];
	}
}

/* ��Ƽ�� 2�� */
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