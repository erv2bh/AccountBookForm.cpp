//Account.cpp
#include "Account.h"
Account::Account()
	:date(Date::Today()), contents(""), note("") {
	this->amount = 0.0;
	this->balance = 0.0;
}

Account::Account(Date date, string contents, Currency amount, Currency balance, string note)
	: date(date), contents(contents), note(note) {
	this->amount = amount;
	this->balance = balance;
}

Account::Account(const Account& source)
	: date(source.date), contents(source.contents), note(source.note) {
	this->amount = source.amount;
	this->balance = source.balance;
}

Account& Account::operator =(const Account& source) {
	this->date = source.date;
	this->contents = source.contents;
	this->amount = source.amount;
	this->balance = source.balance;
	this->note = source.note;
	return *this;
}

Account::~Account(){}

bool Account::IsEqual(const Account& other) {
	bool ret = false;
	if (this->date == other.date && this->contents.compare(other.contents) == 0 && this->amount == other.amount && this->balance == other.balance && this->note.compare(other.note) == 0) {
		ret = true;
	}
	return ret;
}

bool Account::IsNotEqual(const Account& other) {
	bool ret = false;
	if (this->date != other.date || this->contents.compare(other.contents) != 0 || this->amount != other.amount || this->balance != other.balance || this->note.compare(other.note) != 0) {
		ret = true;
	}
	return ret;
}

bool Account::operator==(const Account& other) {
	bool ret = false;
	if (this->date == other.date && this->contents.compare(other.contents) == 0 && this->amount == other.amount && this->balance == other.balance && this->note.compare(other.note) == 0) {
		ret = true;
	}
	return ret;
}

bool Account::operator!=(const Account& other) {
	bool ret = false;
	if (this->date != other.date || this->contents.compare(other.contents) != 0 || this->amount != other.amount || this->balance != other.balance || this->note.compare(other.note) != 0) {
		ret = true;
	}
	return ret;
}