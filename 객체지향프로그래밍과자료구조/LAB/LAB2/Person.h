#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Date.h"
#include <time.h>
using namespace std;

#define MAX_NAME_LEN 15
#define MIN_NAME_LEN 5
class PersonArray;
class Person
{
public:
	Person() : name(string("nobody")), birthDate(Date(1, 1, 1)) { }
	Person(string n, Date bd) : name(n), birthDate(bd) { }
	void setName(string n) { name = n; }
	string getName() { return name; }
	void setBirthDate(Date bd) { birthDate = bd; }
	Date getBirthDate() { return birthDate; }
	void setRandPersonAttributes(); //������ ������� class Person �Ӽ��� �´� ���� ������ ����
	void fprintPerson(ostream& fout); //������ ��°�ü�� class Person�� �Ӽ������� ���
private:
	Date birthDate;
	string name;
};
#endif
