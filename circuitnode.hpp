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

struct circuitnode : named, give_id<circuitnode>
{
    circuitnode();
    circuitnode(std::string_view p_name);
    void add_connection(const component& p_component, const circuitterminal& p_terminal);
    std::vector<std::pair<id_<component>, id_<circuitterminal>>> m_connections;

    std::optional<std::pair<id_<circuitnode>, long double>> get_voltage() const;



    private:
        circuitnode(const component& p_component, std::string_view p_name = "");
        void set_voltage_potential(const circuitnode& zero, long double voltage);
        
        std::optional<std::pair<id_<circuitnode>, long double>> m_voltage_potential;
        
        friend struct circuit; 
};

#else

struct circuitnode;
#endif /* CIRCUITNODE */
