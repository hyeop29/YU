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

void genBigRandArray(int randArray[], int num_rands) //큰 난수 배열 생성 함수
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand;
	flag = (char*)calloc(sizeof(char), num_rands); //calloc을 통해서 nuum_rands 만큼 동적 할당
	while (count < num_rands)
	{
		u_int32 = ((long)rand() << 15) | rand(); //rand를 한번 실행해서는 큰 난수를 만들 수 없어서
												 //rand를 두번 사용하는데 첫 번째 rand 한 것을 왼쪽으로 15칸 옮기고 그 위치에 rand를 실행해서
												 //총 30비트가 되도록 한다
		bigRand = u_int32 % num_rands;           //num_rands 범위만큼 만들기위해 나머지값을 사용
		if (flag[bigRand] == 1) {                //같은 수의 중복을 허용하지 않기 위한 구문
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
	if (fout.fail()) //파일쓰기에 실패하면
	{
		cout << "Error in opening output.txt" << endl;
		exit; //종료
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
