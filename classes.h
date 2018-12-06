//
// Created by KSzym on 05.12.2018.
//

#ifndef PROI_KALKULATOR_CLASSES_H
#define PROI_KALKULATOR_CLASSES_H

class Expression {
protected:
    std::string expression_;
public:
    virtual ~Expression() {}

    virtual float eval() = 0;
    virtual void print() = 0;
};

class Number: public Expression {
public:
    explicit Number(float num): m_value(num) {}
    ~Number() {}

    float eval();
    void print();
protected:
    float m_value;
};

class TwoOperandExp: public Expression {
public:
    explicit TwoOperandExp(Expression* exp1, Expression* exp2) : m_exp1(exp1), m_exp2(exp2) {}
    ~TwoOperandExp() {}
    //void print();
protected:
    Expression* m_exp1;
    Expression* m_exp2;
};

//silnia
class FactorialExp : public Expression {
public:
    explicit FactorialExp(Expression* exp) : m_exp(exp){}
    ~FactorialExp() {}
    float eval();
protected:
    Expression* m_exp;
};
//potegowanie
class PowerExp: public TwoOperandExp {
public:
    PowerExp(Expression* exp1, Expression* exp2) : TwoOperandExp(exp1, exp2) {}
    ~PowerExp() {}
    float eval();
    void print();
};
//log
class Log10Exp: public Expression {
public:
    explicit Log10Exp(Expression* exp) : m_exp(exp){}
    ~Log10Exp() {}
    float eval();
    void print();
protected:
    Expression* m_exp;
};
//ln
class LnExp: public Expression {
public:
    explicit LnExp(Expression* exp): m_exp(exp){}
    ~LnExp() {}
    float eval();
    void print();
protected:
    Expression* m_exp;
};
//exp
class ExpExp: public Expression {
public:
    explicit ExpExp(Expression* exp): m_exp(exp){}
    ~ExpExp() {}
    float eval();
    void print();
protected:
    Expression* m_exp;
};
// dodawanie
class AdditionExp: public TwoOperandExp {
public:
    AdditionExp(Expression* exp1, Expression* exp2) : TwoOperandExp(exp1, exp2) {}
    float eval();
    void print();
};
// odejmowanie
class SubtractionExp : public TwoOperandExp {
public:
    explicit SubtractionExp(Expression* exp1, Expression* exp2) : TwoOperandExp(exp1, exp2) {}
    float eval();
    void print();
};

// mnożenie
class MultiplicationExp : public TwoOperandExp {
public:
    explicit MultiplicationExp(Expression* exp1, Expression* exp2) : TwoOperandExp(exp1, exp2) {}
    float eval();
    void print();
};
// dzielenie
class DivisionExp : public TwoOperandExp {
public:
    explicit DivisionExp(Expression* exp1, Expression* exp2) : TwoOperandExp(exp1, exp2) {}
    float eval();
    void print();
};


#endif //PROI_KALKULATOR_CLASSES_H
