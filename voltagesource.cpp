#include "voltagesource.hpp"


voltagesource::voltagesource(std::string_view p_name, double p_voltage, double p_resistace)
    :   resistance(p_name), m_voltage(p_voltage)
    {}