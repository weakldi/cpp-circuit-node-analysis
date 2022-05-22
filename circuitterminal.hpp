
#ifndef CIRCUITTERMINAL
#define CIRCUITTERMINAL
#include "component.hpp"
#include "circuitnode.hpp"
#include "named.hpp"
#include "id.hpp"
#include "printable.hpp"
struct circuitterminal : named, printable, give_id<circuitterminal>
{
    
    circuitterminal(const component& p_component, std::string_view p_name);
    const component& m_component;
    std::ostream& print(std::ostream& out) const override;
    private:        
        friend struct component;
};

#else

struct circuitterminal;
#endif /* TERMILAN */
