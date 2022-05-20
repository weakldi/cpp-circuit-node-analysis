#ifndef VOLTAGESOURCE
#define VOLTAGESOURCE
#include "resistance.hpp"

struct voltagesource : resistance
{
    public:
        voltagesource(std::string_view p_name, double p_voltage = 0, double p_resistace = 0);
    private:
        double m_voltage;
};


#endif /* VOLTAGESOURCE */
