#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"

enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, NUM_MONTHS };
const char* weekDayName[DAYS_PER_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday",
"Thursday", "Friday", "Saturday" };
const char* weekDayNameShort[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI",
"SAT" };
const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };

Date::Date() //생성자
{            //년, 월, 일을 모두 0으로 설정
	year = 0;
	month = 0;
	day = 0;
}

Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}

Date::~Date() //소멸자
{
	// cout << "Date object instance is destructed" << endl;
}
bool Date::isValidDate(int y, int m, int d) 
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear(y)) //윤년이 경우
		days_month[2] = 29;
	if ((m >= 1) && (m <= 12) && (d >= 1) && (d <= days_month[m])) //해당 월에 날짜 수만큼 맞게 입력했는지
	{
		return true;
	}
	else {
		cout << "Illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}

void Date::setDate(int y, int m, int d)
{
	if (isValidDate(y, m, d))
	{
		year = y;
		month = m;
		day = d;
	}
	else {
		cout << "Invalid date (" << y << ", " << m << ", " << d << ")";
		cout << " Program aborted !!\n";
		exit(1);
	}
}
void Date::setRandDateAttributes()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	year = rand() % 2000 + 1000;
	month = rand() % 12 + 1;
	if (isLeapYear(year) && month == 2)
		days_month[2] = 29;
	day = rand() % days_month[month] + 1;
}
void Date::setMonth(int newMonth)
{
	if ((newMonth >= 1) && (newMonth <= 12)) //이 조건이 맞다면 month로 지정 그렇지 않으면 종료
		month = newMonth;
	else
	{
		cout << "Illegal month value! Program aborted.\n";
		exit(1);
	}
	day = 1; //day는 그 달의 첫번째 날로 설정
}
void Date::setYear(int y)
{
	year = y;
}
int Date::getYearDay()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31,
	30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;
	if (isLeapYear())
		days_month[2] = 29;
	for (int m = 1; m < month; m++)
		yearDay += days_month[m];
	yearDay += day;
	return yearDay;
}
int Date::getYearDay(int month, int day)
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31,
		30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;
	if (isLeapYear()) //해당 년이 윤년이면
		days_month[2] = 29; //2월달은 29일
	for (int m = 1; m < month; m++)
		yearDay += days_month[m]; //month전 까지 달의 날짜를 다 더해준다
	yearDay += day; //거기다가 그 달의 day를 더해준다
	return yearDay;
}
int Date::getElapsedDaysFromAD010101()
{
	int elpsDay = 0;
	elpsDay = getElapsedDaysFromAD010101(*this);
	return elpsDay;
}
int Date::getElapsedDaysFromAD010101(Date d)
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < d.year; y++)//year 직전 연도까지 날짜를 다 더해준다
	{
		if (isLeapYear(y))//윤년이면
			elpsDay += 366;//366일
		else
			elpsDay += 365;
	}
	yearDay = getYearDay(d.month, d.day); //
	elpsDay += yearDay;
	return elpsDay;
}
int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // 1. 1. 1. is Monday
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDaysFromAD010101();
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7; //요일은 7단위로 돌아가므로 7의 나머지 사용
	//cout << ", Elapsed days from AD Jan. 1, 1 (" << elapsedDays << ")";
	return weekDay;
}
void Date::inputDate()
{
	int y, m, d;
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;
	if (isValidDate(y, m, d)) //이 날짜들이 정상적인가 확인
	{
		year = y;
		month = m;
		day = d;
	}
	else {
		cout << "Ilegal date! Program aborted.\n";
		exit(1);
	}
}
bool Date::isLeapYear(int y)
{
	if (((y % 4 == 0) && (y % 100 != 0)) || ((y % 400) == 0)) //4의 배수고 100의 배수가 아니거나 400의 배수면 윤년
		return true;
	else
		return false;
}
bool Date::isLeapYear()
{
	return isLeapYear(year);
}
void Date::fprintDate(ostream& fout)
{
	const char* weekDayName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
	"Friday", "Saturday" };
	const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December" };
	int yearDay = 0;
	int weekDay;
	if ((month >= 1) && (month <= 12))
		fout << setw(10) << string(monthName[month]);
	fout << " " << setw(2) << day << ", " << setw(4) << year;
	yearDay = getYearDay();
	weekDay = getWeekDay();
	fout << " (" << setw(10) << string(weekDayName[weekDay]) << ")";
}