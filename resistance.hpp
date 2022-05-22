#ifndef RESISTANCE
#define RESISTANCE
#include "bipole.hpp"

struct resistance : bipole
{
    resistance(std::string_view p_name, double p_resistance = 1);

    double get_resistance() const{ return m_resistance;}

    double get_resistance(id_<circuitterminal> from, id_<circuitterminal> to) const override {return get_resistance();};

    protected:
        void   add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,id_<circuitterminal> from, id_<circuitterminal> to)   const override;
        void   add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,  id_<circuitterminal> from, id_<circuitterminal> to)   const override;
    
        double m_resistance;
};


#endif /* RESISTANCE */
