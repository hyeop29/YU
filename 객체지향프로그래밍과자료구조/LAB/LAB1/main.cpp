/** LAB 1 C++ Program
*
* - Struct of Student, Sorting and Searching Array of Students
* - Programmed by Chang-Hyeop LEE
* - Last update: 2020-09-01
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
using namespace std;
#define NUM_STUDENTS 5000
#define NUM_SEARCH 5
#define NUM_FIRST_LAST_BLOCK 100

void genBigRandArray(int randArray[], int num_rands) //ū ���� �迭 ���� �Լ�
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand;
	flag = (char*)calloc(sizeof(char), num_rands); //calloc�� ���ؼ� nuum_rands ��ŭ ���� �Ҵ�
	while (count < num_rands)
	{
		u_int32 = ((long)rand() << 15) | rand(); //rand�� �ѹ� �����ؼ��� ū ������ ���� �� ���
												 //rand�� �ι� ����ϴµ� ù ��° rand �� ���� �������� 15ĭ �ű�� �� ��ġ�� rand�� �����ؼ�
												 //�� 30��Ʈ�� �ǵ��� �Ѵ�
		bigRand = u_int32 % num_rands;           //num_rands ������ŭ ��������� ���������� ���
		if (flag[bigRand] == 1) {                //���� ���� �ߺ��� ������� �ʱ� ���� ����
			continue;
		}
		flag[bigRand] = 1;
		randArray[count++] = bigRand;
		
	}
}

void main()
{
	ofstream fout;
	int* student_ids;
	Student* students, * pSt;
	int studentID_search[NUM_SEARCH] = { 1, 123, 999, 2500, 4999 };
	fout.open("output.txt");
	if (fout.fail()) //���Ͼ��⿡ �����ϸ�
	{
		cout << "Error in opening output.txt" << endl;
		exit; //����
	}
	student_ids = (int*)malloc(sizeof(int) * NUM_STUDENTS);
	students = (Student*)malloc(sizeof(Student) * NUM_STUDENTS);  
	genBigRandArray(student_ids, NUM_STUDENTS);
	initStudents(students, student_ids, NUM_STUDENTS);
	fout << endl << endl;
	fout << "Initialized array of students : " << endl;
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	//fout << endl;
	//fprintStudents(fout, students, NUM_STUDENTS);
	fout << endl << endl;
	fout << "Sorting array of students by (decreasing order of GPA, increasing order of ID) : " << endl;
	sortStudentsByGPA_ID(students, NUM_STUDENTS); // non-increasing order
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Searching student with student_ID : " << endl;
	for (int i = 0; i < NUM_SEARCH; i++)
	{
		pSt = searchStudentByID(students, NUM_STUDENTS, studentID_search[i]);
		fout << "Student search by ID (" << setw(4) << studentID_search[i] << ") : ";
		if (pSt != NULL)
			fprintStudent(fout, pSt);
		else
			fout << "NULL - student was not found !!";
		fout << endl;
	}
	fout.close();
}
