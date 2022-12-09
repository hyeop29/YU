/** LAB 1 C++ Program
*
* - Struct of Student, Sorting and Searching Array of Students
* - Programmed by Chang-Hyeop LEE
* - Last update: 2020-09-01
*/
#include <iostream>
#include <iomanip> // 이거 뭔지 알아서 주석
#include <fstream>
using namespace std;

typedef struct s_Student //학생들의 정보를 표현하기 위한 구조체
{
	int st_id;
	char name[16];
	char dept[16];
	int grade;
	double gpa;
} Student;

void initStudents(Student students[], int st_ids[], int num_students); //학생들 구조체 초기값 설정하는 함수
void fprintStudent(ostream& fout, Student* pSt); //주어진 학생 구조체의 내용 출력하는 함수
void fprintStudents(ostream& fout, Student* students, int num_students); //학생들의 배열을 출력하는 함수
void fprintStudentIDs(ostream& fout, Student* student, int num_students); //학생들의 학번만 출력하는 함수
void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last); // 학생들의 학번만 배열의 첫 부분과 끝 부분만을 출력하는 함수
void fprintStudentGPA_ID(ostream& fout, Student* student, int num_students); // 학생들의 성적과 학번만 출력하는 함수
void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last); // 학생들의 성적, 학번을 첫 부분과 끝 부분만 출력하는 함수
void sortStudentsByID(Student students[], int num_students); //학생들 학번으로 오름차순 선택정렬
void sortStudentsByGPA_ID(Student students[], int num_students); //학생들 GPA으로 내림차순 선택정렬
Student* searchStudentByID(Student students[], int num_students, int st_ID); // 학번 기준으로 이진 탐색 기능하는 함수
