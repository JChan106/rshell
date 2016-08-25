#ifndef __TESTER_H__
#define __TESTER_H__
#include "Forker.h"

class Tester : public Forker {
	public:
		Tester() {}
		Tester(vector<string> &v) : Forker(v) {
			id = "test";
		}
		bool execute();
};

#endif
