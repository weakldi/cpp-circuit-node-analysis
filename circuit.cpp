#include "circuit.hpp"
#include <iostream>
circuit::circuit(std::string_view p_name): named(p_name), m_components{}, m_nodes{}, m_connections{}
{

};

void circuit::connect(NODE_HANDEL from, NODE_HANDEL to, std::tuple<COMPONENT_HANDEL, TERMINAL_HANDEL, TERMINAL_HANDEL> connection){
    auto node_pair = std::make_pair(from, to);
    m_connections.emplace(node_pair, connection);
};


void circuit::print() const{
    using std::cout;
    cout << m_name << "{\n";
    
    for(const auto& [connection_pair, component_tuple] : m_connections){
        auto [component, t1, t2] = component_tuple;
        cout    << "\t" << m_nodes.at(connection_pair.first)->get_name() << " --> {";
        cout    << m_components.at(component)->get_terminals().at(t1)->get_name()  << ", ";
        cout    << m_components.at(component)->get_terminals().at(t2)->get_name()  << "} ";
        cout    << m_components.at(component)->get_name() << " --> ";
        cout    << m_nodes.at(connection_pair.second)->get_name() << "\n";
    }
    cout << "}" << std::endl;

}