#ifndef VOLTAGESOURCE
#define VOLTAGESOURCE
#include "bipole.hpp"

struct voltagesource : bipole
{
    public:
        
    private:
        double m_resistance;
        double m_voltage;
};


#endif /* VOLTAGESOURCE */
