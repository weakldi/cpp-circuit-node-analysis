#ifndef VOLTAGESOURCE
#define VOLTAGESOURCE
#include "resistance.hpp"

struct voltagesource : resistance
{
    public:
        voltagesource(std::string_view p_name, double p_voltage = 1, double p_resistace = 0);
        double get_current(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const override;
    private:
        double m_voltage;
};


#endif /* VOLTAGESOURCE */
