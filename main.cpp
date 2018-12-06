#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <stack>
#include "classes.h"
using namespace std;


stack<string> shunting_yard(char* c) {
    stack<string> operators;
    stack<string> output_;
    map<string, int> op_ =
            {
                    {"+", 1}, //L
                    {"-", 1}, //L
                    {"/", 2}, //L
                    {"*", 2}, //L
                    {"^", 3}, //R
                    {"!", 4}, //-
                    {"log", 4}, //-
                    {"ln", 4}, //-
                    {"exp", 4}, //-

            };
   // bool bracket = false; //nawiasy
    for(int i = 0; i < strlen(c); i++)
    {
        string s = "";

        if(isdigit(c[i])){

            while(isdigit(c[i]))
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
            else
            {
                output_.push("@");
                return output_;
            }
        }
        else if(c[i] == '!')
        {
            s += c[i];
            operators.push(s);
        }
        else if(op_[s+c[i]] != 4) /// ? + - * /
        {
            s += c[i];
            while((op_[operators.top()] == 4 || op_[operators.top()] > op_[s] || op_[operators.top()] == op_[s]) && operators.top() != "(")
            {
                output_.push(operators.top());
                operators.pop();
            }
            operators.push(s);
        }
        else if( c[i] == '(')
        {
            s += c[i];
            operators.push(s);
        }
        else if( c[i] == ')')
        {
            s += c[i];
            while(operators.top() != "(")
            {
                output_.push(operators.top());
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            output_.push("@");
            return output_;
        }
    }
    while(!operators.empty())
    {
        output_.push(operators.top());
        operators.pop();
    }

}
int main() {
    float c = 2.68;
    /*Number* n = new Number(c);
    n->print();
     cout << endl;*/

    char exp_[100];
    gets(exp_);
    cout << exp_;
    stack<string> exps = shunting_yard(exp_);
    if(exps.top() == "@")
    {
        cout << "bledne dzialanie";
        return 0;
    }
    while(!exps.empty())
    {
        cout << exps.top();
        exps.pop();
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