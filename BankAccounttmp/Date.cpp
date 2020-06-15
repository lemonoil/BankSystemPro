#include"Date.h"
#include<iostream>
using namespace std;

Date::Date(int y, int m, int d):year(y) {
	setMonth(m);
	setDay(d);
}

void Date::setYear(int y) { year = y; }

int Date::getYear() const { return year; }

void Date::setMonth(int m) {
	month = m;
	// ���birthDate��month�Ƿ�Ϸ��������Ϸ�����ʾ�û���ע���ʱ�޸�
	if (month < 1 || month>12) {
		month = 1;
		cerr << "The month of the birth date is illegal. Please correct it later.\n";
		// ������ʾֱ���������Ļ��
	}
}

int Date::getMonth() const { return month; }

void Date::setDay(int d) {
	day = d;
	// ���birthDate��day�Ƿ�Ϸ��������Ϸ�����ʾ�û���ע���ʱ�޸�
	if (day < 1 || day>checkDays(getMonth())) {
		day = 1;
		cerr << "The day of the birth date is illegal. Please correct it later.\n";
		// ������ʾֱ���������Ļ��
	}
}

int Date::getDay() const { return day; }

// ���birthDate�����ڿ�����θĳ��ļ����루���ɣ�
void Date::print() const {
	cout << getYear() << "/" << getMonth() << "/" << getDay();
}

// ����ÿ����Ӧ���ж�����
int Date::checkDays(int m) const {
	if (m == 2) {
		if (((m % 4 == 0) && (m % 100)) || (m % 400 == 0)) return 29;
		else return 28;
	}
	if (((m % 2) && (m <= 7)) || ((m % 2 == 0) && (m > 7))) return 31;
	return 30;
}