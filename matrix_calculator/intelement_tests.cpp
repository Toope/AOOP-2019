//#define CATCH_CONFIG_MAIN     //include this in only one file
#include "catch.hpp"
#include "intelement.h"

TEST_CASE("IntElement tests","[intelement]")        //tested:
{      
    IntElement zero;                                //default
    CHECK(zero.toString() == "0");                  //toString()
    IntElement one{1};                              //parametric 
    CHECK(one.toString() == "1");
    IntElement two{2};    
    CHECK_FALSE(one==two);                          //==
    one += two;                                     //+=
    CHECK(one.toString() == "3");
    one *= two;                                     //*=
    CHECK(one.toString() == "6");
    IntElement five{5};
    one -= five;                                    //-=
    CHECK(one.toString() == "1");
    
    IntElement sum = one + five;                    //+
    CHECK(sum.toString() == "6");
    
    IntElement minus = one - five;                  //-
    CHECK(minus.toString() == "-4");
    
    IntElement mult = two * five;                   //*
    CHECK(mult.toString() == "10");
    
    two.setVal(8);                                  //setVal()
    CHECK(two.getVal()==8);                         //getVal()
    
    std::cout << two << std::endl;                  //<<    
}
