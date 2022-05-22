#include "resistance.hpp"

resistance::resistance(std::string_view p_name, double p_resistance) 
    :   bipole(p_name), m_resistance(p_resistance)
    {

    }

void   resistance::add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,id_<circuitterminal> from, id_<circuitterminal> to) const {
    A(i,j) -= 1/m_resistance;
    A(j,i) -= 1/m_resistance;
    A(i,i) += 1/m_resistance;
    A(j,j) += 1/m_resistance;
}

void   resistance::add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,id_<circuitterminal> from, id_<circuitterminal> to)   const{
    A(i,i) += 1/m_resistance;
}