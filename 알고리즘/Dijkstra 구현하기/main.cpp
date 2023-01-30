/*
Project :
Dijkstra 구현하기
다음 지도에 대해 해를 구하도록 한다.
출발지를 경산으로 한 경우 서울까지 최단 경로를 찾으시오.
출발지를 서울로 한 경우 경산까지 최단 경로를 찾으시오.

Author: Chang‐Hyeop LEE
task duration: May. 5, 2022 ~ May. 5, 2022
*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define oo INT_MAX
void dijkstra(int n, int W[][12], int G, const char* vertex[]);
void path(int touch[], int W[][12], int dest, const char* vertex[]);

void main() {
	const char* vertex1[12] = { "서울", "부산", "경산" ,"울진", "대전", "광주", "청주", "동해", "천안", "인천", "대구", "강릉" };
	int W1[12][12] =
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
	const char* vertex2[12] = { "경산", "부산", "서울" ,"울진", "대전", "광주", "청주", "동해", "천안", "인천", "대구", "강릉" };
	int W2[12][12] =
	{
		{0, 2, oo, 1, oo, oo, oo, oo, oo, oo, oo, oo},
		{3, 0, oo, oo, oo, 4, oo, oo, oo, oo, oo, oo},
		{oo, oo, 0, oo, oo, oo, 8, oo, oo, 3, oo, 5},
		{3, oo, oo, 0, 5, oo, 2, 3, oo, oo, 3, oo},
		{oo, oo, oo, 5, 0, 3, oo, oo, 5, oo, 3, oo},
		{oo, 5, oo, oo, 3, 0, oo, oo, oo, oo, 6, oo},
		{oo, oo, 13, 2, oo, oo, 0, 1, 3, oo, oo, oo},
		{oo, oo, oo, 5, oo, oo, 2, 0, oo, oo, oo, 5},
		{oo, oo, oo, oo, 4, oo, 4, oo, 0, 3, oo, oo},
		{oo, oo, 7, oo, oo, oo, oo, oo, 1, 0, oo, oo},
		{2, 1, oo, oo, 6, oo, 6, oo, oo, oo, 0, oo},
		{oo, oo, 3, oo, oo, oo, oo, 3, oo, oo, oo, 0}
	};
	printf("출발지를 서울로 한 경우 경산까지 최단 경로를 찾으시오.\n");
	dijkstra(12, W1, 2, vertex1);
	printf("출발지를 경산으로 한 경우 서울까지 최단 경로를 찾으시오.\n");
	dijkstra(12, W2, 2, vertex2);
}
void dijkstra(int n, int W[][12], int G, const char* vertex[]) {
	int i, j, k, q, min;
	int vnear = 0;
	int* touch = (int*)calloc(n, sizeof(int));
	int* length = (int*)calloc(n, sizeof(int));
	/* 초기화 과정 */
	for (q = 1; q < n; q++) {
		touch[q] = 0;
		length[q] = W[0][q];
	}
	for (k = 0; k < n - 1; k++) {
		min = oo;
		/* 집합 Y에 넣을 새로운 정점을 찾는다 */
		for (i = 1; i < n; i++) {
			if ((0 <= length[i]) && (length[i] < min)) {
				min = length[i];
				vnear = i;
			}
		}

		for (j = 1; j < n; j++) {
			if (W[vnear][j] == oo)
				continue;
			/* length 배열 재설정 (집합 Y에 vnear 정점이 들어가기 때문에 최신화 작업)*/
			if (length[vnear] + W[vnear][j] < length[j]) {
				length[j] = length[vnear] + W[vnear][j];
				touch[j] = vnear;
			}
		}
		length[vnear] = -1; // 선택된 정점(Y의 집합으로 들어간 정점)의 length는 -1로 해준다
	}
	path(touch, W, G, vertex);
}
/* 경로 및 최단 거리 출력 함수 */
void path(int touch[], int W[][12], int dest, const char* vertex[]) {
	int count, f, num_vertex, dis, z;
	count = -1;
	f = dest;
	while (touch[f] != 0) {
		f = touch[f];
		count++;
	}
	num_vertex = count + 1;
	int* path = (int*)calloc(count, sizeof(int));
	f = dest;
	/* 경로를 역순으로 담아준다. */
	while (touch[f] != 0) {
		path[count] = touch[f];
		f = touch[f];
		count--;
	}
	printf("경유한 도시 : %s -> ", vertex[0]);
	dis = W[0][path[0]];
	for (z = 0; z < num_vertex; z++) {
		printf("%s -> ", vertex[path[z]]);
		if (z != 0) {
			dis = dis + W[path[z - 1]][path[z]];
		}
	}
	printf("%s", vertex[dest]);
	dis = dis + W[path[z - 1]][dest];

	printf("\n총 거리는 %d 입니다. \n", dis);
}