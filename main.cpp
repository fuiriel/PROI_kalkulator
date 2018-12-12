#include <iostream>
#include <cstring>
#include <map>
#include <queue>
#include <list>
#include "classes.h"
#include "function.h"
using namespace std;

/*czy b = b*2?? czy blad???
 *b = a  a = b*/

std::map<char, ExpressionContainer*> var;

const char* noSpace(char *c) //usuwa spacje
{
    string newC = "";

    for(int i = 0; i < strlen(c); i++)
        if(c[i] != ' ') newC += c[i];

    return newC.c_str();
}
void printQueue(queue<string> q)
{
    while(!q.empty())
    {
        cout << q.front() <<' ';
        q.pop();
    }
    cout << endl;
}

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

        char clear_exp_default[100]; //działanie wyczyszczone -> bez spacji
        strcpy(clear_exp_default, noSpace(exp_default)); //kopiuje tekst bez spacji
        size_t sizeofexp = strlen(clear_exp_default);

        variable = strtok(clear_exp_default, " ="); // dzieli wczytanego stringa na zmienna
        if(strlen(variable) != 1 || !isalpha(variable[0])) // brak dzialania po '=' o zmienna nie 1-literowa
        {
            cout << "bledna zmienna!" << endl;
            continue;
        }

        expression = strtok(nullptr, "="); //dzieli wczytanego stringa na  dzialanie
        if(!expression || sizeofexp != strlen(variable) + strlen(expression)+1) // więcej niż jedno '=' lub brak dzialania po '='
        {
            cout << "bledne dzialanie!" << endl;
            continue;
        }
        queue<string> s_expression = shuntingYard(expression);
        //printQueue(s_expression);
        if (s_expression.back() == "@") {
            cout << "bledne dzialanie" << endl;
            continue;
        }

        Expression* expression_ = resolve(s_expression, var);
        if(!expression_) //nie rozwiazano dzialania
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