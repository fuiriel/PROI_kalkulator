#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include "classes.h"
using namespace std;

int main() {
    float c = 2.68;
    /*Number* n = new Number(c);
    n->print();
     cout << endl;*/


    map <char, Expression*> var;

    Expression* a = new AdditionExp(new Number(2), new PowerExp(new Number(2), new AdditionExp(new Number(2), new Number(1))));
    //a->eval();
    cout << "a = ";
    a->print();
    cout << endl;

    var['a'] = a;

    Expression* b = new PowerExp(var['a'], new Number(2));
   // b->eval();
    cout << "b = ";
    b->print();
    cout << endl;

    a = new Number(2);
    //a->eval();
    cout << "a = ";
    a->print();
    cout << endl;

    //b = new PowerExp(a, new Number(2));
    //b->eval();
    cout << "b = ";
    b->print();
    cout << endl;
}