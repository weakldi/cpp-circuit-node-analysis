#include "circuitnode.hpp"

NODE_HANDEL circuitnode::next_handel = 0;

circuitnode::circuitnode()
    :   named("NODE_" + std::to_string(circuitnode::next_handel)),
        m_handel(circuitnode::next_handel++)
      
    {}

circuitnode::circuitnode(std::string_view p_name) 
    :   named(p_name),
        m_handel(circuitnode::next_handel++)
    {}


void circuitnode::add_connection(const component& p_component, const circuitterminal& p_terminal){
    m_connections.push_back({p_component.get_handel(), p_terminal.get_handel()});
}