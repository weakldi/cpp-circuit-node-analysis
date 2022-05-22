#ifndef BIPOLE
#define BIPOLE
#include "component.hpp"

struct bipole : component{
    bipole(std::string_view p_name);

    virtual const circuitterminal& get_positive() const { return *(m_terminals.at(m_positive).get());}
    virtual const circuitterminal& get_negative() const { return *(m_terminals.at(m_negative).get());}
    //virtual void            add_coefficents(matrix<long double>& A,int i, int j,TERMINAL_HANDEL from, TERMINAL_HANDEL to) const = 0;
    private:
        id_<circuitterminal> m_positive;
        id_<circuitterminal> m_negative;
};
#else
struct bipole;
#endif /* BIPOLE */
