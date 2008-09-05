#include "Config.h"
#include "ConfigSection.h"
#include <iostream>
#include <string>

using namespace std;

void show_usage(string programname){
	cout << "Usage: " << programname << " <configfile> <section> <setting>" << endl;
}

int main(int argc, char** argv){
	if(argc != 4){
		show_usage(string(argv[0]));
		return 0;
	}
	
	Config* config = new Config(string(argv[1]));
	ConfigSection* cs = config->getSection(string(argv[2]));
	
	cout << argv[2] << " for " << argv[3] << ": " << cs->get(string(argv[3])) << endl;
	
	delete config;
	return 0;
}
