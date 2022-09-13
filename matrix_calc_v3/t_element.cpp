#include "t_element.h"


//different 
template<>
int IntElement::evaluate(const Valuation& v) const
{
    return val;
}
template<>
int VariableElement::evaluate(const Valuation& v) const 
{
    return v.at(val);
}

//found only from VarElements

template<>
VariableElement::TElement() : val('a') {}

//found only from IntElements

template<>
IntElement::TElement() : val(0) {}

template<>
IntElement& IntElement::operator+=(const IntElement& i) 
{
    val += i.getVal();
    return *this;
}
template<>
IntElement& IntElement::operator-=(const IntElement& i) 
{
    val -= i.getVal();
    return *this;
}
template<>
IntElement& IntElement::operator*=(const IntElement& i) 
{
    val *= i.getVal();
    return *this;
}

IntElement operator+(const IntElement& i1, const IntElement& i2)
{
    IntElement sum{i1.getVal() + i2.getVal()};
    return sum;
}

IntElement operator-(const IntElement& i1, const IntElement& i2)
{
    IntElement minus{i1.getVal() - i2.getVal()};
    return minus;
}

IntElement operator*(const IntElement& i1, const IntElement& i2)
{
    IntElement mult{i1.getVal() * i2.getVal()};
    return mult;
}
