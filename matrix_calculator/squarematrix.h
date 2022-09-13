/**
 *\file squarematrix.h
 *\brief Header for SquareMatrix class
 */

#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H
#include <string>
#include <iostream>
#include <vector>
#include "intelement.h"
 
 /**
 *\class SquareMatrix
 *\brief A class for square matrices
 */ 

class SquareMatrix 
{
    public:
        /**
         *\brief Default constructor
         */
        SquareMatrix();
        /**
         *\brief Constructs a matrix from string input
         *\param s String input of the form [[a11,...,a1n]...[an1,...,ann]]
         */
        SquareMatrix(const std::string& s);
        /**
         *\brief Copy constructor
         *\param m SquareMatrix to be copied
         */
        SquareMatrix(const SquareMatrix& m);
        /**
         *\brief Default destructor
         */
        virtual ~SquareMatrix() = default;
        /**
         *\brief '=' operator for SquareMatrices
         *\param m Assigned matrix
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        SquareMatrix& operator=(const SquareMatrix& m);
        /**
         *\brief Transposes the matrix       
         *\return transposed matrix
         */
        SquareMatrix transpose() const;
        /**
         *\brief '+=' operator for SquareMatrices
         *\param m Matrix to be added
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        SquareMatrix& operator+=(const SquareMatrix& m);
        /**
         *\brief '-=' operator for SquareMatrices
         *\param m Matrix to be substracted
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        SquareMatrix& operator-=(const SquareMatrix& m);
        /**
         *\brief '*=' operator for SquareMatrices
         *\param m Multiplier matrix
         *\throw std::invalid_argument if the matrices are of different sizes 
         *\return *this
         */
        SquareMatrix& operator*=(const SquareMatrix& m);
        /**
         *\brief '==' operator for SquareMatrices
         *\param m Comparison matrix
         *\return true or false
         */
        bool operator==(const SquareMatrix& m) const;
        /**
         *\brief Returns string representation of SquareMatrix
         *\return string representation of SquareMatrix in form [[a11,...,a1n]...[an1,...,ann]]
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
        
    private:
        int n;
        std::vector<std::vector<IntElement>> elements{};
};

/**
 *\brief Output operator
 *\param os Output stream
 *\param ie Matrix to output
 */
std::ostream& operator<<(std::ostream& os, const SquareMatrix& m);
/**
 *\brief Sum operator for SquareMatrices
 *\param m1 First addend 
 *\param m2 Second addend
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The sum of values
 */
SquareMatrix operator+(const SquareMatrix& m1, const SquareMatrix& m2);
/**
 *\brief Substraction operator for SquareMatrices
 *\param m1 Minuend 
 *\param m2 Substractor
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The result of substraction
 */
SquareMatrix operator-(const SquareMatrix& m1, const SquareMatrix& m2);
/**
 *\brief Multiplication operator for SquareMatrices
 *\param m1 Multiplicand
 *\param m2 Multiplier
 *\throw std::invalid_argument if the matrices are of different sizes 
 *\return The result of multiplication
 */
SquareMatrix operator*(const SquareMatrix& m1, const SquareMatrix& m2);
/**
 *\brief A function to test if given string is a squarematrix and to save values into a vector of vectors
 *\param in Input string
 *\throw std::invalid_argument if the string can't be interpreted as a squarematrix
 *\return vector of vectors
 */
std::vector<std::vector<IntElement> > isSquareMatrix(const std::string& in);

#endif