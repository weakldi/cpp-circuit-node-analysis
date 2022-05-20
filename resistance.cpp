#include "resistance.hpp"

resistance::resistance(std::string_view p_name, double p_resistance) 
    :   bipole(p_name), m_resistance(p_resistance)
    {

    }