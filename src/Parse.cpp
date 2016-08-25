#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
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
void Parse::pop_front(vector<Shell*> &v) {
    assert(!v.empty());
    v.erase(v.begin());
}

//returns true if both '[' and ']' are found 
bool Parse::bracket_finder(vector<string> str_vector, unsigned i) {
    if (str_vector.at(i) == "[") {
        for (unsigned j = i + 2; j < str_vector.size(); ++j) {
            if (str_vector.at(j) == "]") {
                return true;
            }
        }
        perror("Error: Cannot find ']'\n" );
    }
    return false;
}


void Parse::createTester(vector<string> &cmds_vector,unsigned i, unsigned j) {
    vector<string> cmd;
    for (unsigned k = i; k < j; ++k) {
        cmd.push_back(cmds_vector.at(k));
    }
    exec_cmds_vector.push_back(new Tester(cmd));
}
// //deletes brackets 
// void Parse::bracket_deleter(vector<string> &str_vector) {
//     pop_front(str_vector);
//     str_vector.pop_back();
// }

void Parse::createTree(stack<Connector*> &cmd_stack) {
    if (!cmd_stack.empty() && (cmd_stack.top()->getID() == "conn")) {
        //setRightChild
        cmd_stack.top()->setRightChild(exec_cmds_vector.back());
        exec_cmds_vector.pop_back();
        //setLeftChild
        cmd_stack.top()->setLeftChild(exec_cmds_vector.back());
        exec_cmds_vector.pop_back();
        //pop from stack & push onto exec_cmds_vector
        exec_cmds_vector.push_back(cmd_stack.top());
        cmd_stack.pop();
    }
}

void Parse::createFork(vector<string> &cmds_vector, unsigned i, unsigned j) {
    vector<string> cmd;
    for (unsigned k = i; k < j; ++k) {
        if (cmds_vector.at(k) != "\"") {
            cmd.push_back(cmds_vector.at(k));
        }
    }
    exec_cmds_vector.push_back(new Forker(cmd));
}


