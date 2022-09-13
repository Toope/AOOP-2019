By Tiia Leinonen, in spring 2019

Project: matrix_calc_v3
Files: 
    element.h
    element.cpp
    t_element.h
    t_element.cpp
    compositeelement.h
    compositeelement.cpp
    elementarymatrix.h
    elementarymatrix.cpp
    valuation.h
    tests.cpp
    catch.hpp
    main.cpp
    this README.txt

compile: g++ -Wall -o name.exe *.cpp
run: name.exe

Running the program performs a series of unit-tests using catch, and opens an UI with instructions how to use it to perform operations to matrices.
Matrices must be squarematrices, but can be symbolic [[a,b][c,d]], numeric [[1,2][3,4]] or mix of both [[a,b][2,4]].
Adding a valuation gives a symbol a numeric value, i.e. a = 7.
Evaluating a matrix means using these valuations to present the matrix in numeric form.