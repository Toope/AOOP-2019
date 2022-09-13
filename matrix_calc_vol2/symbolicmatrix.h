/**
 *\file symbolicmatrix.h
 *\brief Header for SymbolicSquareMatrix class
 */

#ifndef SYMBOLICSQUAREMATRIX_H
#define SYMBOLICSQUAREMATRIX_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <stdexcept> 

#include "intelement.h"
#include "varelement.h"
#include "concretematrix.h"

 
 /**
 *\class SymbolicSquareMatrix
 *\brief A class for symbolic square matrices
 */ 

class SymbolicSquareMatrix 
{
    public:
        /**
         *\brief Default constructor
         */
        SymbolicSquareMatrix();
        /**
         *\brief Constructs a matrix from string input
         *\param s String input of the form [[a11,...,a1n]...[an1,...,ann]]
         */
        SymbolicSquareMatrix(const std::string& str_m);
        /**
         *\brief Copy constructor
         *\param m SymbolicSquareMatrix to be copied
         */
        SymbolicSquareMatrix(const SymbolicSquareMatrix& m);
        /**
         *\brief Move constructor
         *\param m SymbolicSquareMatrix to be moved
         */
        SymbolicSquareMatrix(SymbolicSquareMatrix&& m);
        /**
         *\brief Default destructor
         */
        virtual ~SymbolicSquareMatrix() = default;
        /**
         *\brief '=' operator for SquareMatrices
         *\param m Assigned matrix
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix& m);
        /**
         *\brief '=' move operator for SquareMatrices
         *\param m Matrix to be assigned and moved
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&& m);
        /**
         *\brief Transposes the matrix       
         *\return transposed matrix
         */
        SymbolicSquareMatrix transpose() const;
        /**
         *\brief '==' operator for SquareMatrices
         *\param m Comparison matrix
         *\return true or false
         */
        bool operator==(const SymbolicSquareMatrix& m) const;
        /**
         *\brief Returns string representation of SymbolicSquareMatrix
         *\return string representation of SymbolicSquareMatrix in form [[a11,...,a1n]...[an1,...,ann]]
         */
        std::string toString() const;
        /**
         *\brief outputs the matrix into the stream os in the form [[a11,...,a1n]...[an1,...,ann]]
         */
        void print(std::ostream& os) const;       
        /**
         *\brief A function to test if given string is a SymbolicSquareMatrix and to save values into a vector of vectors
         *\param in Input string
         *\throw std::invalid_argument if the string can't be interpreted as a SymbolicSquareMatrix
         */
        void isSymbolicSquareMatrix(const std::string& in);
        /**
        *\brief returns an instance of ConcreteSquareMatrix obtained by applying val to each element
        *\param Valuation map
        *\throw an exception if applying val can't be obtained
        *\return an instance of ConcreteSquareMatrix
        */
        ConcreteSquareMatrix evaluate(const Valuation& val) const;
        
    private:
        unsigned int n;
        std::vector<std::vector<unique_elem_ptr>> elements;
};

/**
 *\brief Output operator
 *\param os Output stream
 *\param ie Matrix to output
 */
std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& m);

#endif