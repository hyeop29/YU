#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <cstdlib>
using namespace std;
class Date  //��¥�� ���� Ŭ����
{
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor ������
	void inputDate();  //�Է�
	void printDate();  //���
	void setDate(int y, int m, int d); //�ش� ��¥�� ���� �������� Ȯ��
	void setMonth(int newMonth);
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	int getYearDay(); //1�� 1�Ϻ��� �����ؼ� ���° ��?
	int getWeekDay(); //���� ����?
	int getElapsedDays(); // ���� 1�� 1�� 1�� ���� ������ ��?
	// get elapsed days from AD 1. 1. 1.
private: //������ ���
	bool isLeapYear();
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);
	int year; //��
	int month;  //��
	int day;  //��
};
#endif
