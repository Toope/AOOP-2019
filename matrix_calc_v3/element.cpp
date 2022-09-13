
#include "element.h"

std::ostream& operator<<(std::ostream& os, const Element& ie)
{   
    os << ie.toString();
    return os;
}

bool operator==(const Element& e1, const Element& e2) 
{
    return(e1.toString() == e2.toString());
}




