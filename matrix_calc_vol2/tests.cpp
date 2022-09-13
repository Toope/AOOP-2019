#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "concretematrix.h"
#include "symbolicmatrix.h"
#include "element.h"
#include "intelement.h"
#include "varelement.h"
#include "valuation.h"

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
    
    Valuation map;
    map['a'] = 5;
    map['b'] = 20;
    
    CHECK(two.evaluate(map) == 8);                //evaluate
}

TEST_CASE("ConcreteSquareMatrix tests","[concretesquarematrix]"){                  //tested:
    ConcreteSquareMatrix sm00;
    CHECK(sm00.toString() == "[]");                                                //default
    ConcreteSquareMatrix sm0{"[[0,0][0,0]]"};
    ConcreteSquareMatrix sm1{"[[1,2][4,3]]"};
    CHECK(sm1.toString() == "[[1,2][4,3]]");                                       //parametric
    sm0=sm1;     
    CHECK(sm0.toString() == "[[1,2][4,3]]");                                       //=
    sm1.print(std::cout);                                                          //print()
    sm0+=sm1;
    CHECK(sm0.toString() == "[[2,4][8,6]]");                                       //+=
    sm0-=sm1;
    CHECK(sm0.toString() == "[[1,2][4,3]]");                                       //-=
    ConcreteSquareMatrix sm0_t = sm0.transpose();                       
    CHECK(sm0_t.toString() == "[[1,4][2,3]]");                                     //transpose()
    ConcreteSquareMatrix sm3x3{"[[1,2,3][4,5,6][7,8,9]]"};
    ConcreteSquareMatrix sm3x3_t = sm3x3.transpose();
    CHECK(sm3x3_t.toString() == "[[1,4,7][2,5,8][3,6,9]]");
    sm3x3*=sm3x3_t;                                                                //*=
    CHECK(sm3x3.toString() == "[[14,32,50][32,77,122][50,122,194]]");
    ConcreteSquareMatrix sm4 = sm3x3 + sm3x3_t;                                    //+
    CHECK(sm4.toString() == "[[15,36,57][34,82,130][53,128,203]]");
    ConcreteSquareMatrix sm5 = sm3x3 - sm3x3_t;                                    //-
    CHECK(sm5.toString() == "[[13,28,43][30,72,114][47,116,185]]"); 
    ConcreteSquareMatrix sm6 = sm3x3 * sm3x3_t;                                    //*
    CHECK(sm6.toString() == "[[228,516,804][552,1245,1938][876,1974,3072]]");   
    std::cout << sm6 << std::endl;                                                 //<<
    ConcreteSquareMatrix sm5_copy = ConcreteSquareMatrix{sm5};                     //copy constructor
    CHECK(sm5 == sm5_copy);                                                        //==
    ConcreteSquareMatrix one{"[[1]]"};
    CHECK_FALSE(sm5 == one);
    
    ConcreteSquareMatrix sm1_mov{std::move(sm1)};                                  //move constructor
    CHECK(sm1_mov.toString() == "[[1,2][4,3]]");
    CHECK(sm1.toString() == "[]");
    
    ConcreteSquareMatrix sq2{"[[3,4][5,6]]"};            
    ConcreteSquareMatrix sq3{"[[1,2,7][3,4,8][5,6,9]]"}; 
    
    sm1_mov = std::move(sq3);                                                      //move =
    CHECK(sm1_mov.toString() == "[[1,2,7][3,4,8][5,6,9]]");
    CHECK(sq3.toString() == "[]");
    
    sm1_mov = sm1_mov;                                                             //self assignment
    CHECK(sm1_mov.toString() == "[[1,2,7][3,4,8][5,6,9]]");
    
    sm1_mov = std::move(sm1_mov);                                                  //self move assignment
    CHECK(sm1_mov.toString() == "[[1,2,7][3,4,8][5,6,9]]");
    
}

