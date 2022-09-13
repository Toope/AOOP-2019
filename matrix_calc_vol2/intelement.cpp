
#include "intelement.h"

IntElement::IntElement() : val{0} {}   //default value is 0

IntElement::IntElement(int v) : val{v} {}

int IntElement::getVal() const 
{
    return val;
}

void IntElement::setVal(int v)
{   
    val = v;
}

int IntElement::evaluate(const Valuation& v) const
{
    return val;
}

IntElement& IntElement::operator+=(const IntElement& i) 
{
    val += i.getVal();
    return *this;
}

IntElement& IntElement::operator-=(const IntElement& i) 
{
    val -= i.getVal();
    return *this;
}

IntElement& IntElement::operator*=(const IntElement& i) 
{
    val *= i.getVal();
    return *this;
}

bool IntElement::operator==(const IntElement& i) const
{
    if(val == i.getVal()) 
    {
        return true;
    }
    return false;
}

std::string IntElement::toString() const
{
    std::stringstream ss;   
    ss << val;
    return ss.str();
}

unique_elem_ptr IntElement::clone() const 
{
    return unique_elem_ptr(new IntElement(*this));   //returns unique_ptr to IntElement
}


//operators from outside of the class
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





