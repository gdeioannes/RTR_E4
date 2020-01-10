//============================================================================
// Name        : exercise412.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


class boundingbox{
public :

	void print(string text){
		cout << text << endl;
	}

private:
	void print2(string text){
			cout << text << endl;
	}

};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	boundingbox bx;
	bx.print("Hola");
	return 0;
}

