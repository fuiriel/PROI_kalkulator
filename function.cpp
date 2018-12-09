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

stack<string> shuntingYard(char *c)
{
    stack<string> operators;
    stack<string> output_;

    for(int i = 0; i < strlen(c); i++)
    {
        string s = "";
        s.clear();

        if(isdigit(c[i])){ //tworzy liczbę
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
        else if(c[i] == '!'){
            operators.push("!");
        }
        else if(op_[s+c[i]] > 0 && op_[s+c[i]] < 4) /// + - * /
        {
            s += c[i];
            while(c[i] == s[0]) i++;
            i--;
            while(!operators.empty() && operators.top() != "(" &&
                  (op_[operators.top()] == 4 || op_[operators.top()] > op_[s] || op_[operators.top()] == op_[s]))
            {
                output_.push(operators.top());
                operators.pop();
            }
            operators.push(s);
        }
        else if(c[i] == '('){
            operators.push("(");
        }
        else if(c[i] == ')')
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
    }
    while(!operators.empty())
    {
        output_.push(operators.top());
        operators.pop();
    }
    return output_;
}
