#ifndef __CONNECTBASE_H__
#define __CONNECTBASE_H__
#include "Forker.h"

// Abstract Base Class
class ConnectBase {
	protected:
		Shell* shell;
	public:
		ConnectBase() {}
		virtual void execute(bool &, vector<string> &) = 0;
};

// Inherent from ConnectBase
class Or : public ConnectBase {
	public:
		Or() : ConnectBase() {}
		void execute(bool &, vector<string> &);
};

class And : public ConnectBase {
	public:
		And() : ConnectBase() {}
		void execute(bool &, vector<string> &);
};

class Semi : public ConnectBase {
	public:
		Semi() :ConnectBase() {}
		void execute(bool &, vector<string> &);
};

#endif
