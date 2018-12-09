//
// Created by KSzym on 07.12.2018.
//

#ifndef PROI_KALKULATOR_MAPS_H
#define PROI_KALKULATOR_MAPS_H
#include <map>
#include "classes.h"

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

std::map<char, ExpressionContainer*> var;

#endif //PROI_KALKULATOR_MAPS_H
