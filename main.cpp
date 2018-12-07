#include <iostream>
#include <sstream>
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
        //cout << i << ": " << s+c[i] << endl;
        if(isdigit(c[i])){

            while(isdigit(c[i])|| c[i] == '.'){
                s += c[i];
                i++;
            }
            output_.push(s);
            i--;
        }
        else if(isalpha(c[i]))
        {
            string letters = "";
            while(isalpha(c[i]))
            {
                letters += c[i];
                i++;
            }
            i--;
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
        else if(op_[s+c[i]] < 4 && op_[s+c[i]] > 0) /// + - * /
        {
            s += c[i];
            while(!operators.empty() && operators.top() != "(" && (op_[operators.top()] == 4 ||
                    op_[operators.top()] > op_[s] || op_[operators.top()] == op_[s]))
            {
                //cout << "ugh" << endl;
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
            while(operators.top() != "(" && !operators.empty())
            {
                output_.push(operators.top());
                operators.pop();
            }
            if(operators.empty())
            {
                output_.push("@");
                return output_;
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
    return output_;
}

Expression* resolve(stack<string> exp_)
{
    stringstream ss;
    float v;
    Expression* v1, *v2;
    stack <Expression*> numbers;


    while(!exp_.empty())
    {
        ss.str("");         // usuwamy wszelki tekst ze strumienia
        ss.clear();         // czyœcimy b³êdy konwersji z poprzednich wywo³añ
        ss << exp_.top();

        if(ss >> v) {
            //cout << v << ';';
            numbers.push(new Number(v));
        }
        else if(exp_.top() == "+"){

            v1 = numbers.top();
            numbers.pop();
            v2 = numbers.top();
            numbers.pop();
            numbers.push(new AdditionExp(v1,v2));
        }
        else if (exp_.top() == "-"){
            v1 = numbers.top();
            numbers.pop();
            v2 = numbers.top();
            numbers.pop();
            numbers.push(new SubtractionExp(v2,v1));
        }
        else if (exp_.top() == "/"){
            v1 = numbers.top();
            numbers.pop();
            v2 = numbers.top();
            numbers.pop();
            numbers.push(new DivisionExp(v2,v1));
        }
        else if (exp_.top() == "*"){
            v1 = numbers.top();
            numbers.pop();
            v2 = numbers.top();
            numbers.pop();
            numbers.push(new MultiplicationExp(v2,v1));
        }
        else if (exp_.top() == "^"){
            v1 = numbers.top();
            numbers.pop();
            v2 = numbers.top();
            numbers.pop();
            numbers.push(new PowerExp(v2,v1));
        }
        else if (exp_.top() == "!"){
            v1 = numbers.top();
            numbers.pop();
            numbers.push(new FactorialExp(v1));
        }
        else if (exp_.top() == "log"){
            v1 = numbers.top();
            numbers.pop();
            numbers.push(new Log10Exp(v1));
        }
        else if (exp_.top() == "ln"){
            v1 = numbers.top();
            numbers.pop();
            numbers.push(new LnExp(v1));
        }
        else if (exp_.top() == "exp"){
            v1 = numbers.top();
            numbers.pop();
            numbers.push(new ExpExp(v1));
        }
        else{
            cout << "BLAD!!";
            return nullptr;
        }
       // numbers.top()->print();
        //cout << endl;
        exp_.pop();
    }
    return numbers.top();
}

int main() {

    char exp_[100];
    gets(exp_);
    //cout << exp_ << endl;

   stack<string> exps = shunting_yard(exp_);
    if(exps.top() == "@")
    {
        cout << "bledne dzialanie";
        return 0;
    }
    stack<string> exps2;

    while(!exps.empty())
    {
        //cout << exps.top();
        exps2.push(exps.top());
        exps.pop();
    }
   // cout << endl;
   /* while(!exps2.empty())
    {
        cout << exps2.top() << ' ';
        exps2.pop();
    }*/
    Expression* a = resolve(exps2);
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