/**
 *\file elementarymatrix.h
 *\brief Header for ElementaryMatrix template class
 */

#ifndef ELEMENTARYMATRIX_H
#define ELEMENTARYMATRIX_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <stdexcept>

#include "t_element.h"
#include "compositeelement.h"

template<typename T>
class ElementarySquareMatrix;
using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;
/**
*\class ElementarySquareMatrix
*\brief Template class for Matrices
*\tparam T Element class
*/
template<typename T>
class ElementarySquareMatrix  
{
    public:
        /**
         *\brief Default constructor
         */
        ElementarySquareMatrix() : n{0} {};
        /**
         *\brief Constructs a matrix from string input
         *\param str_m String input of the form [[a11,...,a1n]...[an1,...,ann]]
         */
        ElementarySquareMatrix(const std::string& str_m) 
        {
            isSquareMatrix(str_m);
            n = elements.size();   
        };
        /**
         *\brief Copy constructor
         *\param m ElementarySquareMatrix to be copied
         */
        ElementarySquareMatrix(const ElementarySquareMatrix<T>& m) 
        {
            n = m.n;
            std::vector<std::unique_ptr<T>> row_vector;
            for(auto &row : m.elements) 
            {              
                for(auto &elem : row) 
                {
                    T *elemptr = dynamic_cast<T*>(elem->clone());
                    if(elemptr == nullptr)
                        throw std::invalid_argument("Not matching!");
                    row_vector.push_back(std::unique_ptr<T>(elemptr));
                    elemptr = nullptr;
                }
                elements.push_back(std::move(row_vector));
            }               
        };
        /**
         *\brief Move constructor
         *\param m ElementarySquareMatrix to be moved
         */
        ElementarySquareMatrix(ElementarySquareMatrix<T>&& m) 
        {
            n = m.n;
            elements.clear();
            std::vector<std::unique_ptr<T>> row_vector;
            for(auto &row : m.elements) 
            {              
                for(auto &elem : row) 
                {
                    T *elemptr = dynamic_cast<T*>(elem->clone());
                    if(elemptr == nullptr)
                        throw std::invalid_argument("Not matching!");
                    row_vector.push_back(std::unique_ptr<T>(elemptr));
                    elemptr = nullptr;
                }
                elements.push_back(std::move(row_vector));   
            }
            m.elements.clear();
        };
        /**
         *\brief Default destructor
         */
        virtual ~ElementarySquareMatrix() = default;
        /**
         *\brief '=' operator for ElementarySquareMatrices
         *\param m Assigned matrix
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ElementarySquareMatrix& operator=(const ElementarySquareMatrix& m);
        /**
         *\brief '=' move operator for ElementarySquareMatrices
         *\param m Matrix to be assigned and moved
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ElementarySquareMatrix& operator=(ElementarySquareMatrix&& m);
        /**
         *\brief Transposes the matrix       
         *\return transposed matrix
         */
        ElementarySquareMatrix transpose() const;
        /**
         *\brief '+=' operator for ElementarySquareMatrices
         *\param m Matrix to be added
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ElementarySquareMatrix& operator+=(const ElementarySquareMatrix& m);
        /**
         *\brief '-=' operator for ElementarySquareMatrices
         *\param m Matrix to be substracted
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ElementarySquareMatrix& operator-=(const ElementarySquareMatrix& m);
        /**
         *\brief '*=' operator for ElementarySquareMatrices
         *\param m Multiplier matrix
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ElementarySquareMatrix& operator*=(const ElementarySquareMatrix& m);
        /**
         *\brief '==' operator for ElementarySquareMatrices
         *\param m Comparison matrix
         *\return true or false
         */
        bool operator==(const ElementarySquareMatrix& m) const 
        {
            if(n != m.n)
                return false; 
     
            return (this->toString() == m.toString()); 
        };
        /**
         *\brief '+' operator for SymbolicSquareMatrices
         *\param m Matrix to be added
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return SymbolicSquareMatrix 
         */
        SymbolicSquareMatrix operator+(const SymbolicSquareMatrix& m) const;
        /**
         *\brief '-' operator for SymbolicSquareMatrices
         *\param m Matrix to be substracted
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return SymbolicSquareMatrix 
         */
        SymbolicSquareMatrix operator-(const SymbolicSquareMatrix& m) const;
        /**
         *\brief '*' operator for SymbolicSquareMatrices
         *\param m Matrix to be multiplied
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return SymbolicSquareMatrix 
         */
        SymbolicSquareMatrix operator*(const SymbolicSquareMatrix& m) const;
        /**
         *\brief Returns string representation of ElementarySquareMatrix
         *\return string representation of ElementarySquareMatrix in form [[a11,...,a1n]...[an1,...,ann]]
         */
        std::string toString() const 
        {
            std::stringstream ss;   
            ss << "[";
            for(auto& row : elements)
            {
                ss << "[";
                bool first = true;
                for(auto& col : row)
                {
                    if(!first) ss << ",";
                    ss << *col;
                    first = false;
                }
                ss << "]";        
            }   
            ss << "]";
            return ss.str();
        };
        /**
         *\brief outputs the matrix into the stream os in the form [[a11,...,a1n]...[an1,...,ann]]
         *\param os Output stream
         */
        void print(std::ostream& os) const 
        {
            os << "[";
            for(auto& row : elements)
            {
                os << "[";
                bool first = true;
                for(auto& col : row)
                {
                    if(!first) os << ",";
                    os << *col;
                    first = false;
                }
                os << "]";        
            }   
            os << "]" << std::endl;
        };      
        /**
         *\brief Getter for SquareMatrice's dimension value n
         *\return integer value
         */
        int get_n() const 
        {
            return n;
        };
        /**
         *\brief A function to test if given string is a ElementarySquareMatrix and to save values into a vector of vectors
         *\param in Input string
         *\throw std::invalid_argument if the string can't be interpreted as a ElementarySquareMatrix
         */
        void isSquareMatrix(const std::string& in); 
        /**
        *\brief returns an instance of ConcreteSquareMatrix obtained by applying val to each element
        *\param Valuation map
        *\throw an exception if applying val can't be obtained
        *\return an instance of ConcreteSquareMatrix
        */
        ConcreteSquareMatrix evaluate(const Valuation& val) const; 
        
        private:
            unsigned int n;
            std::vector<std::vector<std::unique_ptr<T>>> elements;
            friend class ElementarySquareMatrix<Element>;
    
};

/**
 *\brief Output operator
 *\param os Output stream
 *\param ie Matrix to output
 */
 template<typename T> 
std::ostream& operator<<(std::ostream& os, const ElementarySquareMatrix<T>& m) 
{
    os << m.toString();
    return os;
}
/**
 *\brief Sum operator for ConcreteSquareMatrices
 *\param m1 First addend 
 *\param m2 Second addend
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The sum of values
 */
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
/**
 *\brief Substraction operator for ConcreteSquareMatrices
 *\param m1 Minuend 
 *\param m2 Substractor
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The result of substraction
 */
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
/**
 *\brief Multiplication operator for ConcreteSquareMatrices
 *\param m1 Multiplicand
 *\param m2 Multiplier
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The result of multiplication
 */
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);

#endif