//
// Created by KSzym on 07.12.2018.
//

#ifndef PROI_KALKULATOR_FUNCTION_H
#define PROI_KALKULATOR_FUNCTION_H

std::stack<std::string> shuntingYard(char*);
Expression* resolve(std::stack<std::string> exp_, std::map<char, ExpressionContainer*>var);

#endif //PROI_KALKULATOR_FUNCTION_H
