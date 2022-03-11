//Outgo.h
#ifndef _OUTGO_H
#define _OUTGO_H
#include "Account.h"

class Outgo :public Account {
public:
	Outgo();
	Outgo(Date date, string contents, Currency amount, Currency balance, string note);
	Outgo(const Outgo& source);
	Outgo& operator=(const Outgo& source);
	~Outgo();
	bool IsEqual(const Outgo& other);
	bool IsNotEqual(const Outgo& other);
	bool operator==(const Outgo& other);
	bool operator!=(const Outgo& other);
};


#endif //_OUTGO_H