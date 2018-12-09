//
// Created by KSzym on 05.12.2018.
//
#include <iostream>
#include <cmath>
#include "classes.h"
using namespace  std;

void Expression::print() {
    cout << eval() << endl;
}

float ExpressionContainer::eval() {
    return m_exp->eval();
}

void ExpressionContainer::setExpression(Expression *exp){
    m_exp = exp;
}

//silnia
float factorial(float n)
{
    if(n - floor(n) > 0)
    {
        cout << "bledne dzialanie!" << endl;
        return -infinityf(); //zwraca -inf - sprawdz
    }
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}
float FactorialExp::eval() {
    return factorial(m_exp->eval());
}

//liczba
float Number::eval() {
    return m_value;
}

//potęgowanie
float PowerExp::eval(){
    return pow(m_exp1->eval(), m_exp2->eval());
}

//Log10
float Log10Exp::eval(){
    return log10(m_exp->eval());
}

//Ln
float LnExp::eval(){
    return log(m_exp->eval());
}

//Exp
float ExpExp::eval(){
    return exp(m_exp->eval());
}

//dodawanie
float AdditionExp::eval() {
    return m_exp1->eval() + m_exp2->eval();
}

//odejmowanie
float SubtractionExp::eval() {
    return m_exp1->eval() - m_exp2->eval();
}

//mnożenie
float MultiplicationExp::eval() {
    return m_exp1->eval() * m_exp2->eval();
}

//dzielenie
float DivisionExp::eval() {
    return m_exp1->eval() / m_exp2->eval();
}
