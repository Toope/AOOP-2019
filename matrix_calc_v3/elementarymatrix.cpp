#include "elementarymatrix.h"

//from SYMBOLIC
template<>
void SymbolicSquareMatrix::isSquareMatrix(const std::string& in){ 
    
    std::string tail;
    int list_count = 0;         //row count
    int el_count = 0;          //col count
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
            
            else if(std::isdigit(symbol) or symbol == '-') {   //and digits
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
    }

    ss >> tail;
    if(tail != ""){
        throw std::invalid_argument{"Not SymbolicSquareMatrix! Tailing stuff!"};
    }
     
    if(el_count != list_count){  //if rows != cols
        throw std::invalid_argument{"Not SymbolicSquareMatrix! Rows and cols don't match!"};
    }
} 

template<>
SymbolicSquareMatrix SymbolicSquareMatrix::operator+(const SymbolicSquareMatrix& m) const 
{
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};
    
    SymbolicSquareMatrix res{};
    res.n = m.n;
    std::vector<unique_elem_ptr> inner;
    
    auto cit = elements.begin();    
    auto cit_m = m.elements.begin();
      
    for(;cit != elements.end() and cit_m != m.elements.end(); cit++, cit_m++)
    {    
        auto cit2 = cit->begin();
        auto cit2_m = cit_m->begin();
        
        for(;cit2 != cit->end() and cit2_m != cit_m->end(); cit2++, cit2_m++)
        {
            CompositeElement comp{**cit2, **cit2_m, std::plus<int>{},'+'};
            inner.push_back(unique_elem_ptr(comp.clone()));          //creates new symbolicmatrix consisting of compositeelements
            
        }
        res.elements.push_back(std::move(inner));
    }  
    
    return res; 
}
template<>
SymbolicSquareMatrix SymbolicSquareMatrix::operator-(const SymbolicSquareMatrix& m) const 
{
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};
    
    SymbolicSquareMatrix res{};
    res.n = m.n;
    std::vector<unique_elem_ptr> inner;
    
    auto cit = elements.begin();    
    auto cit_m = m.elements.begin();
      
    for(;cit != elements.end() and cit_m != m.elements.end(); cit++, cit_m++)
    {    
        auto cit2 = cit->begin();
        auto cit2_m = cit_m->begin();
        
        for(;cit2 != cit->end() and cit2_m != cit_m->end(); cit2++, cit2_m++)
        {
            CompositeElement comp{**cit2, **cit2_m, std::minus<int>{},'-'};
            inner.push_back(unique_elem_ptr(comp.clone()));          //creates new symbolicmatrix consisting of compositeelements
            
        }
        res.elements.push_back(std::move(inner));
    }  
    
    return res; 
}
template<>
SymbolicSquareMatrix SymbolicSquareMatrix::operator*(const SymbolicSquareMatrix& m) const
{
    if(n != m.n)
        throw std::invalid_argument{"Dimension mismatch!"};

    SymbolicSquareMatrix zero{*this}; 

    unsigned int i, j, k;
	for(i = 0; i < zero.n; i++)
	{
		for(j = 0; j < zero.n; j++)
		{
			zero.elements.at(i).at(j) = unique_elem_ptr(new IntElement(0));
		}
	}
           
    for(i = 0; i < m.n; i++)
    {            
        for(j = 0; j < m.n; j++)
        {
            for(k = 0; k < m.n; k++)
            {       
                CompositeElement comp{(*this->elements.at(i).at(k)), (*m.elements.at(k).at(j)), std::multiplies<int>{}, '*'}; //composite *
                CompositeElement comp2{*zero.elements.at(i).at(j), comp, std::plus<int>{}, '+'};  //composite +
                zero.elements.at(i).at(j) = unique_elem_ptr(comp2.clone());             
            }
        }
        
    }

    return zero;
}
template<>
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
            inner.push_back(unique_elem_ptr((*e).clone()));
        }
        elements.push_back(std::move(inner));
    }
    
    
    return *this;
}
template<>
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
            inner.push_back(std::move(unique_elem_ptr((*e).clone())));
            e = nullptr;
        }
        elements.push_back(std::move(inner));
    }
    
    m.elements.clear();  //leaves only empty brackets here '[]'
    
    return *this;
}
template<>
SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const
{
    SymbolicSquareMatrix m{*this};   //copy of matrix, to be transposed and returned later
    
    for(unsigned int i = 0; i < m.elements.size(); i++)
    {        
        for(unsigned int j = 0; j < m.elements.at(0).size(); j++)
        {
            m.elements.at(j).at(i) = unique_elem_ptr((*this->elements.at(i).at(j)).clone());
        }
    } 

    return  m;
}

template<>
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


//from CONCRETE ************************************************************************************************************************************************************

template<> 
void ConcreteSquareMatrix::isSquareMatrix(const std::string& in)
{ 
    
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

template<>
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
template<>
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
template<>
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

template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& m) 
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
            *(*cit2) += *(*cit2_m);
        }
    }   
    return *this;
}

template<>
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
template<>
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
