#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cstring> 
#include <sstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include "Shell.h"
#include "Forker.h"
#include "Parse.h"

using namespace std;

int main() {
	Parse* p = new Parse();
	string line;	
	string arg = "";
	while(true) {
		char user[1024];
		//Gets username, outputs an error if it is unable to
		if (getlogin_r(user, sizeof(user) - 1) != 0) {
			cout << "Unable to retrieve username" << endl;
		}
		cout << user << "@";
		char host[1024];
		// Gets hostname, outputs an error if it is unable to
		if (gethostname(host, sizeof(host) - 1) != 0) {
			cout << "Unable to retrieve hostname" << endl;
		}
		cout << host << "$ "; 
		//Gets a command
		getline(cin, line);  
		// parses and runs code
		p->par(line); 
	}
	return 0;
}
