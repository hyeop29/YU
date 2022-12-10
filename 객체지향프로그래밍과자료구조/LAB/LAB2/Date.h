#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

#define WEEKDAY_AD01Jan01 MON // the weekday of AD Jan 1.
#define DAYS_PER_WEEK 7
#define Secs_in_Minute 60
#define Secs_in_Hour (Secs_in_Minute * 60)
#define Secs_in_DAY (Secs_in_Hour * 24)
#define LOCAL_GMT_OFFSET_HOUR 9

class Date
{
public: //�ܺη� ������ ���
	Date(); // default constructor
	Date(int y, int m, int d); // constructor ������
	~Date(); // �Ҹ���
	void inputDate();
	void fprintDate(ostream& fout); //class Data�� �Ӽ��� ���
	void setDate(int y, int m, int dy);
	void setRandDateAttributes(); //class Date�� ����� �ʱⰪ ����
	void setMonth(int m);
	void setYear(int y);
	int getYear() { return year; } // �ζ��� �Լ�(���� ������ �ʿ���� ������Ͽ��� ����)
	int getMonth() { return month; } //Returns 1 for January, 2 for February, etc.
	int getDay() { return day; }
	int getYearDay(); //1�� 1�� ���� ������ ������ �� �˷��ִ� �Լ�
	int getYearDay(int m, int d);
	int getWeekDay(); //���� 1�� 1�� 1�Ϻ��� ������ ���������� �̿��Ͽ� ������ �˷��ִ� �Լ�
	int getElapsedDaysFromAD010101(); // ���� 1�� 1�� 1�Ϻ��� ������ �������� �˷��ִ� �Լ�
	int getElapsedDaysFromAD010101(Date);

private: //�ܺ� ���� x
	bool isLeapYear(); // class�� ������ ����� �ִ� year�� �������� �Ǵ��ϴ� �Լ�
	bool isLeapYear(int y); // y�� �����ΰ� �Ǵ��Ͽ� true �Ǵ� false ��ȯ
	bool isValidDate(int y, int m, int d); // ���޵� ������ ������ �������� ���� ������ �� �Ǵ��ϴ� �Լ�
	int year; 
	int month;
	int day;
};
#endif

