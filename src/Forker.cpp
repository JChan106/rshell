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

Forker::Forker(vector<string> &cmdLine) {
    id = "cmd";
    cmd = cmdLine;
}
// executes commands using execvp
bool Forker::execute() {

	//Changes cmdLine into a cstring array.
	vector<char*> argv;
	argv.resize(cmd.size() + 1);
	for (size_t i = 0; i != cmd.size(); ++i) {
		argv[i] = &cmd[i][0];
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
            return true;
        }
        else if (WEXITSTATUS(status) == 1) {
            return false;
        }
    }
    return true;
}