void Parse::par(string in) {
    const string a = "&&";
    const string o = "||";
    const string s = ";";
    const string lp = "(";
    const string rp = ")";
    
    //allow for parsing open/close parenthesis using strtok()
    bool validP = true;
    for (unsigned i = 0; i < in.size(); ++i) {
        //checks to see if quotes exist. If exist, will ignore parenthesis
        //within the quotes 
        //Note: won't take care of special characters
        if (in.at(i) == '\"') {
            validP = !validP; //toggle validP
            in.erase(in.begin() + i); //delete the quote
        }
        
        if (validP) {
           if (i < in.size()) {
                if (in.at(i) == '(') { //if open paren, insert space after
                    in.insert(i + 1, " ");
                }
                else if (in.at(i) == ')') { //if close paren, insert space before
                    in.insert(i, " ");
                    ++i;
                }
                else if (in.at(i) == ';') {
                    in.insert(i, " ");
                    ++i;
                }
           }
        }
    }
    
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
    while (ptr != NULL) {
        cmds_vector.push_back(ptr);
        ptr = strtok(NULL, " ");
    }
    // push elements from cmds_vector to exec_cmds_vector until hitting a connector
    // then execute everything before connector and clear
    // check for connector and execute next command depending on connector and if the last command pass/failed
    
    
    stack<Connector*> cmd_stack; 
    
    // comment case
    for (unsigned j = 0; j < cmds_vector.size(); ++j) {
        if ((cmds_vector.at(j))[0] == '#') {
            cmds_vector.resize(j);
            break;
        }
    }
    
    if (cmds_vector.at(0) == "exit") {
        exit(0);
    }
    
    unsigned i;
    for (i = 0; i < cmds_vector.size();++i) {
        // Transferring Commands
        string indexString = cmds_vector.at(i);
        
        
        //connectors & commands
        if (cmds_vector.at(i) == a) {
            //check to see if exist a conn
            createTree(cmd_stack);
            //push new operator onto stack
            cmd_stack.push(new And());
        }
        else if (cmds_vector.at(i) == o) {
            //check to see if exist a conn
            createTree(cmd_stack);
            //push new operator onto stack
            cmd_stack.push(new Or());
        }
        else if (cmds_vector.at(i) == s) {
            //check to see if exist a conn
            createTree(cmd_stack);
            //push new operator onto stack
            cmd_stack.push(new SemiColon());
        }
        else if (cmds_vector.at(i) == rp) {
            //keep create trees until find open parenthesis
            while (cmd_stack.top()->getID() != lp) {
                createTree(cmd_stack);
            }
            //pop the open parenthesis from cmd_stack
            cmd_stack.pop();
        }
        else if (cmds_vector.at(i) == lp) {
            cmd_stack.push(new Parenthesis());
        }
        else if (cmds_vector.at(i) == "test" || 
                bracket_finder(cmds_vector, i)) {
                    // // Delete the word test
                    // if (cmds_vector.at(i) == "test") {
                    //     pop_front(exec_cmds_vector);//-----TODO
                    // }
                    // // Deletes square brackets
                    // else {
                    //     bracket_deleter(cmds_vector,i);//-----TODO
                    // }
                    // Breaks if no arguments after test
                    if ((i + 1) == cmds_vector.size()) {
                        break;
                    }
                    // checkFlag(exec_cmds_vector);
                    if (cmds_vector.at(i) == "test") {
                        
                        unsigned size = cmds_vector.size();
                        
                        if ((i + 1) == size ||
                            cmds_vector.at(i) == a ||
                            cmds_vector.at(i) == o ||
                            cmds_vector.at(i) == s ||
                            cmds_vector.at(i) == lp) {
                                perror("No statement after test\n");
                            }
                        if ((i + 2) == size ||
                            (i + 3) == size) {
                                createTester(cmds_vector, i + 1, size);
                                if ((i + 2) == size) {
                                    ++i;
                                }
                                else {
                                    i += 2;
                                }
                        }
                        else if (cmds_vector.at(i + 2) == a || 
                            cmds_vector.at(i + 2) == o ||
                            cmds_vector.at(i + 2) == s ) {
                                //create Tester() with default flag
                                createTester(cmds_vector, i + 1, i + 2);
                                ++i; //to push conn
                        }
                        else if (cmds_vector.at(i + 3) == a || 
                                cmds_vector.at(i + 3) == o ||
                                cmds_vector.at(i + 3) == s ) {
                                    //create Tester with flag
                                    createTester(cmds_vector, i + 1, i + 3);
                                    i += 2; //to push conn
                                }
                    }
                    else if (cmds_vector.at(i) == "[") {
                        if (cmds_vector.at(i + 2) == "]") {
                            //create Tester() with default flag
                            createTester(cmds_vector, i + 1, i + 2);
                            i += 2; //skip  "]"
                        }
                        else if (cmds_vector.at(i + 3) == "]") {
                            //create Tester with flag
                            createTester(cmds_vector, i + 1, i + 3);
                            i += 3; //skip "]"
                        }
                        else {
                            perror("Invalid #of statements or no ']' found\n");
                        }
                    }
        }
        else {//is part of the bash cmds
            //iterate until find a conn
            unsigned j;
            for (j = i; j < cmds_vector.size(); ++j) {
                //if conn found
                if (cmds_vector.at(j) == a || 
                    cmds_vector.at(j) == o ||
                    cmds_vector.at(j) == s ||
                    cmds_vector.at(j) == rp) {
                        //store strings into new Fork
                        createFork(cmds_vector, i, j);
                        i = j - 1; //need to add the conn
                        break;
                }
            }
            //if no conn found, means end of cmd_vector
            if (j >=  cmds_vector.size()) {
                //create new Fork
                createFork(cmds_vector, i, j);
                break;
            }
        }
    }
    
    while (!cmd_stack.empty()) {
        createTree(cmd_stack);
    }
    
    if (!exec_cmds_vector.empty() && exec_cmds_vector.at(0)->execute()) {
        exec_cmds_vector.clear();
    }
}

