#include "ConnectBase.h"
#include "Forker.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

void Or::execute(bool &last_cmd, vector<string> &cmdLine) {
    // If last_cmd is true, then command doesn't run. If last_cmd is false, then a command runs.
	if (last_cmd) {
	    return;
	}
	else {
		this->shell = new Forker();
		this->shell->execute(last_cmd, cmdLine);
	}
}

void And::execute(bool &last_cmd, vector<string> &cmdLine) {
	// The command doesn't run if last_cmd is false, runs a command as shown in cmdLine
	if (!last_cmd) {
		last_cmd = false;
	}
	else {
		this->shell = new Forker();
		this->shell->execute(last_cmd, cmdLine);
	}
}

void Semi::execute(bool &last_cmd, vector<string> &cmdLine) {
    // Runs a command.
	this->shell = new Forker();
	this->shell->execute(last_cmd, cmdLine);
	
}
