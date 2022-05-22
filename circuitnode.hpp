#ifndef CIRCUITNODE
#define CIRCUITNODE
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <tuple>
#include <optional>

#include "circuitterminal.hpp"
#include "component.hpp"
#include "named.hpp"
#include "id.hpp"

typedef uint64_t NODE_HANDEL;
struct circuitnode : named, give_id<circuitnode>
{
    circuitnode();
    circuitnode(std::string_view p_name);
    void add_connection(const component& p_component, const circuitterminal& p_terminal);
    std::vector<std::pair<COMPONENT_HANDEL, TERMINAL_HANDEL>> m_connections;

    std::optional<std::pair<NODE_HANDEL, long double>> get_voltage() const;

    NODE_HANDEL get_handel() const {return m_handel;} 

    private:
        circuitnode(const component& p_component, std::string_view p_name = "");
        void set_voltage_potential(const circuitnode& zero, long double voltage);
        const NODE_HANDEL m_handel;
        std::optional<std::pair<NODE_HANDEL, long double>> m_voltage_potential;
        static NODE_HANDEL next_handel;
        friend struct circuit; 
};

#else

typedef uint64_t NODE_HANDEL;
struct circuitnode;
#endif /* CIRCUITNODE */
