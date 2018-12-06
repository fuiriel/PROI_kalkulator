//
// Created by KSzym on 05.12.2018.
//
#include <iostream>
#include <cmath>
#include "classes.h"
using namespace  std;

//silnia
float factorial(float n)
{
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
   // cout << " no" << m_value << " ";
    return m_value;
}
void Number::print(){
    cout << m_value;
}

//potęgowanie
float PowerExp::eval(){
    return pow(m_exp1->eval(), m_exp2->eval());
}
void  PowerExp::print() {
    cout << eval();
}

//Log10
float Log10Exp::eval(){
    return log10(m_exp->eval());
}
void  Log10Exp::print() {
    cout << eval();
}

//Ln
float LnExp::eval(){
    return log(m_exp->eval());
}
void  LnExp::print() {
    cout << eval();
}

//Exp
float ExpExp::eval(){
    return exp(m_exp->eval());
}
void  ExpExp::print() {
    cout << eval();
}

//dodawanie
float AdditionExp::eval() {
    return m_exp1->eval() + m_exp2->eval();
}
void  AdditionExp::print() {
    cout << eval();
}

//odejmowanie
float SubtractionExp::eval() {
    return m_exp1->eval() - m_exp2->eval();
}
void  SubtractionExp::print() {
    cout << eval();
}

//mnożenie
float MultiplicationExp::eval() {
    return m_exp1->eval() * m_exp2->eval();
}
void  MultiplicationExp::print() {
    cout << eval();
}

//dzielenie
float DivisionExp::eval() {
    return m_exp1->eval() / m_exp2->eval();
}
void  DivisionExp::print() {
    cout << eval();
}
