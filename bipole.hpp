#ifndef BIPOLE
#define BIPOLE
#include "component.hpp"

struct bipole : component{
    bipole(std::string_view p_name);

    virtual TERMINAL_HANDEL get_positive() const { return m_positive;}
    virtual TERMINAL_HANDEL get_negative() const { return m_negative;}

    private:
        TERMINAL_HANDEL m_positive;
        TERMINAL_HANDEL m_negative;
};


#endif /* BIPOLE */
