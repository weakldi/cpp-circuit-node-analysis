#include "circuitnode.hpp"

NODE_HANDEL circuitnode::next_handel = 0;

circuitnode::circuitnode()
    :   named("NODE_" + std::to_string(circuitnode::next_handel)),
        give_id<circuitnode>(),
        m_handel(circuitnode::next_handel++),
        m_voltage_potential(std::nullopt)
    {}

circuitnode::circuitnode(std::string_view p_name) 
    :   named(p_name),
        m_handel(circuitnode::next_handel++)
    {}


void circuitnode::add_connection(const component& p_component, const circuitterminal& p_terminal){
    m_connections.push_back({p_component.get_handel(), p_terminal.get_handel()});
}

std::optional<std::pair<NODE_HANDEL, long double>> circuitnode::get_voltage() const{
    return m_voltage_potential;
}
void circuitnode::set_voltage_potential(const circuitnode& zero, long double voltage){
    m_voltage_potential = {{zero.get_handel(), voltage}};
}