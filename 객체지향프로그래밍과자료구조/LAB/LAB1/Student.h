/** LAB 1 C++ Program
*
* - Struct of Student, Sorting and Searching Array of Students
* - Programmed by Chang-Hyeop LEE
* - Last update: 2020-09-01
*/
#include <iostream>
#include <iomanip> // �̰� ���� �˾Ƽ� �ּ�
#include <fstream>
using namespace std;

typedef struct s_Student //�л����� ������ ǥ���ϱ� ���� ����ü
{
	int st_id;
	char name[16];
	char dept[16];
	int grade;
	double gpa;
} Student;

void initStudents(Student students[], int st_ids[], int num_students); //�л��� ����ü �ʱⰪ �����ϴ� �Լ�
void fprintStudent(ostream& fout, Student* pSt); //�־��� �л� ����ü�� ���� ����ϴ� �Լ�
void fprintStudents(ostream& fout, Student* students, int num_students); //�л����� �迭�� ����ϴ� �Լ�
void fprintStudentIDs(ostream& fout, Student* student, int num_students); //�л����� �й��� ����ϴ� �Լ�
void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last); // �л����� �й��� �迭�� ù �κа� �� �κи��� ����ϴ� �Լ�
void fprintStudentGPA_ID(ostream& fout, Student* student, int num_students); // �л����� ������ �й��� ����ϴ� �Լ�
void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last); // �л����� ����, �й��� ù �κа� �� �κи� ����ϴ� �Լ�
void sortStudentsByID(Student students[], int num_students); //�л��� �й����� �������� ��������
void sortStudentsByGPA_ID(Student students[], int num_students); //�л��� GPA���� �������� ��������
Student* searchStudentByID(Student students[], int num_students, int st_ID); // �й� �������� ���� Ž�� ����ϴ� �Լ�
