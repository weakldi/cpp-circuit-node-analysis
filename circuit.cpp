#include "circuit.hpp"
#include <iostream>
#include <algorithm>
#include "math.hpp"
#include "voltagesource.hpp"
struct voltagesource;
circuit::circuit(std::string_view p_name): named(p_name), m_components{}, m_nodes{}, m_connections{}
{

};

void circuit::connect(id_<circuitnode> from, id_<circuitnode> to, std::tuple<COMPONENT_HANDEL, id_<circuitterminal>, id_<circuitterminal>> connection){
    auto node_pair = std::make_pair(from, to);
    m_connections.emplace(node_pair, connection);
};


void circuit::connect(circuitnode& from, circuitnode& to, std::tuple<const component&, id_<circuitterminal>, id_<circuitterminal>> connection){
    auto& [comp, t1, t2] = connection;
    connect(from, to, {comp.get_handel(), t1,t2});
}
void circuit::connect(circuitnode& from, circuitnode& to, const bipole& component){
    connect(from, to, {component.get_handel(), component.get_negative(),component.get_positive()});
}

void circuit::print() const{
    using std::cout;
    cout << m_name << "{\n";
    
    for(const auto& [connection_pair, component_tuple] : m_connections){
        /*
        const auto [component, t1, t2] = component_tuple;
        cout    << "\t" << m_nodes.at(connection_pair.first)->get_name() << " --> {";
        cout    << m_components.at(component)->get_terminals().at(t1)->get_name()  << ", ";
        cout    << m_components.at(component)->get_terminals().at(t2)->get_name()  << "} ";
        cout    << m_components.at(component)->get_name() << " --> ";
        cout    << m_nodes.at(connection_pair.second)->get_name() << "\n";*/
    }
    cout << "}" << std::endl;

}
std::optional<connection_t> circuit::has_connections(const circuitnode& from,const circuitnode to) const{
    {
        const auto& iter = m_connections.find({from, to});
        if(iter != m_connections.end()) return {{from, to}};
    }
    {
        const auto& iter = m_connections.find({to, from});
        if(iter != m_connections.end()) {
            return {{to, from}};
        } 
    }
    return std::nullopt;
}

void circuit::knotenpotenzial(id_<circuitnode> zero_handel) const{
    using std::cout;
    
    circuitnode& zero = *(m_nodes.at(zero_handel));
    std::vector<std::reference_wrapper<circuitnode>> nodes;
    matrix<long double> mat(m_nodes.size()-1);
    std::vector<long double> current_vec(m_nodes.size()-1);

    for(auto& [key, value] : m_nodes){
        if(key != zero.id())
            nodes.push_back(std::ref(*(value.get())));
    }

    for(int i = 0; i < nodes.size() ; i++){
        const auto& node1 = nodes[i].get();

        auto lamda = [this, i](const component& comp, id_<circuitterminal> t1, id_<circuitterminal> t2, matrix<long double>& mat, std::vector<long double>& current_vec){
            comp.add_coefficents_zero(mat, current_vec, i, t1,t2);
        };
        auto func = std::bind(lamda,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, std::ref(mat), std::ref(current_vec) );
        for_each_connection(node1, zero, func);


        for(int j = i+1; j < nodes.size(); j++){
            
            const auto& node2 = nodes[j].get();
            auto lamda = [this, i, j](const component& comp, id_<circuitterminal> t1, id_<circuitterminal> t2, matrix<long double>& mat, std::vector<long double>& current_vec){
                comp.add_coefficents(mat, current_vec, i,j, t1,t2);
            };
            auto func = std::bind(lamda,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, std::ref(mat), std::ref(current_vec) );
            for_each_connection(node1, node2, func);
        }
    }
    /*
    for(int i = 0; i < mat.rang; i++){
        for(int j = 0; j < mat.rang; j++){
            cout << mat(i,j) << ", ";
        }
        cout << "*U_" << i << " = "<< current_vec[i] << std::endl;
    }*/

    auto u_vec = gauss(mat, current_vec);
    zero.set_voltage_potential(zero, 0);
    for(int i = 0; i < nodes.size(); i++){
        nodes[i].get().set_voltage_potential(zero, u_vec[i]);
    }

    
}