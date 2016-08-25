#include "Connector.h"


void Connector::errorCheck() {
    //if right == NULL, error
    // try{
    //     if (!left) {
    //         throw logic_error("No left child");
    //     }
    //     else if (!right) {
    //         throw logic_error("No right child");
    //     }
    // }
    // catch(logic_error& e) {
    //     cout << e.what() << endl;
    //     exit(1);
    // }
    if (!left) {
        cout << "No left child" << endl;
        exit(1);
    }
    else if (!right) {
         cout << "No right child" << endl;
        exit(1);
    }
}

void Connector::setLeftChild(Shell* l) {
    left = l;
}
void Connector::setRightChild(Shell * r) {
    right = r;
}

bool And::execute() {
    errorCheck();
    return (left->execute() && right->execute());
}

bool Or::execute() {
    errorCheck();
    return (left->execute() || right->execute());
}

bool SemiColon::execute() {
    bool temp = left->execute(); //dummy variable
    temp = right->execute(); //use temp to avoid error from compiler
                            //for not using variable
    return temp;
}

bool Parenthesis::execute() {
    return true;
}