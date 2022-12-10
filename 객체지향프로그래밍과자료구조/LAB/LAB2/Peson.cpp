#include "Person.h"
#include <stdlib.h>

void Person::setRandPersonAttributes()
{
	char str[MAX_NAME_LEN + 1];
	int name_len, i = 0;
	birthDate.setRandDateAttributes();
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN; //5~14자리
	str[0] = rand() % 26 + 'A'; //첫글자는 대문자
	for (i = 1; i < name_len; i++)
		str[i] = rand() % 26 + 'a'; //나머지는 소문자
	str[i] = '\0'; //문자열
	name = string(str);
}
void Person::fprintPerson(ostream& fout)
{
	fout << " Person [name: ";
	fout.setf(ios::left); //왼쪽 정렬
	fout << setw(16) << name;
	fout << ", birth date: ";
	fout.unsetf(ios::left); //오른쪽 정렬
	birthDate.fprintDate(fout);
	fout << "]";
}