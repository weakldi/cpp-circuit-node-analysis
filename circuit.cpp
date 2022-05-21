#include "circuit.hpp"
#include <iostream>
#include "math.hpp"
circuit::circuit(std::string_view p_name): named(p_name), m_components{}, m_nodes{}, m_connections{}
{

};

void circuit::connect(NODE_HANDEL from, NODE_HANDEL to, std::tuple<COMPONENT_HANDEL, TERMINAL_HANDEL, TERMINAL_HANDEL> connection){
    auto node_pair = std::make_pair(from, to);
    m_connections.emplace(node_pair, connection);
};


void circuit::connect(circuitnode& from, circuitnode to, std::tuple<const component&, TERMINAL_HANDEL, TERMINAL_HANDEL> connection){
    auto& [comp, t1, t2] = connection;
    connect(from.get_handel(), to.get_handel(), {comp.get_handel(), t1,t2});
}
void circuit::connect(circuitnode& from, circuitnode to, const bipole& component){
    connect(from.get_handel(), to.get_handel(), {component.get_handel(), component.get_negative(),component.get_positive()});
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
        const auto& iter = m_connections.find({from.get_handel(), to.get_handel()});
        if(iter != m_connections.end()) return {{from.get_handel(), to.get_handel()}};
    }
    {
        const auto& iter = m_connections.find({to.get_handel(), from.get_handel()});
        if(iter != m_connections.end()) {
            return {{to.get_handel(), from.get_handel()}};
        } 
    }
    return std::nullopt;
}

void circuit::knotenpotenzial(const circuitnode& zero) const{
    using std::cout;

    cout << "Rang Matrix: " << m_nodes.size() - 1 << "\n";
    
    std::unordered_map<NODE_HANDEL, uint64_t> index_map;
    
    matrix<long double> mat(m_nodes.size() - 1);
    std::vector<long double> current_vec(m_nodes.size() - 1);
    uint64_t i = 0;
    for(const auto& [key_from, node1] : m_nodes){
        uint64_t j = 0;
        if(key_from == zero.get_handel()) continue;
        
        for(const auto& [key_to, node2] : m_nodes){
            

           
            
            const auto connection = has_connections(*node1, *node2);
            if(connection){
                
                auto [begin,end] = m_connections.equal_range(connection.value());
                auto [from, to] = connection.value();
                for(auto it = begin; it != end; it++){
                    auto [component, t1, t2] = *(it->second);
                    mat(i,i) += 1.0/m_components.at(component)->get_resistance(t1,t2);
                     //check for switch of direction
                    if(from != node1->get_handel()){
                        std::swap(t1,t2);
                    }
                    cout <<  m_components.at(component)->get_name() << node1->get_name() << " " << node2->get_name() << " I="<< m_components.at(component)->get_current(t1,t2) << "\n";
                    current_vec[i] += m_components.at(component)->get_current(t1,t2); 
                    if(key_to == zero.get_handel()) continue;
                    mat(i,j)  -= 1.0/m_components.at(component)->get_resistance(t1,t2);
                    
                }
               
                
                if(key_to == zero.get_handel()) continue;
                j++;
            }else{
                if(key_to == zero.get_handel()) continue;
                j++;
               // std::cout << "    0   , ";
            }
            
            
        }
        std::cout << "\n";
        i++;
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << mat(i,j) << ", ";
        }
        cout <<  current_vec[i] << std::endl;
    }

    auto u_vec = gauss(mat, current_vec);


}