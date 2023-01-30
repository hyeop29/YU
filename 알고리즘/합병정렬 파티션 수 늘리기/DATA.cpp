#include"DATA.h"

/* Data �迭�� 0���� 1�� �����ϴ� ������ ä��� �Լ� */
void Fill(int Array[]) {
	for (int i = 0; i < SIZE; i++) {
		Array[i] = i;
	}
}

/*Data �迭 �� ���� ���� �Լ� */
void Scramble(int Array[]) {
	int temp;
	int random_num;

	printf("Scramble �Լ� ����\n");

	for (int i = 0; i < SIZE; i++) {
		random_num = rand() % SIZE;  // 0 ~ SIZE-1�� �� �� �������� ���� 
		//printf("%d ", random_num);
		/* Swaping */
		temp = Array[i];
		Array[i] = Array[random_num];
		Array[random_num] = temp;
	}
}

/* �迭�� ���� 0���� 1�� �����ϴ� ������ ���ĵǾ����� �˻��ϱ� ���� �Լ� */
void Validate(int Array[], int val) {
	int check;
	int indent = 0; // �鿩���⸦ ���� ���� ����

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