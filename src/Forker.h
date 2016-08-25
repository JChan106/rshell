#ifndef __FORKER_H__
#define __FORKER_H__
#include "Shell.h"

class Forker : public Shell {
	protected:
		vector<string> cmd;
	public:
		Forker() {}
		Forker(vector<string> &);
		bool execute();
};

#endif
