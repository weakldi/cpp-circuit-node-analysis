#ifndef RESISTANCE
#define RESISTANCE
#include "bipole.hpp"

struct resistance : bipole
{
    resistance(std::string_view p_name, double p_resistance = 1);

    double get_resistance() const{ return m_resistance;}

    double get_resistance(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const override {return get_resistance();};

    protected:
        void   add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,TERMINAL_HANDEL from, TERMINAL_HANDEL to) const override;
        void   add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,TERMINAL_HANDEL from, TERMINAL_HANDEL to)   const override;
    
        double m_resistance;
};


#endif /* RESISTANCE */
