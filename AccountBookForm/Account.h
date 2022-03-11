//Account.h
#ifndef _ACCOUNT_H
#define _ACCOUNT_H
#include "Date.h"
#include <string>
#include <concurrencysal.h>
typedef signed long int Long;
typedef double Currency;
using namespace std;

class Account {
public:
	Account();
	Account(Date date, string contents, Currency amount, Currency balance, string note);
	Account(const Account& source);
	Account& operator=(const Account& source);
	virtual ~Account() = 0;
	bool IsEqual(const Account& other);
	bool IsNotEqual(const Account& other);
	bool operator==(const Account& other);
	bool operator!=(const Account& other);
	Date& GetDate() const;
	string& GetContents() const;
	Currency GetAmount() const;
	Currency GetBalance() const;
	string& GetNote() const;

protected:
	Date date;
	string contents;
	Currency amount;
	Currency balance;
	string note;
};

inline Date& Account::GetDate() const {
	return const_cast<Date&>(this->date);
}

inline string& Account::GetContents() const {
	return const_cast<string&>(this->contents);
}

inline Currency Account::GetAmount() const {
	return (this->amount);
}

inline Currency Account::GetBalance() const {
	return (this->balance);
}

inline string& Account::GetNote() const {
	return const_cast<string&>(this->note);
}

#endif //_ACCOUNT_H
