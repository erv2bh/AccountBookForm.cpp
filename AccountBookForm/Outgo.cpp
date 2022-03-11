//Outgo.cpp
#include "Outgo.h"
Outgo::Outgo() {
}

Outgo::Outgo(Date date, string contents, Currency amount, Currency balance, string note)
	:Account(date, contents, amount, balance, note){
}

Outgo::Outgo(const Outgo& source)
	:Account(source) {
}

Outgo& Outgo::operator=(const Outgo& source) {
	Account::operator=(source);
	return *this;
}

Outgo::~Outgo() {
}

bool Outgo::IsEqual(const Outgo& other) {
	return Account::IsEqual(other);
}

bool Outgo::IsNotEqual(const Outgo& other) {
	return Account::IsNotEqual(other);
}

bool Outgo::operator==(const Outgo& other) {
	return Account::operator==(other);
}

bool Outgo::operator!=(const Outgo& other) {
	return Account::operator!=(other);
}