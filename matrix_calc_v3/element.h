/**
 *\file element.h
 *\brief Header for Element class/interface
 */

#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include <iostream>
#include <memory>
#include <sstream>

#include "valuation.h"

/**
 *\class Element
 *\brief An interface base class for values
 */ 
class Element;
using unique_elem_ptr = std::unique_ptr<Element>;
 
class Element 
{
    public:
        /**
         *\brief Default destructor
         */
        virtual ~Element() = default;
        /**
         *\brief Evaluates the val
         *\param v Valuation map
         *\return val
         */
        virtual int evaluate(const Valuation& v) const = 0;
        /**
         *\brief Returns string representation of IntElement
         *\return string representation of IntElement
         */
        virtual std::string toString() const = 0;
        /**
         *\brief Clones the Element and returns a pointer to it
         *\return Element* pointer
         */
        virtual Element* clone() const = 0;

};

/**
 *\brief Output operator
 *\param os Output stream
 *\param ie Element to output
 */
std::ostream& operator<<(std::ostream& os, const Element& ie);
/**
 *\brief '==' operator for Elements
 *\param e1 Comparison element
 *\param e2 Comparison element
 *\return true or false
 */
bool operator==(const Element& e1, const Element& e2);

#endif