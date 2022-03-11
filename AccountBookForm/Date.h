//Date.h
#ifndef _DATE_H
#define _DATE_H

typedef signed short int Short;

enum Month { JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6, JLY = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12 };
enum WeekDay { SUN = 0, MON = 1, TUE = 2, WED = 3, THU = 4, FRI = 5, SAT = 6 };

class Date {//scope_class
public:
	Date();//생성자 constructor
	~Date();//소멸자 destructor
	Date(Short year, Month month, Short day);
	Date(char(*date));
	static Date Today();
	bool IsEqual(const Date& other);
	Date Yesterday();
	Date Tomorrow();
	Date PreviousDate(Short days);
	Date NextDate(Short days);
	bool IsNotEqual(const Date& other);
	bool IsGreaterThan(const Date& other);
	bool IsLesserThan(const Date& other);
	Date(const Date& source);
	operator char* ();
	Date& operator=(const Date& source);
	bool operator==(const Date& other);
	bool operator!=(const Date& other);
	bool operator>(const Date& other);
	bool operator>=(const Date& other);
	bool operator <(const Date& other);
	bool operator<=(const Date& other);
	Date& operator --();
	Date operator --(int);
	Date& operator++();
	Date operator++(int);
	Date operator-(Short days);
	Date operator+(Short days);
	int GetYear() const;
	Month GetMonth() const;
	int GetDay() const;
	WeekDay GetWeekDay() const;

private://데이터멤버
	int year;
	Month month;
	int day;
	WeekDay weekDay;
};

inline int Date::GetYear() const {
	return this->year;
}

inline Month Date::GetMonth() const {
	return this->month;
}

inline int Date::GetDay() const {
	return this->day;
}

inline WeekDay Date::GetWeekDay() const {
	return this->weekDay;
}

#endif //_DATE_H
