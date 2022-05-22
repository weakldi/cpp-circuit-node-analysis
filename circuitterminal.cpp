#include "circuitterminal.hpp"

circuitterminal::circuitterminal(const component& p_component, std::string_view p_name) 
    : named(p_name), give_id<circuitterminal>(),
      m_component(p_component)
    {}