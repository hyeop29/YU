#include <iostream>
#include <string>
#include "Date.h"
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT
};
Date::Date() //default constructor
{
	year = 0; month = 0; day = 0; //년, 월, 일을 0으로 설정
}
//constructor with given arguments
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}
void Date::setMonth(int newMonth)
{
	if ((newMonth >= 1) && (newMonth <= 12))
		month = newMonth;
	else
	{
		cout << "Illegal month value! Program aborted.\n";
			exit(1);
	}
	day = 1;
}
void Date::setDate(int y, int m, int d)
{
	year = y; //년도 설정
	if ((m >= 1) && (m <= 12))
		month = m;
	else
	{
		cout << "Illegal month value! Program aborted.\n";
			exit(1);
	}
	if ((d >= 1) && (d <= 31))
		day = d;
	else
	{
		cout << "Illegal day value! Program aborted.\n";
			exit(1);
	}
}
bool Date::isLeapYear(int y)  //y가 윤년인지 아닌지 확인
{
	if (((y % 4 == 0) && (y % 100 != 0)) || ((y % 400) == 0)) //4의 배수고 100의 배수가 아니거나 400의 배수면 윤년
		return true;
	else
		return false;
}
bool Date::isLeapYear() // year가 윤년인지 아닌지 확인
{
	return isLeapYear(year);
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
int Date::getElapsedDays()
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < year; y++)
	{
		if (isLeapYear(y))
			elpsDay += 366;
		elpsDay += 365;
	}
	yearDay = getYearDay();
	elpsDay += yearDay;
	return elpsDay;
}
int Date::getWeekDay()
{
	int weekDay_AD010101 = MON;
	// AD Jan. 1, 1 was Monday
	int yearDay;
	int weekDay;
	int elapsedDays = 0;
	yearDay = (getElapsedDays());
	weekDay = yearDay % 7;
	return weekDay;
}
void Date::inputDate()
{
	int y, m, d;
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;
	if (isValidDate(y, m, d))
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
bool Date::isValidDate(int y, int m, int d)
{
	int days_month[13] = { 0, 31, 28, 31, 30,
	31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear(y))
		days_month[2] = 29;
	if ((m >= 1) && (m <= 12) &&
		(d >= 1) && (d <= days_month[m]))
	{
		return true;
	}
	else {
		cout << "Ilegal date! (" << m << ", "
			<< d << ") ==> Program aborted.\n";
		return false;
	}
}
void Date::printDate()
{
	const char* weekDayName[7] = { "Sunday",
	"Monday", "Tuesday", "Wednesday",
	"Thursday", "Friday", "Saturday" };
	const char* monthName[13] = { "", "January",
	"February", "March", "April", "May",
	"June", "July", "August", "September",
	"October", "November", "December" };
	int yearDay = 0;
	int weekDay;
	char todayWeekDayName[10];
	if ((month >= 1) && (month <= 12))
		cout << string(monthName[month]);
	cout << " " << day << ", " << year;
	yearDay = getYearDay();
	weekDay = getWeekDay();
	cout << " ("
		<< string(weekDayName[weekDay])
		<< ")";
}