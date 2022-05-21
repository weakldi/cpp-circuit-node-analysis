#ifndef COMPONENT
#define COMPONENT
#include <unordered_map>
#include "named.hpp"
#include "circuitnode.hpp"
#include "circuitterminal.hpp"

typedef uint64_t COMPONENT_HANDEL;
struct component : named
{
    component();
    component(std::string_view p_name);
    const std::unordered_map<TERMINAL_HANDEL,std::unique_ptr<circuitterminal>>& get_terminals() const {return m_terminals;};
    virtual double get_resistance(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const = 0;
    virtual double get_current(TERMINAL_HANDEL from, TERMINAL_HANDEL to) const { return 0;}
    COMPONENT_HANDEL get_handel() const {return m_handel;}

    protected:
        const COMPONENT_HANDEL m_handel;
        std::unordered_map<TERMINAL_HANDEL,std::unique_ptr<circuitterminal>> m_terminals;

        static COMPONENT_HANDEL next_handel;
       
};

#else
struct component;
typedef uint64_t COMPONENT_HANDEL;
#endif /* COMPONENT */
