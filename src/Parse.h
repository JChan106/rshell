#ifndef __PARSE_H__
#define __PARSE_H__
#include <iostream>
#include <string>
#include "Shell.h"

using namespace std;

class Parse {

    private:
        Shell* shell;
        void pop_front(vector<string>&);
        bool bracket_finder(vector<string>); 
        void bracket_deleter(vector<string> &);
        void checkFlag(vector<string> &);

    public:
        Parse() {}
        void par(string);
        
};

#endif 
