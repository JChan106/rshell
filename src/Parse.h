#ifndef __PARSE_H__
#define __PARSE_H__
#include <iostream>
#include <string>
#include "Shell.h"
#include "ConnectBase.h"

using namespace std;

class Parse {

    private:
        Shell* shell;
        //ConnectBase* connectbase;
        void pop_front(vector<string>&);

    public:
        Parse() {}
        void par(string);
};

#endif 
