#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "Forker.h"
#include "Shell.h"

using namespace std;

// exit
void Forker::eggsit(vector<string> line) {
    if (line[0] == "exit") {
        exit(0);
    }
}
// executes commands using execvp
void Forker::execute(bool &last_cmd, vector<string> &cmdLine) {
    // Checks if cmdLine is "exit", uses eggsit function
    eggsit(cmdLine);

	// Deletes quotation marks in cmdLine.
	char quote = '"';
	for (unsigned i = 1; i < cmdLine.size(); ++i) {
		string::iterator it = cmdLine.at(i).begin();
        string::iterator it_end = cmdLine.at(i).end();
        --it_end;

		if (*it == quote && *it_end == quote && cmdLine.at(i).size() != 1) {
			cmdLine.at(i).erase(it);
			it = --cmdLine.at(i).end();
			cmdLine.at(i).erase(it);
		}
	}

	//Changes cmdLine into a cstring array.
	vector<char*> argv;
	argv.resize(cmdLine.size() + 1);
	for (size_t i = 0; i != cmdLine.size(); ++i) {
		argv[i] = &cmdLine[i][0];
	}

	//Fork() and uses execvp(). The parent waits for the child to finish doing work.
    pid_t pid = fork();
    if (pid == -1) {
        //fork failed to execute
        perror("Could not fork: ");
        exit(1);
    }
    if (pid == 0) {
        // child process
        if (execvp(argv[0], argv.data()) == -1) {
            //failed to execute
            perror("bash; command not found: ");
            exit(1);
        }
    }
    if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);

        if (WEXITSTATUS(status) == 0) {
            last_cmd = true;
        }
        else if (WEXITSTATUS(status) == 1) {
            last_cmd = false;
        }
    }
}
