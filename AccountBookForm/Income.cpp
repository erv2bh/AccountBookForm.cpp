//Income.cpp
#include "Income.h"

Income::Income(){
}

Income::Income(Date date, string contents, Currency amount, Currency balance, string note)
	:Account(date, contents, amount, balance, note) {
}

Income::Income(const Income& source)
	: Account(source) {
}

Income& Income::operator=(const Income& source) {
	Account::operator=(source);
	return *this;
}

Income::~Income() {
}

bool Income::IsEqual(const Income& other) {
	return Account::IsEqual(other);
}

bool Income::IsNotEqual(const Income& other) {
	return Account::IsNotEqual(other);
}

bool Income::operator==(const Income& other) {
	return Account::operator== (other);
}

bool Income::operator!=(const Income& other) {
	return Account::operator!=(other);
}
