//============================================================================
// Name        : PointersTutorials.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Test{
private:
	void print(){
		cout << "hello" << endl;
	}
};

int main() {

	Test test;
	test.print();
	int numbers[1];
	int * pointer;

	//pointer = numbers;
	cout << pointer << endl;

	//*pointer = 10;

	cout << sizeof(numbers) << endl;

	for(int i=0;i<sizeof(numbers);i++){
		cout << i << " ";
	}
	cout << endl;
	return 0;
}
