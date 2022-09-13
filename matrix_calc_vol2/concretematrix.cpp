
#include "concretematrix.h"


ConcreteSquareMatrix::ConcreteSquareMatrix() : n{0}
{
}                        
  
ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string& s)
{
    isConcreteSquareMatrix(s);           //throws occur inside the 'isConcreteSquareMatrix'-function
    n = elements.size();
} 

ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& m)
{
    n = m.n;
    std::vector<unique_intelem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back(unique_intelem_ptr(new IntElement(*e)));
        }
        elements.push_back(std::move(inner));
    }
}

ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& m)
{   
    n = m.n;
    
    elements.clear();
    
    std::vector<unique_intelem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back(std::move(unique_intelem_ptr(new IntElement(*e))));
            e = nullptr;
        }
        elements.push_back(std::move(inner));
    }
    
    m.elements.clear();  //leaves only empty brackets here '[]'
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix& m)
{
    
    if(&m == this)
        return *this;
    
    n = m.n;
    
    elements.clear();
    
    std::vector<unique_intelem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back(unique_intelem_ptr(new IntElement(*e)));
        }
        elements.push_back(std::move(inner));
    }
    
    
    return *this;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(ConcreteSquareMatrix&& m)
{    
    if(&m == this)
        return *this;
    
    n = m.n;
    
    elements.clear();
    
    std::vector<unique_intelem_ptr> inner;
    for(auto& vec : m.elements) 
    {   
        for(auto& e : vec) 
        {
            inner.push_back(std::move(unique_intelem_ptr(new IntElement(*e))));
            e = nullptr;
        }
        elements.push_back(std::move(inner));
    }
    
    m.elements.clear();  //leaves only empty brackets here '[]'
    
    return *this;
}

ConcreteSquareMatrix ConcreteSquareMatrix::transpose() const
{
    ConcreteSquareMatrix m{*this};   //copy of matrix, to be transposed and returned later
    
    for(unsigned int i = 0; i < m.elements.size(); i++)
    {        
        for(unsigned int j = 0; j < m.elements.at(0).size(); j++)
        {
            m.elements.at(j).at(i) = unique_intelem_ptr(new IntElement(*this->elements.at(i).at(j)));
        }
    } 

    return  m;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& m) 
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
            *(*cit2) += *(*cit2_m);
        }
    }   
    return *this;
}


ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& m) 
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
            *(*cit2) -= *(*cit2_m);
        }
    }   
    return *this;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& m)
{      
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};

    ConcreteSquareMatrix zero{*this};        //temporary matrix to hold the result. a copy of 'this'-matrix initialized to zeros
    unsigned int i, j, k;
	for(i = 0; i < zero.n; i++)
	{
		for(j = 0; j < zero.n; j++)
		{
			zero.elements.at(i).at(j) = unique_intelem_ptr(new IntElement(0));
		}
	}
           
    for(i = 0; i < m.n; i++)
    {            
        for(j = 0; j < m.n; j++)
        {
            for(k = 0; k < m.n; k++)
            {       

                *zero.elements.at(i).at(j) += (*this->elements.at(i).at(k)) * (*m.elements.at(k).at(j));
            }
        }
        
    } 
    *this = zero;
    return *this;  
}

bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m) const 
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
            if(*(*cit2) == *(*cit2_m)) continue;
            return false;
        }
    } 
    return true;
}


void ConcreteSquareMatrix::print(std::ostream& os) const
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

std::string ConcreteSquareMatrix::toString() const
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

int ConcreteSquareMatrix::get_n() const 
{
    return n;
}


//outside class operators
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2) 
{
    if(m1.get_n() != m2.get_n())
        throw std::invalid_argument{"Dimension mismatch!"};
    
    ConcreteSquareMatrix sum{m1};
    sum += m2;
    return sum;
}

ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2) 
{
    if(m1.get_n() != m2.get_n())
        throw std::invalid_argument{"Dimension mismatch!"};
    
    ConcreteSquareMatrix minus{m1};
    minus -= m2;  
    return minus;
}

ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2) 
{
    if(m1.get_n() != m2.get_n())
        throw std::invalid_argument{"Dimension mismatch!"};
    
    ConcreteSquareMatrix mult{m1};
    mult *= m2;
    return mult;
}

std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m) 
{
    os << m.toString();
    return os;
}


void ConcreteSquareMatrix::isConcreteSquareMatrix(const std::string& in){  //moved this inside the class
    
    std::string tail;
    int list_count = 0;         //row count
    int num_count = 0;          //col count
    int prev_num_count = 0;     //to compare column lenghts
    std::stringstream ss;
    ss << in;
    char delim;
    
    ss >> delim;
    if(delim != '['){ //outermost left bracket
        throw std::invalid_argument{"Not ConcreteSquareMatrix! Delim not '[' !"};
    }  
    ss >> delim;
    //loops this until delim == ']'  
    while(delim != ']'){
        list_count += 1;
        if(delim != '['){  
            throw std::invalid_argument{"Not ConcreteSquareMatrix! Delim not '[' !"};
        }
        prev_num_count = num_count;
        num_count = 0;
        std::vector<unique_intelem_ptr> inner;
        while(delim != ']'){
            int num;
            ss >> num;
            if(!ss.good()){ 
                throw std::invalid_argument{"Not ConcreteSquareMatrix! Not 'good()' !"};
            }
            else {
                num_count += 1;  //counts numbers
                inner.push_back(unique_intelem_ptr(new IntElement(num)));   //pushes pointers to the matrix         
            }      
            ss >> delim;
            if(delim == ']'){
                break;
            }
            else if(delim != ','){
                throw std::invalid_argument{"Not ConcreteSquareMatrix! Delim not ',' !"};
            }          
        }  
        elements.push_back(std::move(inner));
        inner.clear();
        if(!(ss >> delim)){ //returns false if buffer is empty            
            throw std::invalid_argument{"Not ConcreteSquareMatrix! Buffer empty!"};
        }
        if(prev_num_count != 0 && num_count != prev_num_count){   //if rows don't match
            throw std::invalid_argument{"Not ConcreteSquareMatrix! Rows and previous rows don't match!"};
        }
    }

    ss >> tail;
    if(tail != ""){
        throw std::invalid_argument{"Not ConcreteSquareMatrix! Tailing stuff!"};
    }
     
    if(num_count != list_count){  //if rows != cols
        throw std::invalid_argument{"Not ConcreteSquareMatrix! Rows and cols don't match!"};
    }
} 



