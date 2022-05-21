#ifndef BIPOLE
#define BIPOLE
#include "component.hpp"

struct bipole : component{
    bipole(std::string_view p_name);

    virtual TERMINAL_HANDEL get_positive() const { return m_positive;}
    virtual TERMINAL_HANDEL get_negative() const { return m_negative;}
    //virtual void            add_coefficents(matrix<long double>& A,int i, int j,TERMINAL_HANDEL from, TERMINAL_HANDEL to) const = 0;
    private:
        TERMINAL_HANDEL m_positive;
        TERMINAL_HANDEL m_negative;
};
#else
struct bipole;
#endif /* BIPOLE */
