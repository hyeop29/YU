#include "PersonArray.h"
#include "Person.h"
PersonArray::PersonArray(int size)
{
	person_num = size;
	per = new Person[size];
}
PersonArray::~PersonArray()
{
	//cout << "MtrxArray :: destructor" << endl;
	/*if (students != NULL) {
		delete[] students;
	}*/
}
void PersonArray::sort()
{
	Person tmp;
	Date a, b;
	int min_pos;
	//int y1, y2;
	for (int pos = 0; pos < size(); pos++)
	{
		min_pos = pos; //가장 첫번째 탐색구간을 min_pos로 지정
		a = per[min_pos].getBirthDate();
		//y1 = a.getYear();
		for (int j = pos + 1; j < size(); j++)
		{
			b = per[j].getBirthDate();
			//y2 = b.getYear();
			if (a.getElapsedDaysFromAD010101() > b.getElapsedDaysFromAD010101()) //j번째 단어가 min_pos 단어 보다 작을 경우
			{
				min_pos = j;//j번 째를 min_pos로 지정
				a = per[j].getBirthDate();
			}
		}
		if (min_pos != pos)
		{
			tmp = per[pos];  //pos 값을 temp로 복사
			per[pos] = per[min_pos]; //min_pos값을 pos로 옮겨주고
			per[min_pos] = tmp; //temp값을 min_pos값에 넣어준다
		}
	}
}
Person& PersonArray::operator[](int index)const
{
	return per[index];
}