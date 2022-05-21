#ifndef VOLTAGESOURCE
#define VOLTAGESOURCE
#include "resistance.hpp"

struct voltagesource : resistance
{
    public:
        voltagesource(std::string_view p_name, double p_voltage = 1, double p_resistace = 0);
        double get_current(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const override;
        double get_voltage(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const override;
    protected:
        void   add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,TERMINAL_HANDEL from, TERMINAL_HANDEL to) const override;
        void   add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,TERMINAL_HANDEL from, TERMINAL_HANDEL to)   const override;
    private:
        double m_voltage;
};
#else
struct voltagesource;
#endif /* VOLTAGESOURCE */
