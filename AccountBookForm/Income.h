//Income.h
#ifndef _INCOME_H
#define _INCOME_H
#include "Account.h"

class Income :public Account {
public:
	Income();
	Income(Date date, string contents, Currency amount, Currency balance, string note);
	Income(const Income& source);
	Income& operator=(const Income& source);
	virtual ~Income();
	bool IsEqual(const Income& other);
	bool IsNotEqual(const Income& other);
	bool operator==(const Income& other);
	bool operator!=(const Income& other);
};

#endif //_INCOME_H