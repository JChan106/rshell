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

// executes commands using execvp
void Forker::execute(bool &last_cmd, vector<string> &cmdLine) {

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
            perror("Command not found: ");
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
