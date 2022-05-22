#include "voltagesource.hpp"
#include <iostream>

voltagesource::voltagesource(std::string_view p_name, double p_voltage, double p_resistace)
    :   resistance(p_name, p_resistace), m_voltage(p_voltage)
    {}

double voltagesource::get_current(id_<circuitterminal> from, id_<circuitterminal> to) const {
    return get_voltage(from, to) / m_resistance;
}

double voltagesource::get_voltage(id_<circuitterminal> from, id_<circuitterminal> to) const {
    if(from == to) return 0;
    
    if(from == get_negative() && to == get_positive()){
        return  -m_voltage;
    }else{
        return  m_voltage;
    }
}

void   voltagesource::add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,id_<circuitterminal> from, id_<circuitterminal> to) const {
    A(i,j) -= 1/m_resistance;
    A(j,i) -= 1/m_resistance;
    A(i,i) += 1/m_resistance;
    A(j,j) += 1/m_resistance;
    if(m_resistance == 0){ // ideal source
        uint64_t new_size = A.rang + 1;
        A.resize(new_size);
        b.resize(new_size);

        A(new_size - 1, i) = 1;
        A(i, new_size - 1) = 1;
        //if(key_to != zero.get_handel()) 
        {
            A(new_size - 1, j) = -1;
            A(j, new_size - 1) = -1;
        }
                       
                        
        b[new_size - 1] = get_voltage(from, to);
    }else{
        
        b[i] += get_current(from, to);
    }
    
}

void   voltagesource::add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,id_<circuitterminal> from, id_<circuitterminal> to)   const{
    if(m_resistance == 0){ // ideal source
        uint64_t new_size = A.rang + 1;
        A.resize(new_size);
        b.resize(new_size);

        A(new_size - 1, i) = 1;
        A(i, new_size - 1) = 1;   
        b[new_size - 1] = get_voltage(from, to);
    }else{
       
        A(i,i) += 1/m_resistance;
        b[i]   += get_current(from, to);
    }
}