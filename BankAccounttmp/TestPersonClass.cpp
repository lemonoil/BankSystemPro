#include"Person.h"
#include<iostream>
using namespace std;

int main()
{
	// last,first,ID,ad,D
	Person Man("A", "B", "1234567890", "Green Street", Date(2000, 1, 1));
	Man.print();
	return 0;
}