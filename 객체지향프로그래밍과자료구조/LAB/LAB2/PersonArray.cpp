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
		min_pos = pos; //���� ù��° Ž�������� min_pos�� ����
		a = per[min_pos].getBirthDate();
		//y1 = a.getYear();
		for (int j = pos + 1; j < size(); j++)
		{
			b = per[j].getBirthDate();
			//y2 = b.getYear();
			if (a.getElapsedDaysFromAD010101() > b.getElapsedDaysFromAD010101()) //j��° �ܾ min_pos �ܾ� ���� ���� ���
			{
				min_pos = j;//j�� °�� min_pos�� ����
				a = per[j].getBirthDate();
			}
		}
		if (min_pos != pos)
		{
			tmp = per[pos];  //pos ���� temp�� ����
			per[pos] = per[min_pos]; //min_pos���� pos�� �Ű��ְ�
			per[min_pos] = tmp; //temp���� min_pos���� �־��ش�
		}
	}
}
Person& PersonArray::operator[](int index)const
{
	return per[index];
}