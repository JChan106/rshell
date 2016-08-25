#ifndef __PARSE_H__
#define __PARSE_H__
#include <iostream>
#include <string>
#include <stack>
#include "Shell.h"
#include "Connector.h"

using namespace std;

class Parse {

    private:
        // Shell* shell;
        void pop_front(vector<string>&);
        void pop_front(vector<Shell*>&);
        
        bool bracket_finder(vector<string>, unsigned); 
        // void bracket_deleter(vector<string> &);
        void createTester(vector<string> &,unsigned, unsigned);
        // void checkFlag(vector<string> &);
        void createTree(stack<Connector*> &);
        void createFork(vector<string> &,unsigned, unsigned);
    
    protected:
        vector<Shell*> exec_cmds_vector;
    public:
        Parse() {}
        void par(string);
        
};

#endif 

