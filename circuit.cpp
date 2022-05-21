#include "circuit.hpp"
#include <iostream>
#include <algorithm>
#include "math.hpp"
#include "voltagesource.hpp"
struct voltagesource;
circuit::circuit(std::string_view p_name): named(p_name), m_components{}, m_nodes{}, m_connections{}
{

};

void circuit::connect(NODE_HANDEL from, NODE_HANDEL to, std::tuple<COMPONENT_HANDEL, TERMINAL_HANDEL, TERMINAL_HANDEL> connection){
    auto node_pair = std::make_pair(from, to);
    m_connections.emplace(node_pair, connection);
};


void circuit::connect(circuitnode& from, circuitnode& to, std::tuple<const component&, TERMINAL_HANDEL, TERMINAL_HANDEL> connection){
    auto& [comp, t1, t2] = connection;
    connect(from.get_handel(), to.get_handel(), {comp.get_handel(), t1,t2});
}
void circuit::connect(circuitnode& from, circuitnode& to, const bipole& component){
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

void circuit::knotenpotenzial2(NODE_HANDEL zero_handel) const{
    using std::cout;
    
    circuitnode& zero = *(m_nodes.at(zero_handel));
    std::vector<std::reference_wrapper<circuitnode>> nodes;
    matrix<long double> mat(m_nodes.size()-1);
    std::vector<long double> current_vec(m_nodes.size()-1);

    for(auto& [key, value] : m_nodes){
        if(key != zero_handel)
            nodes.push_back(std::ref(*(value.get())));
    }

    for(int i = 0; i < nodes.size() ; i++){
        const auto& node1 = nodes[i].get();

        auto lamda = [this, i](const component& comp, TERMINAL_HANDEL t1, TERMINAL_HANDEL t2, matrix<long double>& mat, std::vector<long double>& current_vec){
            comp.add_coefficents_zero(mat, current_vec, i, t1,t2);
        };
        auto func = std::bind(lamda,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3, std::ref(mat), std::ref(current_vec) );
        for_each_connection(node1, zero, func);


        for(int j = i+1; j < nodes.size(); j++){
            
            const auto& node2 = nodes[j].get();
            auto lamda = [this, i, j](const component& comp, TERMINAL_HANDEL t1, TERMINAL_HANDEL t2, matrix<long double>& mat, std::vector<long double>& current_vec){
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


void circuit::knotenpotenzial(NODE_HANDEL zero_handel) const{
    using std::cout;

    cout << "Rang Matrix: " << m_nodes.size() -1 << "\n";
    
    circuitnode& zero = *(m_nodes.at(zero_handel));
    std::unordered_map<NODE_HANDEL, uint64_t> index_map;
    
    matrix<long double> mat(m_nodes.size()-1);
    std::vector<long double> current_vec(m_nodes.size()-1);
    std::vector<std::reference_wrapper<circuitnode>> nodes;
    nodes.push_back(std::ref(zero));
    
    uint64_t i = 0;
    for(const auto& [key_from, node1] : m_nodes){
        uint64_t j = 0;
        if(key_from == zero.get_handel()) continue;
        nodes.push_back(std::ref(*node1));
        for(const auto& [key_to, node2] : m_nodes){

            const auto connection = has_connections(*node1, *node2);
            if(connection){
                
                auto [begin,end] = m_connections.equal_range(connection.value());
                auto [from, to] = connection.value();
                //TODO: make function get_coefficients for component
                for(auto it = begin; it != end; it++){
                    auto [component, t1, t2] = *(it->second);
                    //check for switch of direction
                    if(from != node1->get_handel()){
                            std::swap(t1,t2);
                    }

                    auto resistance = m_components.at(component)->get_resistance(t1,t2);
                    auto voltage    = m_components.at(component)->get_voltage(t1,t2);
                    auto current    = m_components.at(component)->get_current(t1,t2);
                    //m_components.at(component)->add_coefficents(mat, i,j, t1,t2);
                    //handel ideal voltage sources and short circuits
                    if(resistance == 0 && voltage != 0){ 
                        uint64_t new_size = mat.rang + 1;
                        mat.resize(new_size);
                        current_vec.resize(new_size);
                    
                        
                        //Calculate indeces for the voltage source
                        int indexFrom = i;
                        mat(new_size - 1, i) = 1;
                        mat(i, new_size - 1) = 1;
                        if(key_to != zero.get_handel()) 
                        {
                            int indexTo = j;
                            mat(new_size - 1, j) = -1;
                            mat(j, new_size - 1) = -1;
                        }
                       
                        auto voltage = m_components.at(component)->get_voltage(t1,t2);
                        current_vec[new_size - 1] = voltage;
                    }
                    // Normal voltage sources and resistors
                    else{
                        cout <<  m_components.at(component)->get_name() << node1->get_name() << " " << node2->get_name() << " I="<< m_components.at(component)->get_current(t1,t2) << "\n";
                        current_vec[i] += current; 
                        
                        mat(i,i) += 1.0/resistance;
                        
                        
                        if(key_to == zero.get_handel()) continue;
                        mat(i,j)  -= 1.0/resistance;
                    }
                   
                    
                }
               
                
                if(key_to == zero.get_handel()) continue;
                j++;
            }else{
                if(key_to == zero.get_handel()) continue;
                j++;
            }
            
            
        }

        i++;
    }
    /*
    for(int i = 0; i < mat.rang; i++){
        for(int j = 0; j < mat.rang; j++){
            cout << mat(i,j) << ", ";
        }
        cout << "*U_" << i << " = "<< current_vec[i] << std::endl;
    }*/

    auto u_vec = gauss(mat, current_vec);
    nodes[0].get().set_voltage_potential(zero, 0);
    for(int i = 1; i < nodes.size(); i++){
        nodes[i].get().set_voltage_potential(zero, u_vec[i-1]);
    }


}