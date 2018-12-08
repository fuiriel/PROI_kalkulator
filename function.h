//
// Created by KSzym on 07.12.2018.
//

#ifndef PROI_KALKULATOR_FUNCTION_H
#define PROI_KALKULATOR_FUNCTION_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <stack>
#include <list>
#include "classes.h"
#include "maps.h"
#include "function.h"


std::stack<std::string> shunting_yard(char* c);
Expression* resolving(std::list<std::string> *exp_);
Expression* resolve(std::stack<std::string> exp_);

#endif //PROI_KALKULATOR_FUNCTION_H
