//AccountBook.h
#ifndef _ACCOUNTBOOK_H
#define _ACCOUNTBOOK_H
#include "Array.h"
#include "Account.h"

class Account;
class AccountBook {
public:
	AccountBook(Long capacity = 256);
	AccountBook(const AccountBook& source);
	AccountBook& operator=(const AccountBook& source);
	~AccountBook();
	void FindByAmount(Currency amount, Long* (*indexes), Long* count);
	Long Record(Date date, string contents, Currency amount, string note);
	void Find(string contents, Long* (*indexes), Long* count);
	void Find(Date startDate, Date endDate, Long* (*indexes), Long* count);
	void Find(Date startDate, Date endDate, string contents, Long* (*indexes), Long* count);
	Long Correct(Long index, Currency amount, string note);
	void Calculate(Date startDate, Date endDate, Currency* totalIncome, Currency* TotalOutgo, Currency* balance);
	Account* GetAt(Long index);
	Long GetCapacity() const;
	
	Long GetLength() const;

private:
	Array<Account*>accounts;
	Long capacity;
	Long length;
};

inline Long AccountBook::GetCapacity() const {
	return this->capacity;
}

inline Long AccountBook::GetLength() const {
	return this->length;
}
int CompareAmount(void* one, void* other);
int CompareContents(void* one, void* other);
#endif //_ACCOUNTBOOK_H