#ifndef COMPONENT
#define COMPONENT
#include <unordered_map>
#include "named.hpp"
#include "circuitnode.hpp"
#include "circuitterminal.hpp"
#include "matrix.hpp"

typedef uint64_t COMPONENT_HANDEL;
struct component : named
{
    component();
    component(std::string_view p_name);
    const std::unordered_map<TERMINAL_HANDEL,std::unique_ptr<circuitterminal>>& get_terminals() const {return m_terminals;};
    virtual double get_resistance(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const = 0;
    virtual double get_current(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const { return 0;}
    virtual double get_voltage(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const { return 0;}
    
    
    COMPONENT_HANDEL get_handel() const {return m_handel;}

    protected:
        virtual void   add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,TERMINAL_HANDEL from, TERMINAL_HANDEL to) const = 0;
        virtual void   add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,TERMINAL_HANDEL from, TERMINAL_HANDEL to)   const = 0;
        
        const COMPONENT_HANDEL m_handel;
        std::unordered_map<TERMINAL_HANDEL,std::unique_ptr<circuitterminal>> m_terminals;

        static COMPONENT_HANDEL next_handel;
        friend struct circuit;
       
};

#else
struct component;
typedef uint64_t COMPONENT_HANDEL;
#endif /* COMPONENT */
