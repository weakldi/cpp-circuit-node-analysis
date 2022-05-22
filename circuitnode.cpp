#include "circuitnode.hpp"


circuitnode::circuitnode()
    :   named("NODE_" + std::to_string(id_<circuitnode>::next_id)),
        give_id<circuitnode>(),
        m_voltage_potential(std::nullopt)
    {}

circuitnode::circuitnode(std::string_view p_name) 
    :   named(p_name)
    {}


void circuitnode::add_connection(const component& p_component, const circuitterminal& p_terminal){
    m_connections.push_back({p_component.id(), p_terminal.id()});
}

std::optional<std::pair<id_<circuitnode>, long double>> circuitnode::get_voltage() const{
    return m_voltage_potential;
}
void circuitnode::set_voltage_potential(const circuitnode& zero, long double voltage){
    m_voltage_potential = {{zero.id(), voltage}};
}