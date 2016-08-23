#ifndef __TESTER_H__
#define __TESTER_H__
#include "Shell.h"

class Tester : public Shell {
	public:
		Tester() {}
		void execute(bool &, vector<string> &);
};

#endif

