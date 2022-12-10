/** LAB 2
*
* - LAB 2
* - Programmed by Chang-Hyeop LEE
* - Last update: 2021-09-08
*/
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "Date.h"
#include "Person.h"
#include "PersonArray.h"
using namespace std;
#define NUM_PERSON 10

void selectionSortbrithDate(Person person[]); // 생일에 따라 선택 정렬
void selectionName(Person person[]); // 이름에 따라 선택 정렬

int main()
{
	Person a;
	//PersonArray Person(10);
	/*Person* pp = (Person*)0x1000;
	//PersonArray Person(10);
	
	cout << "class person의 크기:" << sizeof(a) << endl;
	cout << pp << endl;
	cout << pp + 1 << endl;*/
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening output.txt !!" << endl;
		exit(-1);
	}
	/* part 1 - handling class Date */
	Date AD010101(1, 1, 1);
	int year, month, day;
	int daysToChristmas;
	time_t currentTime;
	struct tm* time_and_date;

	time(&currentTime);
	time_and_date = localtime(&currentTime);
	year = time_and_date->tm_year + 1900;
	month = time_and_date->tm_mon + 1;
	day = time_and_date->tm_mday;
	Date newYearDay(year, 1, 1), today(year, month, day);

	fout << "AD Jan. 1, 1 is ";
	AD010101.fprintDate(fout);
	fout << endl;

	fout << "Today is ";
	today.fprintDate(fout);
	fout << endl;

	fout << "New year's day of this year was ";
	newYearDay.fprintDate(fout);
	fout << endl;

	Date christmas(year, 12, 25);
	fout << "Christmas of this year is ";
	christmas.fprintDate(fout);
	fout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())
	{
		fout << "Today is Christmas! Happy Christmas to you all !!\n";
	}
	else {
		fout << " Sorry, today is not Christmas!\n";
		daysToChristmas = christmas.getElapsedDaysFromAD010101() - today.getElapsedDaysFromAD010101();
		fout << " You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
	}
	fout << endl;

	/* part 2 - handling class Person */
	Person p1(string("Hong, Gil-Dong"), Date(2000, 1, 1)), p2;
	fout << "Person p1 : " << endl;
	p1.fprintPerson(fout);
	fout << endl;
	fout << "Person p2 : " << endl;
	p2.setName(string("Lee, Soo-Jeong"));
	p2.setBirthDate(Date(2018, 9, 1));
	p2.fprintPerson(fout);
	fout << endl;
	fout << endl << "Generating array of persons ... " << endl;
	/*Person* persons;
	persons = (Person*) new Person[NUM_PERSON];*/

	PersonArray persons(NUM_PERSON);
	srand((unsigned int)time(NULL));//rand 함수 사용하기 위해서
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].setRandPersonAttributes();
		persons[i].fprintPerson(fout);
		fout << endl;
	}
	//selectionSortbrithDate(persons);
	persons.sort();
	fout << endl << endl << "SelectionSortbrithDate of persons ... " << endl;
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].fprintPerson(fout);
		fout << endl;
	}
	/*selectionName(persons);
	fout << endl << endl << "SelectionName of persons ... " << endl;
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].fprintPerson(fout);
		fout << endl;
	}*/
	fout << endl;
	//delete[] persons;
	fout.close();
	return 0;
}

/*void selectionSortbrithDate(Person person[])
{
	Person tmp;
	Date a, b;
	int min_pos;
	//int y1, y2;
	for (int pos = 0; pos < NUM_PERSON; pos++)
	{
		min_pos = pos; //가장 첫번째 탐색구간을 min_pos로 지정
		a = person[min_pos].getBirthDate();
		//y1 = a.getYear();
		for (int j = pos + 1; j < NUM_PERSON; j++)
		{
			b = person[j].getBirthDate();
			//y2 = b.getYear();
			if (a.getYear() > b.getYear()) //j번째 단어가 min_pos 단어 보다 작을 경우
			{
				min_pos = j;//j번 째를 min_pos로 지정
				a = person[j].getBirthDate();
			}
			else if (a.getYear() == b.getYear())
			{
				if (a.getMonth() > b.getMonth())
				{
					min_pos = j;//j번 째를 min_pos로 지정
					a = person[j].getBirthDate();
				}
				else if (a.getMonth() == b.getMonth())
				{
					if (a.getDay() > b.getDay())
					{
						min_pos = j;//j번 째를 min_pos로 지정
						a = person[j].getBirthDate();
					}
				}
			}
		}
		if (min_pos != pos)
		{
			tmp = person[pos];  //pos 값을 temp로 복사
			person[pos] = person[min_pos]; //min_pos값을 pos로 옮겨주고
			person[min_pos] = tmp; //temp값을 min_pos값에 넣어준다
		}
	}
}*/

void selectionName(Person person[])
{
	Person tmp;
	string a, b;
	int min_pos;
	for (int pos = 0; pos < NUM_PERSON; pos++)
	{
		min_pos = pos; //가장 첫번째 탐색구간을 min_pos로 지정
		a = person[min_pos].getName();
		for (int j = pos + 1; j < NUM_PERSON; j++)
		{
			b = person[j].getName();
			if (a > b)
			{
				min_pos = j;
				a = person[j].getName();
			}

		}
		if (min_pos != pos)
		{
			tmp = person[pos];  //pos 값을 temp로 복사
			person[pos] = person[min_pos]; //min_pos값을 pos로 옮겨주고
			person[min_pos] = tmp; //temp값을 min_pos값에 넣어준다
		}
	}
}
void selectionSortbrithDate(Person person[])
{
	Person tmp;
	Date a, b;
	int min_pos;
	//int y1, y2;
	for (int pos = 0; pos < NUM_PERSON; pos++)
	{
		min_pos = pos; //가장 첫번째 탐색구간을 min_pos로 지정
		a = person[min_pos].getBirthDate();
		//y1 = a.getYear();
		for (int j = pos + 1; j < NUM_PERSON; j++)
		{
			b = person[j].getBirthDate();
			//y2 = b.getYear();
			if (a.getElapsedDaysFromAD010101() > b.getElapsedDaysFromAD010101()) //j번째 단어가 min_pos 단어 보다 작을 경우
			{
				min_pos = j;//j번 째를 min_pos로 지정
				a = person[j].getBirthDate();
			}
		}
		if (min_pos != pos)
		{
			tmp = person[pos];  //pos 값을 temp로 복사
			person[pos] = person[min_pos]; //min_pos값을 pos로 옮겨주고
			person[min_pos] = tmp; //temp값을 min_pos값에 넣어준다
		}
	}
}