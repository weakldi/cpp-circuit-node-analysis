
#ifndef CIRCUITTERMINAL
#define CIRCUITTERMINAL
#include "component.hpp"
#include "circuitnode.hpp"
#include "named.hpp"
#include "id.hpp"

typedef int TERMINAL_HANDEL;
struct circuitterminal : named, give_id<circuitterminal>
{
    
    circuitterminal(const component& p_component, std::string_view p_name);
    const component& m_component;
    TERMINAL_HANDEL get_handel() const {return m_handel;}
    private:
       
        
        const TERMINAL_HANDEL m_handel;
        static TERMINAL_HANDEL next_handel;

        friend struct component;
};

#else
typedef int TERMINAL_HANDEL;
struct circuitterminal;
#endif /* TERMILAN */
