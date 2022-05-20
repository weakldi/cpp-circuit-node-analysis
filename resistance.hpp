#ifndef RESISTANCE
#define RESISTANCE
#include "bipole.hpp"

struct resistance : bipole
{
    resistance(std::string_view p_name);

    double get_resistance() const{ return m_resistance;}

    double get_resistance(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const override {return get_resistance();};
    protected:
        double m_resistance;
};


#endif /* RESISTANCE */
