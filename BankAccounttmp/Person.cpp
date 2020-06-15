#include"Person.h"
#include<string>
#include<iostream>
using namespace std;

Person::Person(string last, string first, string ID, string ad, Date D):birthDate(D) {
	setLastName(last);
	setFirstName(first);
	setIdentityNumber(ID);
	setAddress(ad);
}

void Person::setLastName(string last) {
	int len = last.length();
	len = (len < 15 ? len : 14);
	last.copy(lastName, len);
	lastName[len] = '\0';
}
string Person::getLastName() const { return lastName; }

void Person::setFirstName(string first) {
	int len = first.length();
	len = (len < 10 ? len : 9);
	first.copy(firstName, len);
	firstName[len] = '\0';
}
string Person::getFirstName() const { return firstName; }

void Person::setIdentityNumber(string ID) { 
	int len = ID.length();
	ID.copy(identityNumber, len);
	identityNumber[len] = '\0';
}
string Person::getIdentityNumber() const { return identityNumber; }

void Person::setAddress(string ad) {
	int len = ad.length();
	len = (len < 20 ? len : 19);
	ad.copy(address, len);
	address[len] = '\0';
}

string Person::getAddress() const { return address; }

// 简单展示一下信息
// 在派生类中可以重载
void Person::print() const{
	cout << "Name: " << getFirstName() << " " << getLastName()<<endl;
	cout << "Identity Number: " << getIdentityNumber()<<endl;
	cout << "Address: " << getAddress()<<endl;
	cout << "Birth Date: ";
	birthDate.print();
	cout << endl;
}