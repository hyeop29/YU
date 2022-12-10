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
	void setRandPersonAttributes(); //데이터 멤버들을 class Person 속성에 맞는 임의 값으로 설정
	void fprintPerson(ostream& fout); //지정된 출력객체로 class Person의 속성값들을 출력
private:
	Date birthDate;
	string name;
};
#endif
