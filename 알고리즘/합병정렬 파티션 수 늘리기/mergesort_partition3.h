#include"DATA.h"

void merge_3(int low, int sec, int third, int high, int S[], int U[]) {
	int i, j, k, q;
	i = low;
	j = sec + 1;
	q = third + 1;
	k = low;
	//printf("low : %d, sec : %d, third : %d, high : %d\n", i, sec, third, high);
	/* 3���� ��Ƽ�ǿ��� �� �񱳴���� ���� ���� �� */
	while (i <= sec && j <= third && q <= high) {
		if (S[i] <= S[j]) {
			if (S[q] <= S[i]) {
				U[k] = S[q];
				q++;
			}
			else {
				U[k] = S[i];
				i++;
			}

		}
		else {
			if (S[q] <= S[j]) {
				U[k] = S[q];
				q++;
			}
			else {
				U[k] = S[j];
				j++;
			}
		}
		k++;
	}
	while (i > sec && j <= third && q <= high) {
		if (S[j] <= S[q]) {
			U[k] = S[j];
			j++;
		}
		else {
			U[k] = S[q];
			q++;
		}
		k++;
	}
	/* 2���� ��Ƽ�ǿ����� �񱳴���� ���� ���� �� */
	while (i <= sec && j > third && q <= high) {
		if (S[i] <= S[q]) {
			U[k] = S[i];
			i++;
		}
		else {
			U[k] = S[q];
			q++;
		}
		k++;
	}
	while (i <= sec && j <= third && q > high) {
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
	if (i > sec && j > third) {
		for (q; q <= high; q++) {
			U[k] = S[q];
			k++;
		}
	}
	else if (i > sec && q > high) {
		for (j; j <= third; j++) {
			U[k] = S[j];
			k++;
		}
	}
	else if (j > third && q > high) {
		for (i; i <= sec; i++) {
			U[k] = S[i];
			k++;
		}
	}
	/* ������ �Ϸ�� U�迭�� S�迭�� �Ѱ��ش� */
	for (low; low <= high; low++) {
		S[low] = U[low];
	}
}

/* ��Ƽ�� 3�� */
void mergesort_3(int low, int high, int S[], int U[]) {
	int sec, third;
	if (low < high) {
		
		sec = (high - low) / 3 + low;
		third =  2*( (high - low) / 3 ) + low;
		mergesort_3(low, sec, S, U);
		mergesort_3(sec + 1, third, S, U);
		mergesort_3(third + 1, high, S, U);
		merge_3(low, sec, third, high, S, U);
	}
}
