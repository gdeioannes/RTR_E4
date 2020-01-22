//============================================================================
// Name        : Pointers.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class A{
public:
	A* l;
	A* r;
	string name;
};

class B{
public:
	A a;

	void assignAValues(){
		cout << "Assign" << endl;


	}

};


int main() {
	cout << "Start" << endl;
	B b;
	b.assignAValues();
	A* a;
	a=b.a.l;
	string name=a->name;
	cout << name << endl;

	//cout << "A " << &name << endl; // prints !!!Hello World!!!
	return 0;
}
