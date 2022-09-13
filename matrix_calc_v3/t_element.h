/**
 *\file t_element.h
 *\brief Header for TElement template class
 */

#ifndef T_ELEMENT_H
#define T_ELEMENT_H

#include <string>
#include <iostream>
#include <memory>
#include <sstream>

#include "valuation.h"
#include "element.h"

/**
*\class TElement
*\brief Template class for Elements
*\tparam T int or char
*/
template<typename T>
class TElement : public Element
{
    public:
        /**
         *\brief Default constructor
         */
        TElement();
         /**
         *\brief Parametric constructor
         *\param v int or char value
         */
        TElement(T v) : val{v} {};
        /**
        *\brief Default destructor
        */
        virtual ~TElement() = default;    
         /**
         *\brief Getter for value val
         *\return char or int value val
         */
        T getVal() const
        {
            return val;
        };
        /**
         *\brief Setter for value val
         *\param v int or char value
         */
        void setVal(T v) 
        {
            val = v;
        };
        /**
         *\brief Returns string representation of TElement
         *\return string representation of TElement
         */
        std::string toString() const 
        {
            std::stringstream ss;   
            ss << val;
            return ss.str();
        };
         /**
         *\brief Clones the TElement and returns a pointer to it
         *\return Element* pointer
         */
        Element* clone() const 
        {
            return new TElement<T>(*this); 
        }
        /**
         *\brief Evaluates the val
         *\param v Valuation map
         *\return val
         */
        int evaluate(const Valuation& v) const;  
        //IntElement operators      
        /**
         *\brief '+=' operator for IntElements
         *\param i Element to be added
         *\return *this
         */
        TElement& operator+=(const TElement& i);
        /**
         *\brief '-=' operator for IntElements
         *\param i Element to be substracted 
         *\return *this
         */
        TElement& operator-=(const TElement& i);
        /**
         *\brief '*=' operator for IntElements
         *\param i Multiplier 
         *\return *this
         */
        TElement& operator*=(const TElement& i);
       
    private:
        T val;  //can be int or char  
};

using IntElement = TElement<int>;
using VariableElement = TElement<char>;
using unique_intelem_ptr = std::unique_ptr<IntElement>;

/**
*\brief output operator for TElement<T>
*\tparam T Type of TElement object
*\param os output streambuf
*\param ie object to be outputted
*\return output stream with ie written to it
*/
template<typename T>
std::ostream& operator<<(std::ostream& os, const TElement<T>& ie)
{
    os << ie.toString();
    return os;
};
/**
 *\brief '==' operator for TElements
 *\param e1 Comparison element
 *\param e2 Comparison element
 *\return true or false
 */
template<typename T>
bool operator==(const TElement<T>& e1, const TElement<T>& e2)
{
     return(e1.toString() == e2.toString());
};

//IntElement operators from outside
/**
 *\brief Sum operator for IntElements
 *\param i1 First addend 
 *\param i2 Second addend
 */
IntElement operator+(const IntElement& i1, const IntElement&i2);
/**
 *\brief Substraction operator for IntElements
 *\param i1 Minuend 
 *\param i2 Substractor
 */
IntElement operator-(const IntElement& i1, const IntElement& i2);
/**
 *\brief Multiplication operator for IntElements
 *\param i1 Multiplicand
 *\param i2 Multiplier
 */
IntElement operator*(const IntElement& i1, const IntElement& i2);

#endif