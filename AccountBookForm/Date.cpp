//Date.cpp
#include "Date.h"
#include<ctime>
#include<stdio.h>
#pragma warning (disable:4996)

Date::Date() {
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}

Date::~Date() {}

Date Date::Today() {
	time_t timer;
	struct tm* today;
	Date today_;
	time(&timer);
	today = localtime(&timer);
	today_.year = today->tm_year + 1900;
	today_.month = static_cast<Month>(today->tm_mon + 1);
	today_.day = today->tm_mday;
	today_.weekDay = static_cast<WeekDay>(today->tm_wday);
	return today_;
}

Date Date::Yesterday() {
	struct tm yesterday = { 0, };
	Date yesterday_;

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;
	mktime(&yesterday);
	yesterday_.year = yesterday.tm_year + 1900;
	yesterday_.month = static_cast<Month>(yesterday.tm_mon + 1);
	yesterday_.day = yesterday.tm_mday;
	yesterday_.weekDay = static_cast<WeekDay>(yesterday.tm_wday);
	return yesterday_;
}

Date Date::Tomorrow() {
	struct tm tomorrow = { 0, };
	Date tomorrow_;

	tomorrow.tm_year = this->year - 1900;
	tomorrow.tm_mon = this->month - 1;
	tomorrow.tm_mday = this->day + 1;
	mktime(&tomorrow);
	tomorrow_.year = tomorrow.tm_year + 1900;
	tomorrow_.month = static_cast<Month>(tomorrow.tm_mon + 1);
	tomorrow_.day = tomorrow.tm_mday;
	tomorrow_.weekDay = static_cast<WeekDay>(tomorrow.tm_wday);
	return tomorrow_;
}

Date Date::NextDate(Short days) {
	struct tm nextDate = { 0, };
	Date nextDate_;

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;
	mktime(&nextDate);
	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);
	return nextDate_;
}

Date Date::PreviousDate(Short days) {
	struct tm previousDate = { 0, };
	Date previousDate_;

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;
	mktime(&previousDate);
	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);
	return previousDate_;
}

bool Date::IsEqual(const Date& other) {
	bool ret = false;
	if (this->year == other.year && this->month == other.month && this->day && other.day) {
		ret = true;
	}
	return ret;
}

bool Date::IsNotEqual(const Date& other) {
	bool ret = false;
	if (this->year != other.year || this->month != other.month || this->day != other.day) {
		ret = true;
	}
	return ret;
}

bool Date::IsGreaterThan(const Date& other) {
	bool ret = false;
	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		ret = true;
	}
	return ret;
}

bool Date::IsLesserThan(const Date& other) {
	bool ret = false;
	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		ret = true;
	}
	return ret;
}

Date::Date(Short year, Month month, Short day) {
	struct tm date = { 0, };
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;
	mktime(&date);
	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);
}

Date::Date(char(*date)) {
	sscanf(date, "%4d%02d%02d", &this->year, &this->month, &this->day);
	struct tm date_ = { 0, };
	date_.tm_year = this->year - 1900;
	date_.tm_mon = this->month - 1;
	date_.tm_mday = this->day;
	mktime(&date_);
	this->year = date_.tm_year + 1900;
	this->month = static_cast<Month>(date_.tm_mon + 1);
	this->day = date_.tm_mday;
	this->weekDay = static_cast<WeekDay>(date_.tm_wday);
}

Date::Date(const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;

}

Date& Date::operator=(const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;
	return *this;
}

Date::operator char* () {
	static char buffer[9];
	sprintf(buffer, "%4d%02d%02d", this->year, this->month, this->day);
	return buffer;
}

bool Date::operator==(const Date& other) {
	bool ret = false;
	if (this->year == other.year && this->month == other.month && this->day == other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator!=(const Date& other) {
	bool ret = false;
	if (this->year != other.year || this->month!=other.month || this->day != other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator>(const Date& other) {
	bool ret = false;
	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator>=(const Date& other) {
	bool ret = false;
	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day >= other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator < (const Date& other) {
	bool ret = false;
	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator<=(const Date& other) {
	bool ret = false;
	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month< other.month){
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day <= other.day) {
		ret = true;
	}
	return ret;
}

Date& Date::operator--(){
	struct tm yesterday = { 0, };
	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;
	mktime(&yesterday);
	this->year = yesterday.tm_year + 1900;
	this->month = static_cast<Month>(yesterday.tm_mon + 1);
	this->day = yesterday.tm_mday;
	this->weekDay = static_cast<WeekDay>(yesterday.tm_wday);
	return *this;
}

Date Date::operator--(int) {
	struct tm date = { 0, };
	Date yesterday(*this);
	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;
	mktime(&date);
	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);
	return yesterday;
}

Date& Date::operator++() {
	struct tm date = { 0, };
	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;
	mktime(&date);
	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);
	return *this;
}

Date Date::operator++(int) {
	struct tm date = { 0, };
	Date tomorrow(*this);
	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;
	mktime(&date);
	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);
	return tomorrow;
}

Date Date::operator-(Short days) {
	struct tm previousDate = { 0, };
	Date previousDate_;

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;
	mktime(&previousDate);
	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);
	return previousDate_;
}

Date Date::operator+(Short days) {
	struct tm nextDate = { 0, };
	Date nextDate_;

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;
	mktime(&nextDate);
	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);
	return nextDate_;
}


/*
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Date date;
	Date today;
	Date yesterday;
	Date tomorrow;
	Date previousDate;
	Date nextDate;
	bool ret;
	today = date.Today();
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << endl;
	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-"
		<< yesterday.GetMonth() << "-"
		<< yesterday.GetDay() << endl;
	tomorrow = today.Tomorrow();
	cout << tomorrow.GetYear() << "-"
		<< tomorrow.GetMonth() << "-"
		<< tomorrow.GetDay() << endl;
	previousDate = tomorrow.PreviousDate(2);
	cout << previousDate.GetYear() << "-"
		<< previousDate.GetMonth() << "-"
		<< previousDate.GetDay() << endl;
	nextDate = today.NextDate(3);
	cout << nextDate.GetYear() << "-"
		<< nextDate.GetMonth() << "-"
		<< nextDate.GetDay() << endl;
	ret = yesterday.IsEqual(previousDate);
	if (ret == true) {
		cout << "날짜가 같습니다" << endl;
	}
	ret = tomorrow.IsNotEqual(nextDate);
	if (ret == true) {
		cout << "날짜가 다릅니다" << endl;
	}
	ret = tomorrow.IsGreaterThan(previousDate);
	if (ret == true) {
		cout << "날짜가 큽니다" << endl;
	}
	ret = today.IsLesserThan(tomorrow);
	if (ret == true) {
		cout << "날짜가 작습니다" << endl;
	}

	Date birthday(static_cast<Short>(2021), JAN, static_cast<Short>(1));
	cout << birthday.GetYear() << "-" << birthday.GetMonth() << "-" << birthday.GetDay() << endl;

	Date other((char(*))("20210101"));
	cout << other.GetYear() << "-" << other.GetMonth() << "-" << other.GetDay() << endl;

	cout << static_cast<char*>(today) << endl;

	if (yesterday == previousDate) {
		cout << "날짜가 같습니다" << endl;
	}

	tomorrow = yesterday-- +(static_cast<Short>(2));
	cout << tomorrow.GetYear() << "-" << tomorrow.GetMonth() << "-" << tomorrow.GetDay() << endl;

	today = --yesterday + (static_cast<Short>(3));
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;
	return 0;
}
*/