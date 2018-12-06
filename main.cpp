#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <stack>
#include "classes.h"
using namespace std;


string shunting_yard(char* c)
{
    stack <string> operators;
    stack <string> output_;
    for(int i = 0; i < strlen(c); i++)
    {
        string s = "";

        if(isdigit(c[i])){
            s += c[i];
            output_.push(s);
        }
        else if(isalpha(c[i]))
        {
            string letters = "";
            while(isalpha(c[i]))
            {
                letters += c[i];
                i++;
            }
            if(letters == "log" || letters == "ln" || letters == "exp")
            {
                operators.push(letters);
            }
            else if(letters.size() == 1)
            {
                output_.push(letters);
            }
            else return "@";
        }
        else if(c[i] == '+' || c[i] == '-' || c[i] == '/' ||c[i] == '*' ||c[i] == '(' ||c[i] == ')'
                || c[i] == '!' || c[i] == '^')
        {
            s += c[i];
            operators.push(s);
        }
        else return "@";
    }

}
int main() {
    float c = 2.68;
    /*Number* n = new Number(c);
    n->print();
     cout << endl;*/

    char* exp_ = new char[100];
    cin >> exp_;

    string exps = shunting_yard(exp_);
    if(exps == "@")
    {
        cout << "bledne dzialanie";
        return 0;
    }

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