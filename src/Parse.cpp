#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include "Parse.h"
#include "Forker.h"
#include "Tester.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <cstdio>

using namespace std;

// pop_front for vector
void Parse::pop_front(vector<string> &v) {
    assert(!v.empty());
    v.erase(v.begin());
}

//returns true if both '[' and ']' are found 
bool Parse::bracket_finder(vector<string> str_vector) {
    if (str_vector.at(0) == "[") {
        if (str_vector.at(str_vector.size() - 1) == "]") {
            return true;
        }
        else {
            perror("Error: Cannot find ']'\n" );
        }
    }
    return false;
}

//deletes brackets 
void Parse::bracket_deleter(vector<string> &str_vector) {
    pop_front(str_vector);
    str_vector.pop_back();
}

// void Parse::checkFlag(vector<string> &v) {
//     //check exist
//     //3rd argument means that first char in string is not a flag; no flag, nor invalid flag specified, check exist
//     if (v.at(0) == "-e" || v.at(0) == "-" || (v.at(0)).at(0) != '-') {
//         //poppin bottles so v.at(0) == filename
//         if(v.at(0) == "-e" || v.at(0) == "-") { 
//             pop_front(v); 
//         }
//         //convert v.at(0) to charray for stat()
//         string str = v.at(0);
//         char f[1024];
//         strcpy(f, str.c_str());  
        
//         //return True if exist
//         struct stat exist;
//         if (stat(f, &exist) == 0) {
//             cout << "True\n";
//         }
//         else {
//             cout << "False\n";
//         }
//     }
//     //check file
//     else if(v.at(0) == "-f") {
//         pop_front(v);
        
//         string str = v.at(0);
//         char f[1024];
//         strcpy(f, str.c_str());  
        
//         struct stat file; 
        
//         if (stat(f, &file) == 0 && S_ISREG(file.st_mode)) {
//             cout << "(True)\nPath Exists\n";
//         }
//         else {
//             cout << "(False)\n";
//         }
//     }
//     //check directory
//     else if(v.at(0) == "-d") {
//         pop_front(v);
        
//         string str = v.at(0);
//         char f[1024];
//         strcpy(f, str.c_str());  
        
//         struct stat file; 
//         //stat(f, &file);
//         //TODO: once false, could be true or false, once true, everything else will be true, 
//         if (stat(f, &file) == 0 && S_ISDIR(file.st_mode)) {
//             cout << "True\n";
//         }
//         else {
//             cout << "False\n";
//         }
//         return;
//     }
//     //else invalid flag
//     else {
//         perror("Error: Invalid flag.\n");
//     }
// } 

void Parse::par(string in) {
    const string a = "&&";
    const string o = "||";
    const string s = ";";
    bool previous = true;
    
    // remove quotations in the string for the echo command
    in.erase(remove( in.begin(), in.end(), '\"'), in.end());
    
    // parse command line and store in cmds_vector 
    char cmds[1024];
    char *ptr;
    // converts cmds from strings to chars
    //vector<string< p_vector;
    vector<string> cmds_vector;
    strcpy(cmds, in.c_str());
    // parse white space
    ptr = strtok(cmds, " "); 
    // store parsed commands into cmds_vector
    while(ptr != NULL) {
        cmds_vector.push_back(ptr);
        ptr = strtok(NULL, " ");
    }
    // push elements from cmds_vector to exec_cmds_vector until hitting a connector
    // then execute everything before connector and clear
    // check for connector and execute next command depending on connector and if the last command pass/failed
    while(!cmds_vector.empty()) {
        // comment case
        if ((cmds_vector.at(0))[0] == '#') {
            cmds_vector.clear();
            break;
        }
        // vector of commands which will be executed
        vector<string> exec_cmds_vector;
        for (unsigned i = 0; i < cmds_vector.size();) {
            // Transferring Commands
            if (cmds_vector.at(i) != a && 
                cmds_vector.at(i) != o &&
                cmds_vector.at(i) != s) {
                    exec_cmds_vector.push_back(cmds_vector.at(i));
                    pop_front(cmds_vector);
            }
            // Stops transferring to exec_cmds_vector if connector is hit
            else {
                break;
            }
        }
        // execute command
        if (!exec_cmds_vector.empty()) {
            // Exits if user types in exit
            if (exec_cmds_vector.at(0) == "exit") {
                exit(0);
            }
            else if (exec_cmds_vector.at(0) == "test" || bracket_finder(exec_cmds_vector)) {
                // Delete the word test
                if (exec_cmds_vector.at(0) == "test") {
                    pop_front(exec_cmds_vector);
                }
                // Deletes square brackets
                else {
                    bracket_deleter(exec_cmds_vector);
                }
                // Breaks if no arguments after test
                if (exec_cmds_vector.empty()) {
                    break;
                }
                // checkFlag(exec_cmds_vector);
                
                // Using test command
                shell = new Tester();
                shell->execute(previous, exec_cmds_vector);
            }
            else {
                // Using execvp
                shell = new Forker();
                shell->execute(previous, exec_cmds_vector);
            }
            exec_cmds_vector.clear();
        }
        // Nothing happens if no commands
        else {
            break;
        }
        
        if (!cmds_vector.empty()) {
            // && case
            if (cmds_vector.at(0) == a && previous == true) {
                pop_front(cmds_vector);
            } 
            // || case
            else if (cmds_vector.at(0) == o && previous == false) {
                pop_front(cmds_vector);
            }
            // ; case
            else if (cmds_vector.at(0) == s) {
                pop_front(cmds_vector);
            }
            else {
                break;
            }
        }
    }
}
