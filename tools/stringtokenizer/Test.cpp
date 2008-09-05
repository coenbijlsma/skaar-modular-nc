#include "StringTokenizer.h"
#include <iostream>

using namespace std;

void show_usage(string programname){
	cout << "Usage: " << programname << " <params>" << endl;
}

int main(int argc, char** argv){
	StringTokenizer* st = 0;
	string s;
	
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			if(i > 1){
				s.append(" ");
			}
			s.append(argv[i]);
		}
		
		cout << "Testing string: " << s << endl;
		st = new StringTokenizer(s, ' ');
	
		while(st->hasNext()){
			cout << st->next() << endl;
		}
		
		delete st;
	}else{
		show_usage(string(argv[0]));
	}
}
