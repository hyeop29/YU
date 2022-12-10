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
public: //외부로 공개된 멤버
	Date(); // default constructor
	Date(int y, int m, int d); // constructor 생성자
	~Date(); // 소멸자
	void inputDate();
	void fprintDate(ostream& fout); //class Data의 속성을 출력
	void setDate(int y, int m, int dy);
	void setRandDateAttributes(); //class Date의 멤버를 초기값 설정
	void setMonth(int m);
	void setYear(int y);
	int getYear() { return year; } // 인라인 함수(따로 정의할 필요없이 헤더파일에서 정의)
	int getMonth() { return month; } //Returns 1 for January, 2 for February, etc.
	int getDay() { return day; }
	int getYearDay(); //1월 1일 부터 몇일이 지났는 지 알려주는 함수
	int getYearDay(int m, int d);
	int getWeekDay(); //서기 1년 1월 1일부터 몇일이 지났는지를 이용하여 요일을 알려주는 함수
	int getElapsedDaysFromAD010101(); // 서기 1년 1월 1일부터 몇일이 지났는지 알려주는 함수
	int getElapsedDaysFromAD010101(Date);

private: //외부 접근 x
	bool isLeapYear(); // class의 데이터 멤버에 있는 year이 윤년인지 판단하는 함수
	bool isLeapYear(int y); // y가 윤년인가 판단하여 true 또는 false 반환
	bool isValidDate(int y, int m, int d); // 전달된 연월일 값들이 정상적인 값을 가지는 지 판단하는 함수
	int year; 
	int month;
	int day;
};
#endif

