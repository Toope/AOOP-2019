#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "squarematrix.h"

TEST_CASE("SquareMatrix tests","[squarematrix]"){                            //tested:
    SquareMatrix sm00;
    CHECK(sm00.toString() == "[[0,0,0][0,0,0][0,0,0]]");                     //default
    SquareMatrix sm0{"[[0,0][0,0]]"};
    SquareMatrix sm1{"[[1,2][4,3]]"};
    CHECK(sm1.toString() == "[[1,2][4,3]]");                                 //parametric
    sm0=sm1;                                                    
    CHECK(sm0.toString() == "[[1,2][4,3]]");                                 //=
    sm1.print(std::cout);                                                    //print()
    sm0+=sm1;
    CHECK(sm0.toString() == "[[2,4][8,6]]");                                 //+=
    sm0-=sm1;
    CHECK(sm0.toString() == "[[1,2][4,3]]");                                 //-=
    SquareMatrix sm0_t = sm0.transpose();                       
    CHECK(sm0_t.toString() == "[[1,4][2,3]]");                               //transpose()
    SquareMatrix sm3x3{"[[1,2,3][4,5,6][7,8,9]]"};
    SquareMatrix sm3x3_t = sm3x3.transpose();
    CHECK(sm3x3_t.toString() == "[[1,4,7][2,5,8][3,6,9]]");
    sm3x3*=sm3x3_t;                                                          //*=
    CHECK(sm3x3.toString() == "[[14,32,50][32,77,122][50,122,194]]");
    SquareMatrix sm4 = sm3x3 + sm3x3_t;                                      //+
    CHECK(sm4.toString() == "[[15,36,57][34,82,130][53,128,203]]");
    SquareMatrix sm5 = sm3x3 - sm3x3_t;                                      //-
    CHECK(sm5.toString() == "[[13,28,43][30,72,114][47,116,185]]"); 
    SquareMatrix sm6 = sm3x3 * sm3x3_t;                                      //*
    CHECK(sm6.toString() == "[[228,516,804][552,1245,1938][876,1974,3072]]");   
    std::cout << sm6 << std::endl;                                           //<<
    SquareMatrix sm5_copy = SquareMatrix{sm5};                               //copy constructor
    CHECK(sm5 == sm5_copy);                                                  //==
    SquareMatrix one{"[[1]]"};
    CHECK_FALSE(sm5 == one);
    
}

TEST_CASE("SquareMatrix throw tests","[throw_tests]") 
{
    //check the form of the string like in VT1   
    try
    {
        SquareMatrix nope{"[[0,1,2][3,4]]"};
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Not squarematrix!");
    }

    CHECK_THROWS(SquareMatrix{"[[1,2][3,4][5,6]]"}); 
    CHECK_THROWS(SquareMatrix{"[[1,2][3,4]"});
    CHECK_THROWS(SquareMatrix{"[1,2][3,4]]"});
    CHECK_THROWS(SquareMatrix{"[[1,2],[3,4]]"});
    CHECK_THROWS(SquareMatrix{"[[a,2][c,4]]"});
    CHECK_THROWS(SquareMatrix{"k[1,2][3,4]]"});
    CHECK_THROWS(SquareMatrix{"[[1-2][3,4]]"});
    CHECK_THROWS(SquareMatrix{"[[1,2][3,4]]k"});
    
    SquareMatrix sq2{"[[3,4][5,6]]"};               //test matrices
    SquareMatrix sq3{"[[1,2,7][3,4,8][5,6,9]]"};  
    
    //inside class operators
    try
    {
        sq2 += sq3;     
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl; 
        CHECK(std::string{e.what()} == "Dimension mismatch!"); //same error comes from other operators too
    }
    CHECK_THROWS(sq2 -= sq3);
    CHECK_THROWS(sq2 *= sq3);
    CHECK_THROWS(sq2 = sq3);
    
    //outside class operators
    try
    {
        SquareMatrix sq_op = sq3 * sq2;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Dimension mismatch!");
    }
    
    try
    {
        SquareMatrix sq_op = sq3 + sq2; 
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Dimension mismatch!");
    }
    
    try
    {
        SquareMatrix sq_op = sq3 - sq2;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Dimension mismatch!");
    }
    
}


