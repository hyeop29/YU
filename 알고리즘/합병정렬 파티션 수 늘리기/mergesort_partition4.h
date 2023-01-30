#include"DATA.h"

void merge_4(int low, int sec, int third, int fourth, int high, int S[], int U[]) {
	int i, j, k, q, u;
	int min;
	i = low;
	j = sec + 1;
	q = third + 1;
	u = fourth + 1;
	k = low;
	//printf("low : %d, sec : %d, third : %d, high : %d\n", i, sec, third, high);
	/* 4���� ��Ƽ�ǿ��� �� �񱳴���� ���� ���� �� */
	while (i <= sec && j <= third && q <= fourth && u <= high) {
		if (S[i] <= S[j]) {
			if (S[q] <= S[i]) {
				if (S[u] <= S[q]) {
					U[k] = S[u];
					u++;
				}
				else {
					U[k] = S[q];
					q++;
				}
			}
			else {
				if (S[u] <= S[i]) {
					U[k] = S[u];
					u++;
				}
				else {
					U[k] = S[i];
					i++;
				}
			}

		}
		else {
			if (S[q] <= S[j]) {
				if (S[u] <= S[q]) {
					U[k] = S[u];
					u++;
				}
				else {
					U[k] = S[q];
					q++;
				}
			}
			else {
				if (S[u] <= S[j]) {
					U[k] = S[u];
					u++;
				}
				else {
					U[k] = S[j];
					j++;
				}
			}
		}
		k++;
	}
	/* 3���� ��Ƽ�ǿ����� �񱳴���� ���� ���� �� */
	while (i > sec && j <= third && q <= fourth && u <= high) {
		if (S[j] <= S[q]) {
			if (S[u] <= S[j]) {
				U[k] = S[u];
				u++;
			}
			else {
				U[k] = S[j];
				j++;
			}
		}
		else {
			if (S[u] <= S[q]) {
				U[k] = S[u];
				u++;
			}
			else {
				U[k] = S[q];
				q++;
			}
		}
		k++;
	}
	while (i <= sec && j > third && q <= fourth && u <= high) {
		if (S[i] <= S[q]) {
			if (S[u] <= S[i]) {
				U[k] = S[u];
				u++;
			}
			else {
				U[k] = S[i];
				i++;
			}
		}
		else {
			if (S[u] <= S[q]) {
				U[k] = S[u];
				u++;
			}
			else {
				U[k] = S[q];
				q++;
			}
		}
		k++;
	}
	while (i <= sec && j <= third && q > fourth && u <= high) {
		if (S[i] <= S[j]) {
			if (S[u] <= S[i]) {
				U[k] = S[u];
				u++;
			}
			else {
				U[k] = S[i];
				i++;
			}
		}
		else {
			if (S[u] <= S[j]) {
				U[k] = S[u];
				u++;
			}
			else {
				U[k] = S[j];
				j++;
			}
		}
		k++;
	}
	while (i <= sec && j <= third && q <= fourth && u > high) {
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
	/* 2���� ��Ƽ�ǿ����� �񱳴���� ���� ���� �� */
	while (i <= sec && j <= third && q > fourth && u > high) {
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
	while (i <= sec && j > third && q <= fourth && u > high) {
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
	while (i <= sec && j > third && q > fourth && u <= high) {
		if (S[i] <= S[u]) {
			U[k] = S[i];
			i++;
		}
		else {
			U[k] = S[u];
			u++;
		}
		k++;
	}
	while (i > sec && j <= third && q <= fourth && u > high) {
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
	while (i > sec && j <= third && q > fourth && u <= high) {
		if (S[j] <= S[u]) {
			U[k] = S[j];
			j++;
		}
		else {
			U[k] = S[u];
			u++;
		}
		k++;
	}
	while (i > sec && j > third && q <= fourth && u <= high) {
		if (S[q] <= S[u]) {
			U[k] = S[q];
			q++;
		}
		else {
			U[k] = S[u];
			u++;
		}
		k++;
	}
	/* 1���� ��Ƽ�Ǹ� ������ ��� */
	if (i > sec && j > third && q > fourth) {
		for (u; u <= high; u++) {
			U[k] = S[u];
			k++;
		}
	}
	else if (i > sec && j > third && u > high) {
		for (q; q <= fourth; q++) {
			U[k] = S[q];
			k++;
		}
	}
	else if (i > sec && q > fourth && u > high) {
		for (j; j <= third; j++) {
			U[k] = S[j];
			k++;
		}
	}
	else if (j > third && q > fourth && u > high) {
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

/* ��Ƽ�� 4�� */
void mergesort_4(int low, int high, int S[], int U[]) {
	int sec, third, fourth;
	if (low < high) {

		sec = (high - low) / 4 + low;
		third = 2 * ((high - low) / 4) + low;
		fourth = 3 * ((high - low) / 4) + low;
		mergesort_4(low, sec, S, U);
		mergesort_4(sec + 1, third, S, U);
		mergesort_4(third + 1, fourth, S, U);
		mergesort_4(fourth + 1, high, S, U);
		merge_4(low, sec, third, fourth, high, S, U);
	}
}
