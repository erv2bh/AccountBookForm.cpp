//AccountBook.cpp
#include "AccountBook.h"
#include "Income.h"
#include "Outgo.h"
#include <string>
using namespace std;

AccountBook::AccountBook(Long capacity)
	:accounts(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

AccountBook::~AccountBook() {
	int i = 0;
	while (i < this->length) {
		delete[] this->accounts[i];
		i++;
	}
}

Account* AccountBook::GetAt(Long index) {
	return this->accounts.GetAt(index);
}
AccountBook::AccountBook(const AccountBook& source) {
	int i = 0;
	while (i < source.length) {
		Account* account = const_cast<AccountBook&>(source).accounts.GetAt(i);
		if (dynamic_cast<Income*>(account)) {
			this->accounts[i] = new Income(*dynamic_cast<Income*>(account));
		}	
		else if (dynamic_cast<Outgo*>(account)) {
			this->accounts[i] = new Outgo(*dynamic_cast<Outgo*>(account));
		}
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

AccountBook& AccountBook::operator=(const AccountBook& source) {
	int i = 0;
	if (this->length > 0) {
		while (i < this->length) {
			delete[] this->accounts[i];
			i++;
		}
	}
	i = 0;
	while (i < source.length) {
		Account* account = const_cast<AccountBook&>(source).accounts.GetAt(i);
		if (dynamic_cast<Income*>(account)) {
			this->accounts[i] = new Income(*dynamic_cast<Income*>(account));
		}
		else if (dynamic_cast<Outgo*>(account)) {
			this->accounts[i] = new Outgo(*dynamic_cast<Outgo*>(account));
		}
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}

Long AccountBook::Record(Date date, string contents, Currency amount, string note) {
	Account* account = 0;
	Currency balance = 0;
	if (this->length == 0) {
		balance = amount;
	}
	else if (this->length > 0) {
		balance = this->accounts[this->length-1]->GetBalance();
		balance = balance + amount;
	}
	
	Long index = this->length;
	if (amount > 0) {
		account = new Income(date, contents, amount, balance, note);
	}
	else if (amount < 0) {
		account = new Outgo(date, contents, amount, balance, note);
	}
	if (this->length < this->capacity) {
		index = this->accounts.Store(index, account);
	}
	else if (this->length >= this->capacity) {
		index = this->accounts.AppendFromRear(account);
		this->capacity++;
	}
	this->length++;
	return index;
}

void AccountBook::Find(string contents, Long* (*indexes), Long* count) {
	this->accounts.LinearSearchDuplicate(&contents, indexes, count, CompareContents);
}

void AccountBook::FindByAmount(Currency amount, Long* (*indexes), Long* count) {
	this->accounts.LinearSearchDuplicate(&amount, indexes, count, CompareAmount);
}

int CompareAmount(void* one, void* other) {
	int ret;
	if (((*(static_cast<Account**>(one)))->GetAmount() > (*static_cast<Currency*>(other)))) {
		ret = 1;
	}
	else if (((*(static_cast<Account**>(one)))->GetAmount() == (*static_cast<Currency*>(other)))) {
		ret = 0;
	}
	else if (((*(static_cast<Account**>(one)))->GetAmount() < (*static_cast<Currency*>(other)))) {
		ret = -1;
	}
	return ret;
}

int CompareContents(void* one, void* other) {
	return ((*(static_cast<Account**>(one)))->GetContents().compare(*static_cast<string*>(other)));
}

void AccountBook::Find(Date startDate, Date endDate, Long* (*indexes), Long* count) {
	*count = 0;
	*indexes = new Long[this->length];
	int i = 0;
	int j = 0;
	while (i < this->length) {
		if (this->accounts.GetAt(i)->GetDate() >= startDate && this->accounts.GetAt(i)->GetDate() <= endDate) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

void AccountBook::Find(Date startDate, Date endDate, string contents, Long* (*indexes), Long* count) {
	*count = 0;
	*indexes = new Long[this->length];
	int i = 0;
	int j = 0;
	while (i < this->length) {
		if (this->accounts[i]->GetDate() >= startDate && this->accounts[i]->GetDate() <= endDate) {
			if (this->accounts[i]->GetContents().compare(contents) == 0) {
				(*indexes)[j] = i;
				j++;
				(*count)++;
			}
		}
		i++;
	}
}

Long AccountBook::Correct(Long index, Currency amount, string note) {
	Long modifyIndex;
	Account* account=0;
	Currency difference=0;
	Currency balance=0;
	Currency prevAmount=0;
	prevAmount = this->accounts[index]->GetAmount();
	
	difference = amount - prevAmount;
	if (index > 0) {
		balance = this->accounts[index]->GetBalance();
		balance = balance + difference;
	}
	else {
		balance = this->accounts[index]->GetBalance();
		balance = balance + difference;
	}
	
	
	account = this->accounts.GetAt(index);
	if (dynamic_cast<Income*>(account)) {
		account = new Income(this->accounts[index]->GetDate(),
			this->accounts[index]->GetContents(),
			amount, balance, note);
	}
	else if (dynamic_cast<Outgo*>(account)) {
		account = new Outgo(this->accounts[index]->GetDate(),
			this->accounts[index]->GetContents(),
			amount, balance, note);
	}
	modifyIndex = this->accounts.Modify(index, account);
	if (index > 0) {
		int i = 1;
		while (index + i < this->length) {
			account = this->accounts.GetAt(index + i);
			balance = this->accounts[index + i]->GetBalance();
			balance = balance + difference;
			if (dynamic_cast<Income*>(account)) {
				account = new Income(this->accounts[index + i]->GetDate(),
					this->accounts[index + i]->GetContents(),
					this->accounts[index + i]->GetAmount(), balance, this->accounts[index + i]->GetNote());
			}
			else if (dynamic_cast<Outgo*>(account)) {
				account = new Outgo(this->accounts[index + i]->GetDate(),
					this->accounts[index + i]->GetContents(),
					this->accounts[index + i]->GetAmount(), balance, this->accounts[index + i]->GetNote());
			}
			this->accounts.Modify(index + i, account);
			i++;
		}
	}
	else {
		int i = 1;
		int j = 0;
		while (index + i < this->length) {
			account = this->accounts.GetAt(index + i);
			balance = this->accounts[index + j]->GetBalance();
			amount = this->accounts[index + i]->GetAmount();
			if (dynamic_cast<Income*>(account)) {
				balance = balance + amount;
				account = new Income(this->accounts[index + i]->GetDate(),
					this->accounts[index + i]->GetContents(),
					this->accounts[index + i]->GetAmount(), balance, this->accounts[index + i]->GetNote());
			}
			else if (dynamic_cast<Outgo*>(account)) {
				balance = balance - amount;
				account = new Outgo(this->accounts[index + i]->GetDate(),
					this->accounts[index + i]->GetContents(),
					this->accounts[index + i]->GetAmount(), balance, this->accounts[index + i]->GetNote());
			}
			this->accounts.Modify(index + i, account);
			i++;
			j++;
		}
	}
	return modifyIndex;
}

void AccountBook::Calculate(Date startDate, Date endDate, Currency* totalIncome, Currency* totalOutgo, Currency* balance) {
	int i = 0;
	*totalIncome=0;
	*totalOutgo = 0;
	*balance = 0;
	while (i < this->length) {
		if (this->accounts[i]->GetDate() >= startDate && this->accounts[i]->GetDate() <= endDate) {
			Account* account = this->accounts.GetAt(i);
			if (dynamic_cast<Income*>(account)) {
				(*totalIncome) = (*totalIncome) + this->accounts[i]->GetAmount();
			}
			else if (dynamic_cast<Outgo*>(account)) {
				(*totalOutgo) = (*totalOutgo) + this->accounts[i]->GetAmount();
			}
			(*balance) = (*totalIncome) + (*totalOutgo);
		}
		i++;
	}
}


#include <iostream>
int main(int argc, char* argv[]) {
	AccountBook accountBook(256);
	Account* account;
	Long(*indexes);
	Long count;
	Long index;
	Date date;
	string contents;
	Date today = date.Today();
	Date tomorrow = today.Tomorrow();
	index = accountBook.Record(today, "용돈", 500000, "없음");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;

	index = accountBook.Record(tomorrow, "교통비", -55000, "없음");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
	
	index = accountBook.Record(tomorrow, "식사", -10000, "없음");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;

	index = accountBook.Record(tomorrow, "알바비", 100000, "없음");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
	
	cout << "적요로 찾기" << endl;
	contents = "알바비";
	accountBook.Find(contents, &indexes, &count);
	int i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}
	
	cout << "날짜로 찾기" << endl;

	indexes = 0;
	count = 0;
	accountBook.Find(today, tomorrow, &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}

	cout << "날짜&적요로 찾기" << endl;
	indexes = 0;
	count = 0;
	accountBook.Find(today, tomorrow, "용돈", &indexes, &count);
	i = 0;
	while (i < count) {
		account = accountBook.GetAt(indexes[i]);
		cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}

	index = 0;
	index = accountBook.Correct(0, 600000, "금액 변경");
	account = accountBook.GetAt(index);
	cout << account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
	
	Currency totalIncome;
	Currency totalOutgo;
	Currency balance;
	accountBook.Calculate(today, tomorrow, &totalIncome, &totalOutgo, &balance);
	cout << " 총 수입  " << totalIncome << " 총 지출  " << totalOutgo << " 차액  " << balance << endl;
	

	i = 0;
	while (i < accountBook.GetLength()) {
		account = accountBook.GetAt(i);
		cout<< account->GetDate() << " " << account->GetContents() << " " << account->GetAmount() << " " << account->GetBalance() << " " << account->GetNote() << endl;
		i++;
	}

	return 0;
}