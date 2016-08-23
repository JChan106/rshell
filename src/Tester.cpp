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
#include <sys/errno.h>
#include <sys/stat.h>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include "Tester.h"
#include "Shell.h"

using namespace std;

void Tester::execute(bool &last_cmd, vector<string> &cmdLine) {
    bool check = false;
    // Checks if the test has arguments
    if (cmdLine.at(0) == "-e" || cmdLine.at(0) == "-f" || cmdLine.at(0) == "-d") {
        // Puts the file name into a character array
        string filename = cmdLine.at(1);
        char f[1024];
        strcpy(f, filename.c_str());
        
        struct stat exist;
        
        if (cmdLine.at(0) == "-e") {
            if (stat(f, &exist) == 0) {
                cout << "(True)\npath exists\n";
                check = true;
            }
            else {
                cout << "(False)\n";
            }
        }
        else if (cmdLine.at(0) == "-f") {
            if (stat(f, &exist) == 0 && S_ISREG(exist.st_mode)) {
                cout << "(True)\npath exists\n";
                check = true;
            }
            else {
                cout << "(False)\n";
            }
        }
        else {
            if (stat(f, &exist) == 0 && S_ISDIR(exist.st_mode)) {
                cout << "(True)\npath exists\n";
                check = true;
            }
            else {
                cout << "(False)\n";
            }
        }
    }
    // Error if invalid argument
    else {
        perror("Error: Invalid flag.\n");
    }
    last_cmd = check;
}

