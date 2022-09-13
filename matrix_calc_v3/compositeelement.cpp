#include "compositeelement.h"


CompositeElement::CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc) : oprnd1{unique_elem_ptr(e1.clone())}, 
                                                                                                        oprnd2{unique_elem_ptr(e2.clone())}, op_fun{op}, op_ch{opc}
{   
}

CompositeElement::CompositeElement(const CompositeElement& e)
{
    oprnd1 = unique_elem_ptr((*e.oprnd1).clone());
    oprnd2 = unique_elem_ptr((*e.oprnd2).clone());
    op_fun = e.op_fun;
    op_ch = e.op_ch;     
}

CompositeElement& CompositeElement::operator=(const CompositeElement& e) 
{
    oprnd1 = unique_elem_ptr((*e.oprnd1).clone());
    oprnd2 = unique_elem_ptr((*e.oprnd2).clone());
    op_fun = e.op_fun;
    op_ch = e.op_ch;  
    return *this;
}

std::string CompositeElement::toString() const 
{
    return "(" + oprnd1->toString() + op_ch + oprnd2->toString() + ")";
}

Element* CompositeElement::clone() const 
{
    return new CompositeElement(*this);
}

int CompositeElement::evaluate(const Valuation& v) const 
{
    return op_fun(oprnd1->evaluate(v), oprnd2->evaluate(v));
}