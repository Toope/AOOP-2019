/**
 *\file compositeelement.h
 *\brief Header for CompositeElement class
 */
 
#ifndef COMPOSITEELEMENT_H
#define COMPOSITEELEMENT_H

#include "element.h"
#include <functional>
/**
 *\class CompositeElement
 *\brief A class for composite values, subclass of Element
 */ 
 
class CompositeElement : public Element
{
    public:
        /**
         *\brief Parametric constructor
         *\param e1 Element for operation
         *\param e2 Element for operation
         *\param op std::function, function
         *\param opc char used in the printing of the CompositeElement
         */
        CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc);
        /**
         *\brief Copy constructor
         *\param e CompositeElement to be copied
         */
        CompositeElement(const CompositeElement& e);
        /**
         *\brief '=' operator for CompositeElements
         *\param m Assigned element
         *\return *this
         */
        CompositeElement& operator=(const CompositeElement& e);
        /**
         *\brief Default destructor
         */
        virtual ~CompositeElement() = default;
        /**
         *\brief Returns string representation of CompositeElement
         *\return "(" + oprnd1->toString() + op_ch + oprnd2->toString() + ")"
         */
        std::string toString() const override;
        /**
         *\brief Clones the Element and returns a pointer to it
         *\return Element* pointer
         */
        Element* clone() const override;
        /**
         *\brief Evaluates the val
         *\param v Valuation map
         *\return op_fun(oprnd1->evaluate(v), oprnd1->evaluate(v))
         */
        int evaluate(const Valuation& v) const override;
        
    
    private:
        unique_elem_ptr oprnd1;
        unique_elem_ptr oprnd2;
        std::function<int(int,int)> op_fun;
        char op_ch;
};

#endif