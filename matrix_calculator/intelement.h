/**
 *\file intelement.h
 *\brief Header for IntElement class
 */

#ifndef INTELEMENT_H
#define INTELEMENT_H
#include <string>
#include <iostream>

/**
 *\class IntElement
 *\brief A class for integer values
 */ 

class IntElement 
{
    public:
        /**
         *\brief Default constructor
         */
        IntElement();
        /**
         *\brief Parametric constructor
         *\param v Integer value
         */
        IntElement(int v);
        /**
         *\brief Default destructor
         */
        virtual ~IntElement() = default;
        /**
         *\brief Getter for IntElement's value
         *\return integer value
         */
        int getVal() const;
        /**
         *\brief Setter for IntElement's value
         */
        void setVal(int v);       
        /**
         *\brief '+=' operator for IntElements
         *\param i Element to be added
         *\return *this
         */
        IntElement& operator+=(const IntElement& i);
        /**
         *\brief '-=' operator for IntElements
         *\param i Element to be substracted 
         *\return *this
         */
        IntElement& operator-=(const IntElement& i);
        /**
         *\brief '*=' operator for IntElements
         *\param i Multiplier 
         *\return *this
         */
        IntElement& operator*=(const IntElement& i);
        /**
         *\brief '==' operator for IntElements
         *\param i Comparison element
         *\return true or false
         */
        bool operator==(const IntElement& i) const;
        /**
         *\brief Returns string representation of IntElement
         *\return string representation of IntElement
         */
        std::string toString() const;

    private:
        int val;  
};

/**
 *\brief Output operator
 *\param os Output stream
 *\param ie Element to output
 */
std::ostream& operator<<(std::ostream& os, const IntElement& ie);
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