#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <cstdlib>
using namespace std;
class Date  //날짜에 대한 클래스
{
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor 생성자
	void inputDate();  //입력
	void printDate();  //출력
	void setDate(int y, int m, int d); //해당 날짜가 정상 범위인지 확인
	void setMonth(int newMonth);
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	int getYearDay(); //1월 1일부터 누적해서 몇번째 날?
	int getWeekDay(); //무슨 요일?
	int getElapsedDays(); // 서기 1년 1월 1일 부터 누적된 날?
	// get elapsed days from AD 1. 1. 1.
private: //내부적 사용
	bool isLeapYear();
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);
	int year; //연
	int month;  //월
	int day;  //일
};
#endif
