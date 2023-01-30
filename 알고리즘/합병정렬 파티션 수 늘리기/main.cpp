/*
Project : 
합병정렬 pseudo code를 기반으로 파티션 수를 기존 2개에서 3, 4개로 수정한 합병정렬을 구현한 후 성능을 측정한다.
테스트 환경에서 정의 가능한 가장 큰 32bit integer 타입의 배열을 만든다. 이때 가용 메모리 양을 고려하도록 한다.
예를 들어 현재 1GB 메모리 여유가 있는 경우, 1GB/4B = 256M이므로 시스템이 허락하는 한도안에서 256M 개 이하로 배열을 할당한다. 
#define SIZE 256000000
Int data[SIZE];
Data 배열을 0부터 1씩 증가하는 값으로 채운다.  Fill( data );
Data 배열 내 값을 섞는다. I 는 0.. SIZE-1의 값으로 모든 i에 대해서 i번째 값을 무작위로 선택된 인덱스의 값과 서로 바꾼다. 
Scramble( data );
이제 구현한 합병정렬 알고리즘을 사용하여 오름차순으로 정렬을 한다. 이때 정렬하는데 걸린 시간(tic 수)을 측정한다.
startTime = getTime();
mergesort( data );
elapsedTime = getTime() – startTime;
정렬 후 배열내 값이 0부터 1씩 증가하는 값으로 정렬되었는지 검사한다.
Validate( data );

Author: Chang‐Hyeop LEE
task duration: March. 29, 2022 ~ April. 3, 2022
*/

#include"DATA.h"
#include"mergesort_partition2.h"
#include"mergesort_partition3.h"
#include"mergesort_partition4.h"

void main() {
	int* data = (int*)calloc(SIZE, sizeof(int));   // SIZE 크기의 data 배열 동적 생성
	int val[3];
	double start[3], end[3];
	Fill(data);
	
	Scramble(data);
	int* U = (int*)calloc(SIZE, sizeof(int));
	if (U == NULL) {
		printf("Error");
	}
	start[0] = clock();
	mergesort(0, SIZE - 1, data, U);
	end[0] = clock();
	free(U); //사용한 heap 메모리 반환
	Validate(data, val[0]);
	
	
	Scramble(data);
	int* B = (int*)calloc(SIZE, sizeof(int));
	if (B == NULL) {
		printf("Error");
	}
	start[1] = clock();
	mergesort_3(0, SIZE - 1, data, B);
	end[1] = clock();
	free(B); //사용한 heap 메모리 반환
	Validate(data, val[1]);

	
	Scramble(data);
	int* C = (int*)calloc(SIZE, sizeof(int));
	if (C == NULL) {
		printf("Error");
	}
	start[2] = clock();
	mergesort_4(0, SIZE - 1, data, C);
	end[2] = clock();
	free(C); //사용한 heap 메모리 반환
	Validate(data, val[2]);
	
	free(data); //사용한 heap 메모리 반환
	
	printf("분석 결과\n");
	for (int i = 0; i < 3; i++) {
		if (val[i] > 0) {
			printf(" 파티션 %d개 정렬은 실패 했습니다\n", i+2);
		}
		else {
			printf(" 파티션 %d개 정렬은 성공 했습니다\n", i+2);
		}
		printf("정렬에 소요된 시간은 %lf ms초 입니다.\n", end[i] - start[i]);
	
	}
}
