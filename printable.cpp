#include "printable.hpp"

std::ostream& operator<<(std::ostream& out, const printable& lhs){
    return lhs.print(out);
}
