#include "voltagesource.hpp"
#include <iostream>

voltagesource::voltagesource(std::string_view p_name, double p_voltage, double p_resistace)
    :   resistance(p_name), m_voltage(p_voltage)
    {}

double voltagesource::get_current(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const {
    //std::cout << "From" << from << " to" << to << "\n"; 
    if(from == to) return 0;
    double current = m_voltage / m_resistance;
    if(from == get_negative() && to == get_positive()){
        return  -current;
    }else{
        return current;
    }
    return -1;
}