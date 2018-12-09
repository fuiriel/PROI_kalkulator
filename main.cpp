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

/*Do poprawki:
 * b = b*2
 *
 Do rozpatrzenia bledy:
 *poprawne wystepowanie po sobie znakow
*/

stack<string> shuntingYard(char *c)
{
    stack<string> operators;
    stack<string> output_;

    for(int i = 0; i < strlen(c); i++)
    {
        string s = "";
        s.clear();
        string c_next = "";
        if(i != strlen(c)-1) c_next += c[i+1];

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
        else if(c[i] == '!' && i != 0 && (i == strlen(c)-1 || c[i+1] == '!' || c[i+1] == ')'
                                          || (!c_next.empty() && op_[c_next] > 0 && op_[c_next] < 4))) {
            operators.push("!");
        }
        else if(op_[s+c[i]] > 0 && op_[s+c[i]] < 4 && i != 0 && (isalnum(c[i+1])|| c[i] == '(')) // + - * / ^
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
        else if(c[i] == '(' && i != strlen(c)-1 && isalnum(c[i+1])){ //czy gdy i = 0?
            operators.push("(");
        }
        else if(c[i] == ')' && i != 0 && (i == strlen(c)-1 || c[i+1] == '!' || (!c_next.empty() && op_[c_next] > 0 && op_[c_next] < 4)))
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

Expression* resolve(stack<string> exp_)
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
        else if(op_[exp_.top()] == 4) // ! log ln exp
        {
            v1 = numbers.top();
            numbers.pop();
            if(exp_.top() == "!")
                numbers.push(new FactorialExp(v1));
            else if(exp_.top() == "log")
                numbers.push(new Log10Exp(v1));
            else if(exp_.top() == "ln")
                numbers.push(new LnExp(v1));
            else if(exp_.top() == "exp")
                numbers.push(new ExpExp(v1));
        }
        else if(isalpha(exp_.top()[0])){
            numbers.push(var[exp_.top()[0]]);
        }
        else if(op_[exp_.top()] > 0 && op_[exp_.top()] < 4) // + - / * ^
        {
            v1 = numbers.top();
            numbers.pop();
            v2 = numbers.top();
            numbers.pop();
            if(exp_.top() == "+")
                numbers.push(new AdditionExp(v2,v1));
            else if(exp_.top() == "-")
                numbers.push(new SubtractionExp(v2,v1));
            else if(exp_.top() == "/")
                numbers.push(new DivisionExp(v2,v1));
            else if(exp_.top() == "*")
                numbers.push(new MultiplicationExp(v2,v1));
            else if(exp_.top() == "^")
                numbers.push(new PowerExp(v2,v1));
        }
        else{
            return nullptr;
        }
        exp_.pop();
    }
    return numbers.top();
}

int main() {
    cout << "KALKULATOR ZMIENNYCH\nAby zakonczyc wpisz #\nAby wykonac obliczenia wpisz =\n";

    char exp_default[100];
    char symbols[] = " abcdefghijklmnopqrstuvwxyz.1234567890/*()!+=-^";
    char *expression, *variable;

    while(true) {
        gets(exp_default);

        if (exp_default[0] == '#') return 0;
        if(exp_default[0] == '=')
        {
            if(!var.empty())
            {
                for(auto elem: var) //wypisuje mapę wyrazen
                {
                    cout << elem.first <<  " = ";
                    elem.second->print();
                }
            } else
                cout << "brak dzialan do wykonania" << endl;
            continue;
        }
        if(strlen(exp_default) == strcspn(exp_default,symbols) || strlen(exp_default) == strcspn(exp_default,"="))
            //sprawdza czy wystepuja niechciane znaki i czy na pewno jest "="
        {
            cout << "bledne dzialanie!" << endl;
            continue;
        }

        variable = strtok(exp_default, " ="); // dziele wczytanego stringa na zmienna i jej dzialanie
        expression = strtok(nullptr, " =");

        if(strlen(variable) != 1 || !isalpha(variable[0])) //z zalozenia zmienna jest jednoliterowa
        {
            cout << "bledna zmienna" << endl;
            continue;
        }

        stack<string> s_expression = shuntingYard(expression);
        if (s_expression.top() == "@") {
            cout << "bledne dzialanie" << endl;
            continue;
        }

        stack<string> s_expression2; // przepisuje odrwotnie - stos s_expression do zmiany na queue lub listę by nie robic tej petli
        while (!s_expression.empty()) {
            s_expression2.push(s_expression.top());
           // cout << s_expression2.top() << ' ';
            s_expression.pop();
        }
        //cout << endl;

        Expression* expression_ = resolve(s_expression2);
        if(!expression_)
        {
            cout << "bledne dzialanie" << endl;
            continue;
        }

        if(var.find(variable[0]) != var.end()){ //zmienna byla juz podana i zmienia jej dzialanie
            var[variable[0]]->setExpression(expression_);
            continue;
        }
        var[variable[0]] = new ExpressionContainer(expression_);

    }
}