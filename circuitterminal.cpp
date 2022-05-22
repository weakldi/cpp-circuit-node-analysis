#include "circuitterminal.hpp"
TERMINAL_HANDEL circuitterminal::next_handel = 0;
circuitterminal::circuitterminal(const component& p_component, std::string_view p_name) 
    : named(p_name), give_id<circuitterminal>(), m_component(p_component), 
      m_handel(circuitterminal::next_handel++)
    {}