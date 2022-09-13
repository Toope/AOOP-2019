#define CATCH_CONFIG_RUNNER 
#include "catch.hpp"
#include <stack> 

#include "elementarymatrix.h"
#include "element.h"
#include "t_element.h"
#include "valuation.h"
#include "compositeelement.h"

int main(int argc, char* argv[])
{
    int result = Catch::Session().run(argc, argv);  //catch call
        
    std::string input;
    std::stack<SymbolicSquareMatrix> mystack;
    Valuation map;
    std::cout << "Welcome to use the Matrix Calculator! Write 'quit' to leave." << std::endl;
    std::cout << "Enter a matrix in the form of [[1,a][2,b]] or a valuation in the form of x=7." << std::endl;
    std::cout << "Write '+', '-' or '*' to calculate the two latest matrices together or '=' to evaluate the latest matrix." << std::endl << std::endl;
    
    do 
    {
        std::cout << "Give an input: " << std::endl;
        std::getline(std::cin, input);
        if(input == "quit")
        {
            std::cout << "Bye bye!" << std::endl;
        }
        else if(input == "")
        {
            std::cout << "Empty input not valid." << std::endl;
        }
        else if(input == "+" or input == "-" or input == "*" )
        {
            //take two from the top, make a new symbolicmatrix out of the result, print result and push it to the stack
            try {
                if(mystack.size() < 2)
                    throw std::invalid_argument{"Not enough matrices to calculate"};
                    
                auto x = mystack.top();
                mystack.pop();              //pop first to access the second
                auto y = mystack.top();
                mystack.pop(); 
               
                if(input == "+")
                {
                    SymbolicSquareMatrix z = x + y;
                    std::cout << z << std::endl;
                    mystack.push(z);
                }
                if(input == "-")
                {
                    SymbolicSquareMatrix z = x - y;
                    std::cout << z << std::endl;
                    mystack.push(z);
                }
                if(input == "*")
                {
                    SymbolicSquareMatrix z = x * y;
                    std::cout << z << std::endl;
                    mystack.push(z);
                }
            }
            catch(const std::exception& e) 
            {
                std::cout << e.what() << std::endl;
            }
         
        }
        else if(input == "=")
        {
           //evaluate the top one and print the result 
            auto x = mystack.top();
            try
            {
               std::cout << x.evaluate(map) << std::endl;
            }
            catch(const std::exception& e) 
            {
                std::cout << "All necessary values not in the map yet." << std::endl;
            }
           
        }
        else if(std::isalpha(input.at(0))) //if first char is a letter try to add an evaluation to the map
        {
            std::stringstream ss;
            char var;
            int val;
            std::string tail;
            try
            {
                ss << input; 

                char symbol = ss.peek();
                if(std::isalpha(symbol))
                    ss >> var;
                else if(!std::isalpha(symbol))
                    throw std::invalid_argument{"Not alpha!"};
                symbol = ss.peek();
                if(symbol == '=')
                    ss >> var;
                else if(symbol != '=')
                    throw std::invalid_argument{"Not '=' !"};
                symbol = ss.peek();
                if(std::isdigit(symbol) or symbol == '-')
                    ss >> val;             //if you try to do a=-a, it adds a=0
                else if(!std::isdigit(symbol))
                    throw std::invalid_argument{"Not digit!"};
                ss >> tail;

                if(tail != ""){
                    throw std::invalid_argument{"Tailing stuff!"};
                }
                
                map[input.at(0)] = val;
                std::cout << "Valuation " << input.at(0) << "=" << val << " added to map." << std::endl;
                
            }
            catch(const std::exception& e)
            {   
                std::cout << "Invalid valuation." << std::endl;               
            }
        }
        else
        {
            try
            {
                //try to read a new matrix, push it to the stack if okay
                mystack.push(SymbolicSquareMatrix{input});
            }
            catch(const std::exception& e) 
            {
                std::cout << "Error! Not squarematrix." << std::endl;
            }
        }
        
    }while(input != "quit");
    
    return result;
}
