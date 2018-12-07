#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <stack>
#include <list>
#include "classes.h"
#include "maps.h"
#include "function.h"
using namespace std;

int main() {

    char exp_[100];
    gets(exp_);


    stack<string> exps = shunting_yard(exp_);
    if(exps.top() == "@")
    {
        cout << "bledne dzialanie";
        return 0;
    }
    stack<string> exps2;
    cout << exp_ << endl;
    while(!exps.empty())
    {
        //cout << exps.top() << ' ';
        exps2.push(exps.top());
        exps.pop();
    }
   // cout << endl;
    list <string> listOfExp;
    /*while(!exps2.empty())
    {
        //cout << exps2.top() << ' ';
        listOfExp.push_back(exps2.top());
        cout <<listOfExp.back() << ' ';
        exps2.pop();
    }
    cout << endl;*/

    Expression* a;
    a = resolve(exps2);
    /*a = resolving(&listOfExp);
    if(!a)
    {
        cout << "bledne dzialanie!" << endl;
    }*/
    a -> print();
    cout << endl;
    /*map <char, Expression*> var;







    Expression* a = new AdditionExp(new Number(2), new PowerExp(new Number(2), new AdditionExp(new Number(2), new Number(1))));
    //a->eval();
    cout << "a = ";
    a->print();
    cout << endl;

    var['a'] = a;
    Expression* b = new PowerExp(a, new Number(2));

    cout << "b = ";
    b->print();
    cout << endl;
    var['b'] = b;

    a = new Number(2);
    var['a'] = a;

    //a->eval();
    cout << "a = ";
    a->print();
    cout << endl;

    //b = new PowerExp(a, new Number(2));
    //b->eval();
    cout << "b = ";
    b->print();
    cout << endl;*/
}