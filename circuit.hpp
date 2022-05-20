#ifndef CIRCUIT
#define CIRCUIT
#include <unordered_map>
#include <vector>
#include <utility> //pair
#include <tuple>
#include <memory>
#include <cstdint>
#include <iostream>
#include <optional>

#include "util.hpp"
#include "component.hpp"
#include "bipole.hpp"
#include "circuitnode.hpp"
#include "named.hpp"


using connection_component_t = std::optional<std::tuple<COMPONENT_HANDEL, TERMINAL_HANDEL, TERMINAL_HANDEL>>;
using connection_t = std::pair<NODE_HANDEL, NODE_HANDEL>;

struct circuit : named
{
    circuit(std::string_view p_name);

    template<class T, typename... Args>
    T& make_component(Args&& ... args){ 
        static_assert(std::is_base_of<component, T>());
        //T* c = new T(std::forward<Args>(args)...);
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *(component); //get reference before move
        m_components.emplace(component->get_handel(), std::move(component));
        return ref;
    }

    template<class T, typename... Args>
    T& make_node(Args ... args){
        static_assert(std::is_base_of<circuitnode, T>());
        auto node = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *(node); //get reference before move
        m_nodes.emplace(node->get_handel(), std::move(node));
        return ref;
    }

    void connect(NODE_HANDEL from, NODE_HANDEL to, std::tuple<COMPONENT_HANDEL, TERMINAL_HANDEL, TERMINAL_HANDEL> connection);
    void connect(circuitnode& from, circuitnode to, std::tuple<const component&, TERMINAL_HANDEL, TERMINAL_HANDEL> connection);
    void connect(circuitnode& from, circuitnode to, const bipole& component);
    void print() const;
    
    std::optional<connection_t> has_connections(const circuitnode& from,const circuitnode to) const;
    
    component& get_component(COMPONENT_HANDEL handel) const{
        return *(m_components.at(handel));
    }

    void knotenpotenzial(const circuitnode& zero) const;

    private:

        
        std::unordered_map<COMPONENT_HANDEL, std::unique_ptr<component>> m_components;
        std::unordered_map<NODE_HANDEL, std::unique_ptr<circuitnode>> m_nodes;
        using connection_map = std::unordered_multimap<connection_t, connection_component_t, pair_hash>;
        connection_map m_connections;
        
};

#else

using connection_component_t = std::optional<std::tuple<COMPONENT_HANDEL, TERMINAL_HANDEL, TERMINAL_HANDEL>>;
using connection_t = std::pair<NODE_HANDEL, NODE_HANDEL>;
struct circuit;
#endif /* CIRCUIT */
