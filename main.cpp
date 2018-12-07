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


stack<string> shunting_yard(char* c) {
    stack<string> operators;
    stack<string> output_;

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
Expression* resolving(list<string> exp_) //rekurencyjnie
{
    stringstream ss;
    float v;
    ss << exp_.back();
    list <string> v1, v2;

    if(ss >> v) {
        //cout << v << ';';
        return new Number(v);
    }
    else if(exp_.back() == "+") {
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 2)
        {
            v1.push_back(exp_.front());
            v2.push_back(exp_.back());
            return new AdditionExp(resolving(v1),resolving(v2));
        }
        while (op_[exp_.front()] > 4 || op_[exp_.front()] < 0)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }
        v1.push_back(exp_.front());
        exp_.pop_front();

        v2 = exp_;

        return new AdditionExp(resolving(v1),resolving(v2));
    }
    else if (exp_.back() == "-"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 2)
        {
            v1.push_back(exp_.front());
            v2.push_back(exp_.back());
            return new SubtractionExp(resolving(v1),resolving(v2));
        }
        while (op_[exp_.front()] > 4 || op_[exp_.front()] < 0)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }

        v1.push_back(exp_.front());
        exp_.pop_front();

        v2 = exp_;


        return new SubtractionExp(resolving(v1),resolving(v2));
    }
    else if (exp_.back() == "/"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 2)
        {
            v1.push_back(exp_.front());
            v2.push_back(exp_.back());
            return new DivisionExp(resolving(v1),resolving(v2));
        }
        while (op_[exp_.front()] > 4 || op_[exp_.front()] < 0)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }

        v1.push_back(exp_.front());
        exp_.pop_front();

        v2 = exp_;

        return new DivisionExp(resolving(v1),resolving(v2));
    }
    else if (exp_.back() == "*"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 2)
        {
            v1.push_back(exp_.front());
            v2.push_back(exp_.back());
            return new MultiplicationExp(resolving(v1),resolving(v2));
        }
        while (op_[exp_.front()] > 4 || op_[exp_.front()] < 0)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }

        v1.push_back(exp_.front());
        exp_.pop_front();

        v2 = exp_;


        return new MultiplicationExp(resolving(v1),resolving(v2));
    }
    else if (exp_.back() == "^"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 2) //2! log10 ???
        {
            v1.push_back(exp_.front());
            v2.push_back(exp_.back());
            return new PowerExp(resolving(v1), resolving(v2));
        }
        while (op_[exp_.front()] > 4 || op_[exp_.front()] < 0)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }

        v1.push_back(exp_.front());
        exp_.pop_front();

        v2 = exp_;

        return new PowerExp(resolving(v1),resolving(v2));
    }
    else if (exp_.back() == "!"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;
        if(exp_.size() == 1)
        {
            v1.push_back(exp_.front());
            return new FactorialExp(resolving(v1));
        }
        while(op_[exp_.front()] > 4 || op_[exp_.front()] < 1)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }
        v1.push_back(exp_.front());
        exp_.pop_front();

        return new FactorialExp(resolving(v1));
    }
    else if (exp_.back() == "log"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 1)
        {
            v1.push_back(exp_.front());
            return new Log10Exp(resolving(v1));
        }
        while(op_[exp_.front()] > 4 || op_[exp_.front()] < 1)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }
        v1.push_back(exp_.front());
        exp_.pop_front();

        return new Log10Exp(resolving(v1));
    }
    else if (exp_.back() == "ln"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 1)
        {
            v1.push_back(exp_.front());
            return new LnExp(resolving(v1));
        }
        while(op_[exp_.front()] > 4 || op_[exp_.front()] < 1)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }
        v1.push_back(exp_.front());
        exp_.pop_front();

        return new LnExp(resolving(v1));
    }
    else if (exp_.back() == "exp"){
        exp_.pop_back();
        if(exp_.empty()) return nullptr;

        if(exp_.size() == 1)
        {
            v1.push_back(exp_.front());
            return new ExpExp(resolving(v1));
        }
        while(op_[exp_.front()] > 4 || op_[exp_.front()] < 1)
        {
            v1.push_back(exp_.front());
            exp_.pop_front();
        }
        v1.push_back(exp_.front());
        exp_.pop_front();

        return new ExpExp(resolving(v1));
    }
    else{
        cout << "BLAD!!";
        return nullptr;
    }


}
Expression* resolve(stack<string> exp_) //nierekurencyjnie
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
        // numbers.top().print();
        //cout << endl;
        exp_.pop();
    }
    return numbers.top();
}

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

    while(!exps.empty())
    {
        //cout << exps.top() << ' ';
        exps2.push(exps.top());
        exps.pop();
    }
   // cout << endl;
    list <string> listOfExp;
    while(!exps.empty())
    {
        listOfExp.push_front(exps.top());
        exps.pop();
    }
    cout << endl;
    //cout << listOfExp.size() << endl;
    Expression* a;
    a = resolve(exps2);
    //a = resolving(listOfExp);
   /* if(!a)
    {
        cout << "bledne dzialanie!" << endl;
    }*/
    a->print();
    cout << endl;
    /*map <char, Expression*> var;







    Expression* a = new AdditionExp(new Number(2), new PowerExp(new Number(2), new AdditionExp(new Number(2), new Number(1))));
    //a.eval();
    cout << "a = ";
    a.print();
    cout << endl;

    var['a'] = a;
    Expression* b = new PowerExp(a, new Number(2));

    cout << "b = ";
    b.print();
    cout << endl;
    var['b'] = b;

    a = new Number(2);
    var['a'] = a;

    //a.eval();
    cout << "a = ";
    a.print();
    cout << endl;

    //b = new PowerExp(a, new Number(2));
    //b.eval();
    cout << "b = ";
    b.print();
    cout << endl;*/
}