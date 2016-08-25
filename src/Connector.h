#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Shell.h"
#include <stdlib.h> //exit()

class Connector : public Shell {
	protected:
	    Shell* left;
	    Shell* right;
	public:
		Connector() : left(NULL), right(NULL) { id = "conn"; } 
		//error checking function
		void errorCheck();
		//modifier function
		void setLeftChild(Shell* l);
		void setRightChild(Shell* r);
		//access function
		virtual bool execute() = 0;
};

class And : public Connector {
    public:
        And() {}
        bool execute();
};

class Or : public Connector {
    public:
        Or() {}
        bool execute();
};

class SemiColon : public Connector {
    public:
        SemiColon() {}
        bool execute();
};

class Parenthesis : public Connector {
	public:
		Parenthesis() { id = "("; }
		bool execute();
};
#endif
