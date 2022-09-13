/**
 *\file varelement.h
 *\brief Header for VariableElement class
 */

#ifndef VARIABLEELEMENT_H
#define VARIABLEELEMENT_H
#include <string>
#include <iostream>
#include <memory>
#include <sstream>

#include "element.h"
#include "valuation.h"

/**
 *\class VariableElement
 *\brief A class for integer values, subclass of Element
 */ 
class VariableElement;
using unique_elem_ptr = std::unique_ptr<Element>;

class VariableElement : public Element
{
    public:
        /**
         *\brief Default constructor
         */
        VariableElement();
        /**
         *\brief Parametric constructor
         *\param v char variable
         */
        VariableElement(char v);
        /**
         *\brief Default destructor
         */
        virtual ~VariableElement() = default;
        /**
         *\brief Getter for VariableElement's value
         *\return char variable
         */
        char getVal() const;
        /**
         *\brief Setter for VariableElement's value
         *\param v char
         */
        void setVal(char v);  
        /**
         *\brief Evaluates the val
         *\param v Valuation map
         *\throw exception if variable is not defined
         *\return v[var]
         */
        int evaluate(const Valuation& v) const override;
        /**
         *\brief '==' operator for VariableElements
         *\param i Comparison element
         *\return true or false
         */
        bool operator==(const VariableElement& i) const;
        /**
         *\brief Returns string representation of VariableElement
         *\return string representation of VariableElement
         */
        std::string toString() const override;
        /**
         *\brief Clones the VariableElement and returns a pointer to it
         *\return Element* pointer
         */
        unique_elem_ptr clone() const override;
             

    private:
        char var;  
};

#endif