#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>    //exceptions
#include "squarematrix.h"
#include "intelement.h"


SquareMatrix::SquareMatrix() : n{3}
{
    elements.resize(n, std::vector<IntElement>(n, IntElement()));   //3x3 zero matrix is the default
}                        
  
SquareMatrix::SquareMatrix(const std::string& s)
{
    elements = isSquareMatrix(s);           //throws occur inside the 'isSquareMatrix'-function
    n = elements.size();
} 

SquareMatrix::SquareMatrix(const SquareMatrix& m)
{
    elements = m.elements;
    n = m.n;
}

SquareMatrix& SquareMatrix::operator=(const SquareMatrix& m) 
{
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};
    
    elements = m.elements;
    n = m.n;
    return *this;
}

SquareMatrix SquareMatrix::transpose() const
{
    SquareMatrix matrix_t{*this};   //copy of matrix, to be transposed and returned later
    
    for(unsigned int i = 0; i < matrix_t.elements.size(); i++)      //'traditional' for loop
    {        
        for(unsigned int j = 0; j < matrix_t.elements[i].size(); j++)
        {
            matrix_t.elements[j][i] = this->elements[i][j];
        }
    }   
    return matrix_t;
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& m) 
{
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};
    
    auto cit = elements.begin();    
    auto cit_m = m.elements.begin();
      
    for(;cit != elements.end() and cit_m != m.elements.end(); cit++, cit_m++) //for loop done with iterators
    {    
        auto cit2 = cit->begin();
        auto cit2_m = cit_m->begin();
        
        for(;cit2 != cit->end() and cit2_m != cit_m->end(); cit2++, cit2_m++)
        {
            *cit2 += *cit2_m;
        }
    }   
    return *this;
}


SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& m) 
{
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};
    
    auto cit = elements.begin();
    auto cit_m = m.elements.begin();
      
    for(;cit != elements.end() and cit_m != m.elements.end(); cit++, cit_m++)
    {
        auto cit2 = cit->begin();
        auto cit2_m = cit_m->begin();
        
        for(;cit2 != cit->end() and cit2_m != cit_m->end(); cit2++, cit2_m++)
        {
            *cit2 -= *cit2_m;
        }
    }   
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& m)
{      
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};

    SquareMatrix zero{*this};        //temporary matrix to hold the result. a copy of 'this'-matrix initialized to zeros
    int i, j, k;
	for(i = 0; i < zero.n; i++)
	{
		for(j = 0; j < zero.n; j++)
		{
			zero.elements[i][j] = IntElement{0} ;
		}
	}
           
    for(i = 0; i < m.n; i++)
    {            
        for(j = 0; j < m.n; j++)
        {
            for(k = 0; k < m.n; k++)
            {
                zero.elements[i][j] += (this->elements[i][k] * m.elements[k][j]);
            }
        }
        
    } 
    *this = zero;
    return *this;  
}

bool SquareMatrix::operator==(const SquareMatrix& m) const 
{
    if(n != m.n)
        return false;  //no need to throw exception when you can just return false
     
    auto cit = elements.begin();
    auto cit_m = m.elements.begin();
      
    for(;cit != elements.end() and cit_m != m.elements.end(); cit++, cit_m++)
    {
        auto cit2 = cit->begin();
        auto cit2_m = cit_m->begin();
        
        for(;cit2 != cit->end() and cit2_m != cit_m->end(); cit2++, cit2_m++)
        {
            if(*cit2 == *cit2_m) continue;
            return false;
        }
    } 
    return true;
}


void SquareMatrix::print(std::ostream& os) const
{ 
    os << "[";
    for(auto& row : elements)     //range based for loop
    {
        os << "[";
        bool first = true;
        for(auto& col : row)
        {
            if(!first) os << ",";
            os << col.getVal();
            first = false;
        }
        os << "]";        
    }   
    os << "]" << std::endl;
}

std::string SquareMatrix::toString() const
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
            ss << col.getVal();
            first = false;
        }
        ss << "]";        
    }   
    ss << "]";
    return ss.str();
}

int SquareMatrix::get_n() const 
{
    return n;
}


//outside class operators
SquareMatrix operator+(const SquareMatrix& m1, const SquareMatrix& m2) 
{
    if(m1.get_n() != m2.get_n())
        throw std::invalid_argument{"Dimension mismatch!"};
    
    SquareMatrix sum{m1};
    sum += m2;
    return sum;
}

SquareMatrix operator-(const SquareMatrix& m1, const SquareMatrix& m2) 
{
    if(m1.get_n() != m2.get_n())
        throw std::invalid_argument{"Dimension mismatch!"};
    
    SquareMatrix minus{m1};
    minus -= m2;  
    return minus;
}

SquareMatrix operator*(const SquareMatrix& m1, const SquareMatrix& m2) 
{
    if(m1.get_n() != m2.get_n())
        throw std::invalid_argument{"Dimension mismatch!"};
    
    SquareMatrix mult{m1};
    mult *= m2;
    return mult;
}

std::ostream& operator<<(std::ostream& os, const SquareMatrix& m) 
{
    os << m.toString();
    return os;
}


std::vector<std::vector<IntElement> > isSquareMatrix(const std::string& in){
     
    std::vector<std::vector<IntElement> > matrix{};
    
    std::string tail;
    int list_count = 0;         //row count
    int num_count = 0;          //col count
    int prev_num_count = 0;     //to compare column lenghts
    std::stringstream ss;
    ss << in;
    char delim;
    
    ss >> delim;
    if(delim != '['){ //outermost left bracket
        throw std::invalid_argument{"Not squarematrix!"};
    }  
    ss >> delim;
    //loops this until delim == ']'  
    while(delim != ']'){
        list_count += 1;
        if(delim != '['){  
            throw std::invalid_argument{"Not squarematrix!"};
        }
        prev_num_count = num_count;
        num_count = 0;
        std::vector<IntElement> inner;
        while(delim != ']'){
            int num;
            ss >> num;
            if(!ss.good()){ 
                throw std::invalid_argument{"Not squarematrix!"};
            }
            else {
                num_count += 1;  //counts numbers
                inner.push_back(IntElement(num));   //pushes numbers to the matrix         
            }      
            ss >> delim;
            if(delim == ']'){
                break;
            }
            else if(delim != ','){
                throw std::invalid_argument{"Not squarematrix!"};
            }          
        }  
        matrix.push_back(inner);
        inner.clear();
        if(!(ss >> delim)){ //returns false if buffer is empty            
            throw std::invalid_argument{"Not squarematrix!"};
        }
        if(prev_num_count != 0 && num_count != prev_num_count){   //if rows don't match
            throw std::invalid_argument{"Not squarematrix!"};
        }
    }

    ss >> tail;
    if(tail != ""){
        throw std::invalid_argument{"Not squarematrix!"};
    }
     
    if(num_count != list_count){  //if rows != cols
        throw std::invalid_argument{"Not squarematrix!"};
    }
    return matrix;
} 

