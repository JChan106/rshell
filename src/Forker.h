#ifndef __FORKER_H__
#define __FORKER_H__
#include "Shell.h"

class Forker : public Shell {
	public:
		Forker() {}
		void execute(bool &, vector<string> &);
};

#endif
