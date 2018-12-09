#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <stack>
#include <list>
#include "classes.h"
#include "function.h"
using namespace std;

/*czy b = b*2??*/

std::map<char, ExpressionContainer*> var;

int main() {
    cout << "KALKULATOR ZMIENNYCH\nAby zakonczyc wpisz #\nAby wykonac obliczenia wpisz =\n";

    char exp_default[100];
    char symbols[] = " abcdefghijklmnopqrstuvwxyz.1234567890/*()!+=-^";
    char *expression, *variable;
    string s;
    while(true) {
        getline(cin, s);
        strcpy(exp_default, s.c_str());

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
            s_expression.pop();
        }

        Expression* expression_ = resolve(s_expression2, var);
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