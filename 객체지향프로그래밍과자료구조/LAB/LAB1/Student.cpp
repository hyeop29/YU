#include "Student.h"
#include <time.h>

void initStudents(Student students[], int st_ids[], int num_students)
{
	int name_len,dept_len;
	int j, grade;
	double br;
	srand(time(0));
	for (int i = 0; i < num_students; i++)
	{
		students[i].st_id = st_ids[i]; //아이디 배열에서 아이디는 그대로 받아온다
		
		name_len = rand() % 11 + 5;    // 5~15문자라는 조건 만족하기 위해
		students[i].name[0] = rand() % 26 + 'A'; //이름 처음 문자는 반드시 대문자 표시 조건 만족
		for (j = 1; j < name_len; j++)
			students[i].name[j] = rand() % 26 + 'a'; //나머지 이름은 소문자
		students[i].name[j] = NULL;
		
		dept_len = rand() % 3 + 3; //3~5 조건 만족
		for (j = 0; j < dept_len; j++)
			students[i].dept[j] = rand() % 26 + 'A'; //대문자 조건 만족
		students[i].dept[j] = NULL;
		
		students[i].grade = rand() % 8 + 1;
		students[i].gpa = (rand() % 10000) / 100.0; //0.00~99.99 범위
	}
}

void fprintStudent(ostream& fout, Student* pSt)
{
	int count = 0;  //format 설정
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);

	fout << "Student(ID: " << setw(4) << pSt->st_id;
	fout << ", Name: " << setw(16) << pSt->name;
	fout << ", Dept : " << setw(6) << pSt->dept;
	fout << ", Grade : " << pSt->grade;
	fout << ", GPA: " << setw(5) << pSt->gpa;
	fout << endl;
}

void fprintStudents(ostream& fout, Student* students, int num_students)
{
	Student pSt;
	for (int i = 0; i < num_students; i++)
	{
		pSt = students[i];
		fprintStudent(fout, &pSt);
	}
}

void fprintStudentIDs(ostream& fout, Student* student, int num_students)
{
	int count = 0; //format 설정
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);
	fout << "Student(ID: " << setw(4) << student->st_id;
}

void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last)
{
	Student* pSt;
	int count = 0;
	if (num_students <= num_first_last * 2) // 샘플로 출력할 배열이 전체 학생 수보다  클 경우
	{
		for (int i = 0; i < num_students; i++) //전체 출력
		{
			pSt = &students[i];
			fout << setw(6) << pSt->st_id;
			count++;
			if ((count % 10) == 0)
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++) //num_first_last만큼 출력
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;
		count++;
		if ((count % 10) == 0)
			fout << endl;
	}
	fout << " . . . . . " << endl;
	for (int i = num_students - num_first_last; i < num_students; i++) //뒤에서 num_first_last 출력
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;
		count++;
		if ((count % 10) == 0)
			fout << endl;
	}
}

void fprintStudentGPA_ID(ostream& fout, Student* student, int num_students)
{
	fout.setf(ios::fixed); //고정 소수점 표시 
	fout.setf(ios::showpoint); //소수점 표시
	fout.precision(2); //소수점 2자리까지 표시 설정

	fout << "(" << setw(5) << student->gpa << "," << setw(6) << student->st_id << ") ";
}

void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last)
{
	Student* pSt;
	int count = 0;

	if (num_students <= num_first_last * 2) // 샘플로 출력할 배열이 전체 학생 수보다  클 경우
	{
		for (int i = 0; i < num_students; i++) //전체 경우 출력
		{
			pSt = &students[i];
			fout << "(" << setw(5) << pSt->gpa << "," << setw(6) << pSt->st_id << ") ";
			count++;
			if ((count % 10) == 0)
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++) //num_first_last만큼 출력
	{
		pSt = &students[i];
		fout << "(" << setw(5) << pSt->gpa << "," << setw(6) << pSt->st_id << ") ";
		count++;
		if ((count % 10) == 0)
			fout << endl;
	}
	fout << " . . . . . " << endl;
	for (int i = num_students - num_first_last; i < num_students; i++) //뒤에서 num_first_last 출력
	{
		pSt = &students[i];
		fout << "(" << setw(5) << pSt->gpa << "," << setw(6) << pSt->st_id << ") ";
		count++;
		if ((count % 10) == 0)
			fout << endl;
	}
}

void sortStudentsByID(Student students[], int num_students)
{
	int i, j, mx;
	char minName[16] = { 0 };
	Student tmp;
	int min_st, min_ID;
	for (i = 0; i < num_students - 1; i++)
	{
		min_st = i;
		min_ID = students[min_st].st_id;
		for (j = i + 1; j < num_students; j++)
		{
			if (students[j].st_id < min_ID) //더 작은 아이디 발견하면
			{
				min_st = j;                 //min_st값은 j값
				min_ID = students[j].st_id; //min_ID 값도 j번째 학생 구조체의 id 값
			}
		}
		if (min_st != i)
		{
			tmp = students[i];
			students[i] = students[min_st];
			students[min_st] = tmp; //스와핑 하는 과정
		}
	}
}

void sortStudentsByGPA_ID(Student students[], int num_students)
{
	int i, j, mx;
	char minName[16] = { 0 };
	Student tmp;
	int min_st, max_GPA;
	for (i = 0; i < num_students - 1; i++)
	{
		min_st = i;
		max_GPA = students[min_st].gpa;
		for (j = i + 1; j < num_students; j++)
		{
			if (students[j].gpa > max_GPA) //더 큰 gpa 발견하면
			{
				min_st = j;                //min_st값은 j값
				max_GPA = students[j].gpa; //max_GPA 값도 j번째 학생 구조체의 gpa 값
			}
			else if (students[j].gpa == max_GPA) //만약 GPA가 같으면
			{
				if (students[j].st_id < students[i].st_id)  //id가 더 빠른사람(작은 사람) 먼저
				{
					min_st = j;
					max_GPA = students[j].gpa;
				}
			}
		}
		if (min_st != i)
		{
			tmp = students[i];
			students[i] = students[min_st];
			students[min_st] = tmp; //스와핑하는 과정
		}
	}
}

Student* searchStudentByID(Student students[], int num_students, int st_ID)
{
	int low, high, mid;
	low = 0;
	high = num_students - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (st_ID == students[mid].st_id)
			return &students[mid];
		else if (st_ID < students[mid].st_id)
			high = mid - 1;
		else
			low = mid + 1;
	}
}