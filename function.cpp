#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include "classes.h"
#include <cmath>
#include "function.h"
using namespace std;

std::map<std::string, int> op_ =
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
const char* noSpace(char *c)
{
    string newC = "";
    for(int i = 0; i < strlen(c); i++)
        if(c[i] != ' ') newC += c[i];
    return newC.c_str();
}
queue<string> shuntingYard(char *exp)
{
    stack<string> operators;
    queue<string> output_;

    char *c =  new char[100];
    strcpy(c, noSpace(exp));

    for(int i = 0; i < strlen(c); i++)
    {
        string s = "";
        s.clear();
        string c_next = "";

        if(i != strlen(c)-1) c_next += c[i+1];
        if(isdigit(c[i]) && (i == strlen(c)-1 || (!isalpha(c[i+1]) && c[i+1] != '('))){ //tworzy liczbę

            while(isdigit(c[i]) || c[i] == '.'){
                s += c[i];
                i++;
            }
            output_.push(s);
            i--;
        }
        else if(isalpha(c[i]))
        {
            string letters = "";
            while(isalpha(c[i])){
                letters += c[i];
                i++;
                if(letters == "log" || letters == "ln" || letters == "exp") break;
            }
            i--;
            if(letters == "log" || letters == "ln" || letters == "exp")
                operators.push(letters);
            else if(letters.size() == 1)
                output_.push(letters);
            else
            {
                output_.push("@"); //blad
                return output_;
            }
        }
        else if(c[i] == '-' && (i == 0 || c[i-1] == '('))
        {
            output_.push("0");
            operators.push("-");
        }
        else if(c[i] == '!' && i != 0 && (i == strlen(c)-1 || c[i+1] == '!' || c[i+1] == ')'
                                          || (!c_next.empty() && op_[c_next] > 0 && op_[c_next] < 4))) {
            operators.push("!");
        }
        else if(op_[s+c[i]] > 0 && op_[s+c[i]] < 4 && i != 0 && i != strlen(c)-1 && (isalnum(c[i+1]) || c[i+1] == '(')) // + - * / ^
        {
            s+=c[i];
            while(!operators.empty() && operators.top() != "(" &&
                  (op_[operators.top()] == 4 || op_[operators.top()] > op_[s] || op_[operators.top()] == op_[s]))
            {
                output_.push(operators.top());
                operators.pop();
            }
            operators.push(s);
        }
        else if(c[i] == '(' && i != strlen(c)-1 && (isalnum(c[i+1]) || c[i+1] == '-')){ //czy gdy i = 0?
            operators.push("(");
        }
        else if(c[i] == ')' && i != 0 && (i == strlen(c)-1 || c[i+1] == '!'
                                          || (!c_next.empty() && op_[c_next] > 0 && op_[c_next] < 4)))
        {
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
Expression* resolve(queue<string> exp_, map<char, ExpressionContainer*> var)
{
    stringstream ss;
    float v;
    Expression* v1, *v2;
    stack <Expression*> numbers;

    while(!exp_.empty())
    {
        ss.str("");         // usuwanie tekstu ze strumienia
        ss.clear();         // czyszcenie bledow konwersji
        ss << exp_.front();

        if(ss >> v) {
            numbers.push(new Number(v));
        }
        else  if(exp_.front() == "!" && numbers.top()->eval()-floor(numbers.top()->eval()) == 0)
        {
            v1 = numbers.top();
            numbers.pop();
            numbers.push(new FactorialExp(v1));
        }
        else if(op_[exp_.front()] == 4 && exp_.front() != "!") //log ln exp
        {
            v1 = numbers.top();
            numbers.pop();

            if(exp_.front() == "log")
                numbers.push(new Log10Exp(v1));
            else if(exp_.front() == "ln")
                numbers.push(new LnExp(v1));
            else if(exp_.front() == "exp")
                numbers.push(new ExpExp(v1));
        }
        else if(isalpha(exp_.front()[0])){
            numbers.push(var[exp_.front()[0]]);
        }
        else if(op_[exp_.front()] > 0 && op_[exp_.front()] < 4) // + - / * ^
        {
            v1 = numbers.top();
            numbers.pop();
            v2 = numbers.top();
            numbers.pop();
            if(exp_.front() == "+")
                numbers.push(new AdditionExp(v2,v1));
            else if(exp_.front() == "-")
                numbers.push(new SubtractionExp(v2,v1));
            else if(exp_.front() == "/")
                numbers.push(new DivisionExp(v2,v1));
            else if(exp_.front() == "*")
                numbers.push(new MultiplicationExp(v2,v1));
            else if(exp_.front() == "^")
                numbers.push(new PowerExp(v2,v1));
        }
        else{
            return nullptr;
        }
        exp_.pop();
    }
    return numbers.top();
}
