#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include "Parse.h"
#include "Forker.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>

using namespace std;

// pop_front for vector
void Parse::pop_front(vector<string> &v) {
    assert(!v.empty());
    v.erase(v.begin());
}

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
        for(unsigned i = 0; i < cmds_vector.size();) {
            if (cmds_vector.at(i) != a && 
                cmds_vector.at(i) != o && 
                cmds_vector.at(i) != s) {
                    exec_cmds_vector.push_back(cmds_vector.at(i));
                    pop_front(cmds_vector);
            }
            // breaks so that the for loop doesn't keep running through the connectors. 
            else {
                break;
            }
        }
        // execute command
        if (!exec_cmds_vector.empty()) {
            shell = new Forker();
            shell->execute(previous, exec_cmds_vector); 
            exec_cmds_vector.clear();
        }
        else {
            break;
        }

        if(!cmds_vector.empty()) {
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
            // else break
            else {
                break;
            }
        }
    }
}
