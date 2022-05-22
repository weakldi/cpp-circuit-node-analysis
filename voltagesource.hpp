#ifndef VOLTAGESOURCE
#define VOLTAGESOURCE
#include "resistance.hpp"

struct voltagesource : resistance
{
    public:
        voltagesource(std::string_view p_name, double p_voltage = 1, double p_resistace = 0);
        double get_current(id_<circuitterminal> from, id_<circuitterminal> to) const override;
        double get_voltage(id_<circuitterminal> from, id_<circuitterminal> to) const override;
        std::ostream& print(std::ostream& out = std::cout) const override;
    protected:
        void   add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,id_<circuitterminal> from, id_<circuitterminal> to) const override;
        void   add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,id_<circuitterminal> from, id_<circuitterminal> to)   const override;
    private:
        double m_voltage;
};
#else
struct voltagesource;
#endif /* VOLTAGESOURCE */
