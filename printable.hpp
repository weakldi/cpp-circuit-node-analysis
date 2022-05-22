#ifndef PRINTABLE
#define PRINTABLE
#include <iostream>
struct printable
{
    virtual std::ostream& print(std::ostream& out = std::cout) const = 0;
};

std::ostream& operator<<(std::ostream& out, const printable& lhs);
#endif