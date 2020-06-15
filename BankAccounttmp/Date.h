#ifndef DATE_H
#define DATE_H

class Date {
public:
	Date(int =2020,int =1,int =1);
	~Date() {}
	void setYear(int);
	int getYear() const;
	void setMonth(int);
	int getMonth() const;
	void setDay(int);
	int getDay() const;
	void print() const;
private:
	int year;
	int month;
	int day;
	int checkDays(int) const;
};

#endif
