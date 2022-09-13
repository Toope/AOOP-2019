/**
 *\file concretematrix.h
 *\brief Header for ConcreteSquareMatrix class
 */

#ifndef CONCRETESQUAREMATRIX_H
#define CONCRETESQUAREMATRIX_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <memory>

#include "intelement.h"
 
 /**
 *\class ConcreteSquareMatrix
 *\brief A class for numerical square matrices
 */ 

class ConcreteSquareMatrix 
{
    public:
        /**
         *\brief Default constructor
         */
        ConcreteSquareMatrix();
        /**
         *\brief Constructs a matrix from string input
         *\param s String input of the form [[a11,...,a1n]...[an1,...,ann]]
         */
        ConcreteSquareMatrix(const std::string& str_m);
        /**
         *\brief Copy constructor
         *\param m ConcreteSquareMatrix to be copied
         */
        ConcreteSquareMatrix(const ConcreteSquareMatrix& m);
        /**
         *\brief Move constructor
         *\param m ConcreteSquareMatrix to be moved
         */
        ConcreteSquareMatrix(ConcreteSquareMatrix&& m);
        /**
         *\brief Default destructor
         */
        virtual ~ConcreteSquareMatrix() = default;
        /**
         *\brief '=' operator for SquareMatrices
         *\param m Assigned matrix
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix& m);
        /**
         *\brief '=' move operator for SquareMatrices
         *\param m Matrix to be assigned and moved
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& m);
        /**
         *\brief Transposes the matrix       
         *\return transposed matrix
         */
        ConcreteSquareMatrix transpose() const;
        /**
         *\brief '+=' operator for SquareMatrices
         *\param m Matrix to be added
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);
        /**
         *\brief '-=' operator for SquareMatrices
         *\param m Matrix to be substracted
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);
        /**
         *\brief '*=' operator for SquareMatrices
         *\param m Multiplier matrix
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);
        /**
         *\brief '==' operator for SquareMatrices
         *\param m Comparison matrix
         *\return true or false
         */
        bool operator==(const ConcreteSquareMatrix& m) const;
        /**
         *\brief Returns string representation of ConcreteSquareMatrix
         *\return string representation of ConcreteSquareMatrix in form [[a11,...,a1n]...[an1,...,ann]]
         */
        std::string toString() const;
        /**
         *\brief outputs the matrix into the stream os in the form [[a11,...,a1n]...[an1,...,ann]]
         */
        void print(std::ostream& os) const;       
        /**
         *\brief Getter for SquareMatrice's dimension value n
         *\return integer value
         */
        int get_n() const;
        /**
         *\brief A function to test if given string is a ConcreteSquareMatrix and to save values into a vector of vectors
         *\param in Input string
         *\throw std::invalid_argument if the string can't be interpreted as a ConcreteSquareMatrix
         */
        void isConcreteSquareMatrix(const std::string& in);
        
    private:
        unsigned int n;
        std::vector<std::vector<unique_intelem_ptr>> elements;
};

/**
 *\brief Output operator
 *\param os Output stream
 *\param ie Matrix to output
 */
std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m);
/**
 *\brief Sum operator for SquareMatrices
 *\param m1 First addend 
 *\param m2 Second addend
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The sum of values
 */
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
/**
 *\brief Substraction operator for SquareMatrices
 *\param m1 Minuend 
 *\param m2 Substractor
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The result of substraction
 */
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
/**
 *\brief Multiplication operator for SquareMatrices
 *\param m1 Multiplicand
 *\param m2 Multiplier
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The result of multiplication
 */
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);


#endif