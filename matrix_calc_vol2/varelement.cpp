
#include "varelement.h"

VariableElement::VariableElement() : var{'a'} {}   //default value is 'a'

VariableElement::VariableElement(char v) : var{v} {}

char VariableElement::getVal() const 
{
    return var;
}

void VariableElement::setVal(char v)
{   
    var = v;
}

int VariableElement::evaluate(const Valuation& v) const   //throws exception
{
    return v.at(var);
}

bool VariableElement::operator==(const VariableElement& i) const
{
    if(var == i.getVal()) 
    {
        return true;
    }
    return false;
}

std::string VariableElement::toString() const
{
    std::stringstream ss;   
    ss << var;
    return ss.str();
}

unique_elem_ptr VariableElement::clone() const 
{
    return unique_elem_ptr(new VariableElement(*this));   //returns unique_ptr to VariableElement
}





