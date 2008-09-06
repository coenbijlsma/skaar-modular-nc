#include "Skaar.h"
#include <string>
#include <iostream>

int main(int argc, char** argv){
	Skaar* skaar = new Skaar();
	int i;
	cout << "Press a key to exit" << endl;
	cin >> i;
	delete skaar;
	return 0;
}
