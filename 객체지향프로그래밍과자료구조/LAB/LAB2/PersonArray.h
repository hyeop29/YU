#ifndef PERSONARRAY_H
#define PERSONARRAY_H

#include <iostream>
#include "Person.h"

using namespace std;

class PersonArray
{
public:
	PersonArray(int size);
	~PersonArray();
	int size() { return person_num; }
	void sort();
	Person& operator[](int index)const;
	//배열 연산자 만들기
private:
	Person* per;
	int person_num;
};
#endif
