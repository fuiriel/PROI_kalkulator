#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <stack>
#include <list>
#include "classes.h"
#include "maps.h"
//#include "function.h"
using namespace std;

/*10*(2+2^2-10) rek = -80 nierek = -40*/
/*10*(2+2^2-10)*log100+50 nierek ok, ale gdy spacja to "bledne dzialanie"*/

stack<string> shunting_yard(char* c) {
    stack<string> operators;
    stack<string> output_;

    for(int i = 0; i < strlen(c); i++)
    {
        string s = "";
        s.clear();

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
                operators.push(letters);
            else if(letters.size() == 1)
                output_.push(letters);
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
            while(!operators.empty() && operators.top() != "(" &&
                    (op_[operators.top()] == 4 || op_[operators.top()] > op_[s] || op_[operators.top()] == op_[s]))
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

Expression* resolve(stack<string> exp_) //nierekurencyjnie
{
    stringstream ss;
    float v;
    Expression* v1, *v2;
    stack <Expression*> numbers;

    while(!exp_.empty())
    {
        ss.str("");         // usuwanie tekstu ze strumienia
        ss.clear();         // czyszcenie bledow konwersji
        ss << exp_.top();

        if(ss >> v) {
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
        exp_.pop();
    }
    return numbers.top();
}

int main() {
    cout << "KALKULATOR ZMIENNYCH\nAby zakonczyc wpisz #\n";
    char exp_[100];

    while(true) {
        gets(exp_);
        if (exp_[0] == '#') return 0;
        if(exp_[0] == '=')
        {
            if(!var.empty())
            {
                for(auto elem: var)
                {
                    cout << elem.first <<  " = ";
                    elem.second->print();
                }
            } else
            {
                cout << "brak dzialan do wykonania" << endl;
            }
            continue;
        }

        stack<string> exps = shunting_yard(exp_);
        if (exps.top() == "@") {
            cout << "bledne dzialanie" << endl;
            continue;
        }

        stack<string> exps2; // przepisuje odrwotnie
        while (!exps.empty()) {
            exps2.push(exps.top());
            exps.pop();
        }

        ExpressionContainer *exp;
        exp->setExpression(resolve(exps2));
        /*ExpressionContainer* a = new ExpressionContainer(new Number(3));
        ExpressionContainer* b = new ExpressionContainer(new MultiplicationExp(a, new Number(2)));
        b->print();
        a->setExpression(new Number(100));
        b->print();*/
        //a = resolving(listOfExp);
        if (!exp->eval()) { // wymyśl coś by nie liczyło dwa razy
            cout << "bledne dzialanie!" << endl;
        }
        exp->print();
        // cout << endl;

    }
}