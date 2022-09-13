
#include "element.h"

std::ostream& operator<<(std::ostream& os, const Element& ie)
{   
    os << ie.toString();
    return os;
}




