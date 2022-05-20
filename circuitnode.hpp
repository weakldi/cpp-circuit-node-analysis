#ifndef CIRCUITNODE
#define CIRCUITNODE
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <tuple>

#include "circuitterminal.hpp"
#include "component.hpp"
#include "named.hpp"

typedef uint64_t NODE_HANDEL;
struct circuitnode : named
{
    circuitnode();
    circuitnode(std::string_view p_name);
    void add_connection(const component& p_component, const circuitterminal& p_terminal);
    std::vector<std::pair<COMPONENT_HANDEL, TERMINAL_HANDEL>> m_connections;

    NODE_HANDEL get_handel() const {return m_handel;} 

    private:
        circuitnode(const component& p_component, std::string_view p_name = "");
        const NODE_HANDEL m_handel;
        static NODE_HANDEL next_handel;
        friend struct circuit; 
};

#else

typedef uint64_t NODE_HANDEL;
struct circuitnode;
#endif /* CIRCUITNODE */
