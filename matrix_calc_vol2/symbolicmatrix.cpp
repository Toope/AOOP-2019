
#include "symbolicmatrix.h"
 
SymbolicSquareMatrix::SymbolicSquareMatrix() : n{0}
{
}                        
  
SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& s)
{
    isSymbolicSquareMatrix(s);           //throws occur inside the 'isSymbolicSquareMatrix'-function
    n = elements.size();
} 


SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& m)
{
    n = m.n;
    std::vector<unique_elem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back((*e).clone());
        }
        elements.push_back(std::move(inner));
    }
}

SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& m)
{   
    n = m.n;
    
    elements.clear();
    
    std::vector<unique_elem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back(std::move((*e).clone()));
            e = nullptr;
        }
        elements.push_back(std::move(inner));
    }
    
    m.elements.clear();  //leaves only empty brackets here '[]'
}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix& m)
{
    
    if(&m == this)
        return *this;
    
    n = m.n;
    
    elements.clear();
    
    std::vector<unique_elem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back((*e).clone());
        }
        elements.push_back(std::move(inner));
    }
    
    
    return *this;
}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix&& m)
{    
    if(&m == this)
        return *this;
    
    n = m.n;
    
    elements.clear();
    
    std::vector<unique_elem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back(std::move((*e).clone()));
            e = nullptr;
        }
        elements.push_back(std::move(inner));
    }
    
    m.elements.clear();  //leaves only empty brackets here '[]'
    
    return *this;
}

SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const
{
    SymbolicSquareMatrix m{*this};   //copy of matrix, to be transposed and returned later
    
    for(unsigned int i = 0; i < m.elements.size(); i++)
    {        
        for(unsigned int j = 0; j < m.elements.at(0).size(); j++)
        {
            m.elements.at(j).at(i) = (*this->elements.at(i).at(j)).clone();
        }
    } 

    return  m;
}


bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m) const 
{
    if(n != m.n)
        return false;  //no need to throw exception when you can just return false
     
    return (this->toString() == m.toString());  //easy to compare strings
}


void SymbolicSquareMatrix::print(std::ostream& os) const
{ 
    os << "[";
    for(auto& row : elements)     //range based for loop
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
}

std::string SymbolicSquareMatrix::toString() const
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
}


ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& val) const 
{   
    SymbolicSquareMatrix zero{*this};   //make a copy of this to hold the result 
    zero.elements.clear();
    
    std::vector<unique_elem_ptr> inner;
    for(auto& row : elements)
    {
        for(auto& col : row)
        {
            inner.push_back(unique_intelem_ptr(new IntElement((*col).evaluate(val))));
        }
        zero.elements.push_back(std::move(inner));  //push the evaluated values into zero
    }
    
    ConcreteSquareMatrix res{zero.toString()};   //make symbolic zero change into concrete res using toString()
    return res; 
}


//outside class operators

std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& m) 
{
    os << m.toString();
    return os;
}

void SymbolicSquareMatrix::isSymbolicSquareMatrix(const std::string& in){ 
    
    std::string tail;
    int list_count = 0;         //row count
    int el_count = 0;          //col count
    int prev_el_count = 0;     //to compare column lenghts
    std::stringstream ss;
    ss << in;
    char delim;
    int num;
    char cha;

    
    ss >> delim;
    if(delim != '['){ //outermost left bracket
        throw std::invalid_argument{"Not SymbolicSquareMatrix! Delim not '[' !"};
    }  
    ss >> delim;
    //loops this until delim == ']'  
    while(delim != ']'){
        list_count += 1;
        if(delim != '['){  
            throw std::invalid_argument{"Not SymbolicSquareMatrix! Delim not '[' !"};
        }
        prev_el_count = el_count;
        el_count = 0;
        std::vector<unique_elem_ptr> inner;
        while(delim != ']'){
            
            char symbol = ss.peek();   //peeks the next char/int
                                  
            if(std::isalpha(symbol))   //allows letters
            {           
                ss >> cha;
                el_count += 1; 
                inner.push_back(unique_elem_ptr(new VariableElement(cha)));
            }
            
            else if(std::isdigit(symbol)) {   //and digits
                ss >> num;
                el_count += 1; 
                inner.push_back(unique_elem_ptr(new IntElement(num)));   //pushes pointers to the matrix         
            }             
            else if(!ss.good()){ 
                throw std::invalid_argument{"Not SymbolicSquareMatrix! Not 'good()' !"};
            }            
            ss >> delim;
            if(delim == ']'){
                break;
            }
            else if(delim != ','){
                throw std::invalid_argument{"Not SymbolicSquareMatrix! Delim not ',' !"};
            }          
        }  
        elements.push_back(std::move(inner));
        inner.clear();
        if(!(ss >> delim)){ //returns false if buffer is empty            
            throw std::invalid_argument{"Not SymbolicSquareMatrix! Buffer empty!"};
        }
        if(prev_el_count != 0 && el_count != prev_el_count){   //if rows don't match
            throw std::invalid_argument{"Not SymbolicSquareMatrix! Rows and previous rows don't match!"};
        }
    }

    ss >> tail;
    if(tail != ""){
        throw std::invalid_argument{"Not SymbolicSquareMatrix! Tailing stuff!"};
    }
     
    if(el_count != list_count){  //if rows != cols
        throw std::invalid_argument{"Not SymbolicSquareMatrix! Rows and cols don't match!"};
    }
} 


