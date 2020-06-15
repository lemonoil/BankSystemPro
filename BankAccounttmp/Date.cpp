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
	// 检查birthDate的month是否合法，若不合法则提示用户在注册后及时修改
	if (month < 1 || month>12) {
		month = 1;
		cerr << "The month of the birth date is illegal. Please correct it later.\n";
		// 错误提示直接输出到屏幕上
	}
}

int Date::getMonth() const { return month; }

void Date::setDay(int d) {
	day = d;
	// 检查birthDate的day是否合法，若不合法则提示用户在注册后及时修改
	if (day < 1 || day>checkDays(getMonth())) {
		day = 1;
		cerr << "The day of the birth date is illegal. Please correct it later.\n";
		// 错误提示直接输出到屏幕上
	}
}

int Date::getDay() const { return day; }

// 输出birthDate，还在考虑如何改成文件输入（存疑）
void Date::print() const {
	cout << getYear() << "/" << getMonth() << "/" << getDay();
}

// 返回每个月应该有多少天
int Date::checkDays(int m) const {
	if (m == 2) {
		if (((m % 4 == 0) && (m % 100)) || (m % 400 == 0)) return 29;
		else return 28;
	}
	if (((m % 2) && (m <= 7)) || ((m % 2 == 0) && (m > 7))) return 31;
	return 30;
}