#ifndef __SHELL_H__
#define __SHELL_H__
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// Base Class
class Shell {
	public:
		Shell() {}
		virtual void execute(bool &, vector<string> &) = 0;
};

#endif
