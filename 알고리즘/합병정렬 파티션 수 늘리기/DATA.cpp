#include"DATA.h"

/* Data 배열을 0부터 1씩 증가하는 값으로 채우는 함수 */
void Fill(int Array[]) {
	for (int i = 0; i < SIZE; i++) {
		Array[i] = i;
	}
}

/*Data 배열 내 값을 섞는 함수 */
void Scramble(int Array[]) {
	int temp;
	int random_num;

	printf("Scramble 함수 실행\n");

	for (int i = 0; i < SIZE; i++) {
		random_num = rand() % SIZE;  // 0 ~ SIZE-1의 값 중 무작위로 추출 
		//printf("%d ", random_num);
		/* Swaping */
		temp = Array[i];
		Array[i] = Array[random_num];
		Array[random_num] = temp;
	}
}

/* 배열내 값이 0부터 1씩 증가하는 값으로 정렬되었는지 검사하기 위한 함수 */
void Validate(int Array[], int val) {
	int check;
	int indent = 0; // 들여쓰기를 위한 변수 선언

	for (int i = 0; i < SIZE; i++) {
		
		//check = Array[i];
		
		if (Array[i] != i) {
			val++;
		}
		
		//if (indent == 10) {
		//	printf("\n");
		//	indent = 0;
		//}

		//printf("%d ", check);
		//indent++;
	}
	//printf("\n\n");
}