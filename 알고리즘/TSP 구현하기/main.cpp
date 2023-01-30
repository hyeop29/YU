/*
Project :
TSP 문제를 교재에서 제시된 동적계획법 알고리즘으로 구현하고 다음 지도에 대해 해를 구하도록 한다. 
해를 구하면 일주 경로를 출력하고 총 경로의 길이를 출력하도록 한다.
출발지를 대구로 한 경우 최단 일주 경로를 찾으시오.
출발지를 서울로 한 경우 최단 일주 경로를 찾으시오.

Author: Chang‐Hyeop LEE
task duration: April. 29, 2022 ~ April. 30, 2022
*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define oo 10000  //INT_MAX
#define N  12
void travel(int n, int W[][12], int P[][2048], const char* vertex[12]);
bool check(int a, int b);

void main() {
	//const char* vertex[12] = { "대구", "부산", "울산" ,"울진", "대전", "광주", "청주", "동해", "천안", "인천", "서울", "강릉" };
	const char* vertex[12] = { "서울", "부산", "울산" ,"울진", "대전", "광주", "청주", "동해", "천안", "인천", "대구", "강릉" };
	int path[12];
	/* 출발지 대구 W[12][12] */
	/*int W[12][12] = 
	{ 
		{0, 1, 2, oo, 6, oo, 6, oo, oo, oo, oo, oo},
		{oo, 0, 3, oo, oo, 4, oo, oo, oo, oo, oo, oo},
		{oo, 2, 0, 1, oo, oo, oo, oo, oo, oo, oo, oo},
		{3, oo, 3, 0, 5, oo, 2, 3, oo, oo, oo, oo},
		{3, oo, oo, 5, 0, 3, oo, oo, 5, oo, oo, oo},
		{6, 5, oo, oo, 3, 0, oo, oo, oo, oo, oo, oo},
		{oo, oo, oo, 2, oo, oo, 0, 1, 3, oo, 13, oo},
		{oo, oo, oo, 5, oo, oo, 2, 0, oo, oo, oo, 5},
		{oo, oo, oo, oo, 4, oo, 4, oo, 0, 3, oo, oo},
		{oo, oo, oo, oo, oo, oo, oo, oo, 1, 0, 7, oo},
		{oo, oo, oo, oo, oo, oo, 8, oo, oo, 3, 0, 5},
		{oo, oo, oo, oo, oo, oo, oo, 3, oo, oo, 3, 0}
	};*/
	/* 출발지 서울 W[12][12]*/
	int W[12][12] =
	{
		{0, oo, oo, oo, oo, oo, 8, oo, oo, 3, oo, 5},
		{oo, 0, 3, oo, oo, 4, oo, oo, oo, oo, oo, oo},
		{oo, 2, 0, 1, oo, oo, oo, oo, oo, oo, oo, oo},
		{oo, oo, 3, 0, 5, oo, 2, 3, oo, oo, 3, oo},
		{oo, oo, oo, 5, 0, 3, oo, oo, 5, oo, 3, oo},
		{oo, 5, oo, oo, 3, 0, oo, oo, oo, oo, 6, oo},
		{13, oo, oo, 2, oo, oo, 0, 1, 3, oo, oo, oo},
		{oo, oo, oo, 5, oo, oo, 2, 0, oo, oo, oo, 5},
		{oo, oo, oo, oo, 4, oo, 4, oo, 0, 3, oo, oo},
		{7, oo, oo, oo, oo, oo, oo, oo, 1, 0, oo, oo},
		{oo, 1, 2, oo, 6, oo, 6, oo, oo, oo, 0, oo},
		{3, oo, oo, oo, oo, oo, oo, 3, oo, oo, oo, 0}
	};
	int P[12][2048] = { 0, };
	int result = 0;
	travel(N, W, P, vertex);
}

void travel(int n, int W[][12], int P[][2048], const char* vertex[12]) {
	int i, j, k, A;
	int index = 0;
	int min;
	int D[12][2048] = { 0, };
	
	for (i = 1; i < n; i++) {
		D[i][0] = W[i][0];
	}
	for (k = 1; k < n - 1; k++) {
		//printf("k값은 %d\n", k);
		for (A = 1; A < 2048; A++) {
			//printf("A는 %d\n", A);
			int count = 0;
			int temp;
			/* V - {v1}의 부분집합 중에서 k개의 정점을 가진 모든 부분집합 A 구별 */
			for (i = 0; i < n; i++) {
				temp = A & (1 << i);
				//printf("temp 값은 %d\n", temp);
				if (temp > 0) {
					count = count + 1;
				}
				//printf("count 값은 %d\n", count);
			}
			if (k != count)
				continue;
			else if(k == count){
				for (i = 1; i < n; i++) {
					/* i : 0 이 아니고 vi가 A에 속하지 않는 모든 i 구별 */
					if (check(A, i) == TRUE) // A에 i가 속한다면 다시 반복문으로 돌아간다.
					{
						continue;
					}
					else // A에 i가 속하지 않는다면
					{
						min = oo;
						/* 가장 최적의 j를 선택하고 최단 거리 값 설정 */
						for (j = 1; j < n; j++) {
							if ((W[i][j] == oo) || (D[j][A & ~(1 << (j - 1))] == oo)) // 둘 중 하나의 값이 oo이면 최솟값이 되지 못하므로 continue
							{
								continue;
							}
							else if (check(A, j) == TRUE) // j를 선택할 때 A에서 속한 상태에서 j를 선택할 수 있으므로 확인한다.
							{
								if (min > W[i][j] + D[j][A & ~(1 << (j - 1))]) {
									min = W[i][j] + D[j][A & ~(1 << (j - 1))];
									index = j;
									//printf("W[%d][%d] : %d\n", i, j, W[i][j]);
									//printf("D[%d][%d] : %d\n", j, A & ~(1 << (j - 1)), D[j][A & ~(1 << (j - 1))]);
									//printf("j는 %d min은 %d\n", j, min);
								}
							}
							else {
								continue;
							}
						}
						D[i][A] = min;   // 최솟값을 D 행렬에 넣어준다.
						P[i][A] = index; // 기억해둔 j값을 P 행렬에 넣어준다.
					}
				}
			}
		}
	}
	A = 2047;
	min = oo;
	for (j = 1; j < n; j++) {
		if ((W[0][j] == oo) || (D[0][A & ~(1 << (j - 1))] == oo)) {
			continue;
		}
		else if (check(A, j) == TRUE) {
			if (min > W[0][j] + D[j][A & (~(1 << (j - 1)))]) {
				min = W[0][j] + D[j][A & (~(1 << (j - 1)))];
				index = j;
				//printf("W[%d][%d] : %d\n", 0, j, W[0][j]);
				//printf("D[%d][%d] : %d\n", j, A & ~(1 << (j - 1)), D[j][A & ~(1 << (j - 1))]);
				//printf("j는 %d min은 %d\n", j, min);
			}
		}
		else {
			continue;
		}
	}
	D[0][A] = min;
	P[0][A] = index;
	int x = 0;
	int path = 0;
	int q = A;
	printf("최단 경로: %s ", vertex[0]);
	for (x; x < 12; x++) {
		q = q & ~(1 << (path - 1));
		path = P[path][q];
		printf("%s ", vertex[path]);
	}
	printf("\n최단 거리는 %d 입니다.", min);
}
bool check(int a, int b) {
	int temp = 1 << (b - 1);
	if ((a & temp) > 0) {
		return TRUE;
	}
	else
		return FALSE;
}