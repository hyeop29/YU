/*
Project : 분기한정법으로 외판원문제를 해결해라
Author: Chang‐Hyeop LEE
task duration: May. 31, 2022 ~ June. 4, 2022
*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#include<queue> // 우선 순위 큐를 쓰기 위한 라이브러리
#define oo INT_MAX
using namespace std;

struct node {
	int level;
	int bound;
	int count;
	int path[6] = { 0, };

	// bound 값이 가장 작은 우선 순위 큐로 만들기 위해 설정
	bool operator<(const node n) const {
		return this->bound > n.bound;
	}
};

void best_first_branch_and_bound(int n, int W[][5], int path[]); // 분기한정법 TSP 함수
bool costains(node v, int i); // node v.path에 i가 있는지 없는지 확인하는 함수
int length(node k, int W[][5], int n); // 현재 node의 path에 들어가있는 거리 구하는 함수
int bound(node k, int W[][5], int n); // 현재 배열에 출발지만 들어가 있는 경우

void main()
{
	int W[5][5] =
	{
		{0, 14, 4, 10, 20},
		{14, 0, 7 , 8, 7},
		{4, 5, 0, 7, 16},
		{11, 7, 9, 0, 2},
		{18, 7, 17, 4, 0}
	};
	int path[6] = { 0, }; // 최소 경로를 담을 배열 생성
	best_first_branch_and_bound(5, W, path);
}

void best_first_branch_and_bound(int n, int W[][5], int path[])
{
	bool check;
	priority_queue<node> PQ; // 우선 순위 큐 생성
	node v, u;
	v.level = 0;
	v.count = 0;
	v.path[0] = 0;
	v.count += 1;
	v.bound = bound(v, W, n);
	int minlength = oo;
	PQ.push(v);
	while (!PQ.empty()) {
		v = PQ.top();
		printf("\ntop 정보 \n");
		printf("top의 bound 값 : %d \n", v.bound);
		printf("top의 path \n ");
		for (int i = 0; i < v.count; i++) {
			printf(" %d ", v.path[i]);
		}
		printf("\n");
		PQ.pop();
		if (v.bound < minlength) {
			u.level = v.level + 1;
			for (int i = 1; i < n; i++) {
				if (costains(v, i))  // 한번 넣은 node 넣을 필요 x
				{ 
					continue; 
				} 
				else if(!costains(v,i)) {
					for (int b = 0; b < n + 1; b++) { // u.path = v.path
						u.path[b] = v.path[b];
					}
					u.count = v.count;
					printf("path 에 들어가는 값 : %d \n", i);
					u.path[u.count] = i;
					u.count += 1;
				}
				if (u.level == n - 2) // 남은 node와 출발지 node 자동으로 넣어주면 된다  
				{
					for (int j = 0; j < n; j++) {
						if (!costains(u, j)) // 남은 node 찾고 넣어준다.
						{
							u.path[u.count] = j;
							u.count += 1;
						}
					}
					u.path[u.count] = 0; // 마지막으로 출발지 node 넣어준다.
					u.count += 1;
					printf("value : %d \n", length(u, W, n));
					if (length(u, W, n) < minlength) {
						minlength = length(u, W, n);
						for (int b = 0; b < n + 1; b++) {
							path[b] = u.path[b];
						}
					}
				}
				else {
					u.bound = bound(u, W, n);
					printf("큐에 들어가는 node 정보\n");
					printf("큐에 들어가는 node의 bound : %d \n", u.bound);
					printf("큐에 들어가는 node의 path \n");
					for (int i = 0; i < u.count; i++) {
						printf(" %d ", u.path[i]);
					}
					printf("\n");
					if (u.bound < minlength) // node가 유망한지 점검
					{
						PQ.push(u);
						printf("해당 node는 큐에 들어갔습니다. \n");
					}
					else {
						printf("해당 node는 유망하지 않으므로 큐에 들어가지 않았습니다. \n");
					}
				}
			}
		}
	}
	/* 최단 거리 출력 및 최소 경로 출력 */
	printf("\n\n 최단거리 : %d 이고, 최소 경로는 ", minlength);
	for (int i = 0; i < n; i++) {
		printf(" %d -> ", path[i]);
	}
	printf(" %d 입니다. ", path[n]);
}

bool costains(node v, int i) { // node v.path에 i가 있는지 없는지 확인하는 함수
	int check = 0;
	for (int k = 0; k < v.count; k++) {
		if (v.path[k] == i) {
			check = 1;
		}
	}
	if (check == 1) {
		return true;
	}
	else {
		return false;
	}
}
int length(node k, int W[][5], int n) { // 현재 node의 path에 들어가있는 거리 구하는 함수
	int result = 0;
	for (int i = 0; i < k.count - 1; i++) {
		result = result + W[k.path[i]][k.path[i + 1]];
	}
	return result;
}
int bound(node k, int W[][5], int n) {
	int result = 0;
	int min = oo;

	if (k.count == 1) { // 현재 배열에 출발지만 들어가 있는 경우
		for (int j = 0; j < n; j++) {
			for (int z = 0; z < n; z++) {
				if (W[j][z] == 0) { continue; } // 행에서 최소값 구할 때 0 일때는 제외한다.
				else if (min > W[j][z]) {
					min = W[j][z];
				}
			}
			result += min;
			min = oo;
		}
		return result;
	}
	else {
		int** W1 = (int**)calloc(n, sizeof(int*));
		for (int i = 0; i < n; i++)
		{
			W1[i] = (int*)calloc(n, sizeof(int));
		}
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {
				W1[i][k] = W[i][k];
			}
		}
		result = length(k, W, n);
		/* path 안에 들어가 있는 원소의 수가 n이라고 하면 n-1개 까지의 길이는 length 함수에서 구했기 때문에 bound 함수에서 또
	    더해 줄 필요가 없으므로 0 값으로 만들어준다.*/
		for (int i = 0; i < k.count - 1; i++) {
			for (int q = 0; q < n; q++) {
				W1[k.path[i]][q] = 0;
			}
		}
		/* 이미 왔던 경로는 다시 갈 수 없기에 0 값으로 만들어 준다. */
		for (int a = 0; a < n; a++) {
			for (int x = 1; x < k.count; x++) {
				W1[a][k.path[x]] = 0;
			}
		}
		for (int j = 0; j < n; j++) {
			for (int z = 0; z < n; z++) {
				if (W1[j][z] == 0) { continue; } // 행에서 최소값 구할 때 0 일때는 제외한다.
				else if (j == k.path[k.count - 1]) {
					if (z == 0) { continue; } // 바로 출발지로 가는 경우는 없다.
					else {
						if (min > W1[j][z]) {
							min = W1[j][z];
						}
					}
				}
				else if (min > W1[j][z]) {
					min = W1[j][z];
				}
			}
			if (min == oo) { min = 0; }
			result += min;
			min = oo;
		}
		return result;
	}
}