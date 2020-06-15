#ifndef PERSON_H
#define PERSON_H
#include<string>
#include"Date.h"
using std::string;
class Person {
public:
	Person(string,string,string,string,Date);
	~Person() {}
	void setLastName(string);
	string getLastName() const;
	void setFirstName(string);
	string getFirstName() const;
	void setIdentityNumber(string);
	string getIdentityNumber() const;
	void setAddress(string);
	string getAddress() const;
	void print() const;
private:
	char lastName[15];
	char firstName[10];
	char identityNumber[20];
	char address[20];
	Date birthDate;
};

#endif

