#include "currentsource.hpp"
#include <iostream>

currentsource::currentsource(std::string_view p_name, double p_current, double p_resistace)
    :   resistance(p_name, p_resistace), m_current(p_current)
    {}

double currentsource::get_current(id_<circuitterminal> from, id_<circuitterminal> to) const {
    if(from == to) return 0;
    
    if(from == get_negative() && to == get_positive()){
        return  -m_current;
    }else{
        return  m_current;
    }
}

double currentsource::get_voltage(id_<circuitterminal> from, id_<circuitterminal> to) const {
    return m_resistance * get_current(from,to);
}

void   currentsource::add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,id_<circuitterminal> from, id_<circuitterminal> to) const {
    A(i,j) -= 1.0/m_resistance;
    A(j,i) -= 1.0/m_resistance;
    A(i,i) += 1.0/m_resistance;
    A(j,j) += 1.0/m_resistance;
    b[i] += get_current(from, to);
}

void   currentsource::add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,id_<circuitterminal> from, id_<circuitterminal> to)   const{
    A(i,i) += 1.0/m_resistance;
    b[i]   += get_current(from, to);
    
}