TEST_CASE("ConcreteSquareMatrix throw tests","[CSM_throw_tests]") 
{
    //check the form of the string like in VT1   
    try
    {
        ConcreteSquareMatrix nope{"[[0,1,2][3,4]]"};
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Not ConcreteSquareMatrix! Rows and previous rows don't match!");
    }

    CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4][5,6]]"}); 
    CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4]"});
    CHECK_THROWS(ConcreteSquareMatrix{"[1,2][3,4]]"});
    CHECK_THROWS(ConcreteSquareMatrix{"[[1,2],[3,4]]"});
    CHECK_THROWS(ConcreteSquareMatrix{"[[a,2][c,4]]"});
    CHECK_THROWS(ConcreteSquareMatrix{"k[1,2][3,4]]"});
    CHECK_THROWS(ConcreteSquareMatrix{"[[1-2][3,4]]"});
    CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4]]k"});
    
    ConcreteSquareMatrix sq2{"[[3,4][5,6]]"};               //test matrices
    ConcreteSquareMatrix sq3{"[[1,2,7][3,4,8][5,6,9]]"};  
    
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
    
    //outside class operators
    try
    {
        ConcreteSquareMatrix sq_op = sq3 * sq2;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Dimension mismatch!");
    }
    
    try
    {
        ConcreteSquareMatrix sq_op = sq3 + sq2; 
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Dimension mismatch!");
    }
    
    try
    {
        ConcreteSquareMatrix sq_op = sq3 - sq2;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Dimension mismatch!");
    }
    
}

TEST_CASE("VariableElement tests","[variableelement]") 
{
    Valuation map;
    map['a'] = 5;
    map['b'] = 20;
    
    VariableElement a;                              //default
    CHECK(a.toString() == "a");      
    REQUIRE(a.evaluate(map) == 5);                  //evaluate()

    VariableElement b{'b'};                         //parametric 
    CHECK(b.toString() == "b");
    REQUIRE(b.evaluate(map) == 20);
       
    CHECK_FALSE(a==b);                              //==
    
    b.setVal('c');                                  //setVal()
    CHECK(b.getVal()=='c');                         //getVal()
    a.setVal('c');
    CHECK(a==b);
    
    try
    {
        a.evaluate(map);            //test exception: there's no 'c' in the map
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "map::at");
    }
    
    
    std::cout << b << std::endl;   
    
    CHECK((*a.clone()).toString() == a.toString()); //clone()
    
}

TEST_CASE("SymbolicSquareMatrix tests","[symbolicsquarematrix]") 
{
    Valuation map;
    map['a'] = 5;
    map['b'] = 20;
    
    SymbolicSquareMatrix ssm1;                                          //default
    SymbolicSquareMatrix ssm2{"[[1,a][3,b]]"};                          //parametric
    SymbolicSquareMatrix ssm3{"[[1,a][3,b]]"};
    SymbolicSquareMatrix ssm3_mov{std::move(ssm3)};                     //move constructor
    CHECK(ssm3_mov.toString() == "[[1,a][3,b]]");
    CHECK(ssm3.toString() == "[]");
    CHECK((ssm2.evaluate(map)).toString() == "[[1,5][3,20]]");          //evaluate + toString
    CHECK_FALSE(ssm1 == ssm2);                                          // ==
    CHECK(ssm3_mov == ssm2);
    ssm1 = ssm2;                                                        // =
    CHECK(ssm1.toString() == "[[1,a][3,b]]");
    ssm1 = ssm1;                                                        //= , self
    ssm1 = std::move(ssm1);                                             //move = 
    ssm2 = std::move(ssm1);
    CHECK(ssm2.toString() == "[[1,a][3,b]]");
    CHECK(ssm1.toString() == "[]");
    SymbolicSquareMatrix ssm2_t = ssm2.transpose();                     //transpose()
    CHECK(ssm2_t.toString() == "[[1,3][a,b]]");
    ssm2_t.print(std::cout);                                            //print()
    std::cout << ssm2 << std::endl;                                     //<<
    
    SymbolicSquareMatrix c{"[[1,a][c,b]]"};
    try
    {
        c.evaluate(map);            //test exception: there's no 'c' in the map
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "map::at");
    }
     
    
}

TEST_CASE("SymbolicSquareMatrix throw tests","[SSM_throw_tests]") 
{
    //check the form of the string like in VT1   
    try
    {
        SymbolicSquareMatrix nope{"[[0,1,c][3,4]]"};
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(std::string{e.what()} == "Not SymbolicSquareMatrix! Rows and previous rows don't match!");
    }

    CHECK_THROWS(SymbolicSquareMatrix{"[[1,a][3,b][c,6]]"}); 
    CHECK_THROWS(SymbolicSquareMatrix{"[[1,2][c,4]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[k,2][3,4]]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[1,2],[3,4]]"});
    CHECK_THROWS(SymbolicSquareMatrix{"k[1,2][3,4]]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[1-2][3,b]]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[1,g][3,4]]k"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[1,2][3,$]"});
    CHECK_THROWS(SymbolicSquareMatrix{"[[+,-][@,$]"});

}




























