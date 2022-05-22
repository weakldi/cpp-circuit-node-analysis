
#ifndef CIRCUITTERMINAL
#define CIRCUITTERMINAL
#include "component.hpp"
#include "circuitnode.hpp"
#include "named.hpp"
#include "id.hpp"

struct circuitterminal : named, give_id<circuitterminal>
{
    
    circuitterminal(const component& p_component, std::string_view p_name);
    const component& m_component;
   
    private:        
        friend struct component;
};

#else

struct circuitterminal;
#endif /* TERMILAN */
