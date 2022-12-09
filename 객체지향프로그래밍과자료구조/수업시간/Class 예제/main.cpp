#include <iostream>
#include <time.h>
#include "Date.h"
using namespace std;

int main()
{
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
	Date newYearDay(year, 1, 1),
		today(year, month, day);
	cout << "AD Jan. 1, 1 is ";
	AD010101.printDate();
	cout << endl;
	cout << "Today is ";
	today.printDate();
	cout << endl;
	cout << "New year's day of this year was ";
	newYearDay.printDate();
	cout << endl;
	//christmas.setDate(12, 25, 2020);
	Date christmas(year, 12, 25);
	cout << "Christmas of this year is ";
	christmas.printDate();
	cout << endl;
	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())
	{
		cout << "Today is Christmas! Happy Christmas to you all !!\n";
	}
	else {
		cout << "Sorry, today is not Christmas!";
		daysToChristmas =
			christmas.getElapsedDays() - today.getElapsedDays();
		cout << " You must wait "
			<< daysToChristmas << " day(s) to Christmas !"
			<< endl;
	}
	return 0;
}