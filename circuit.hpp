#ifndef CIRCUIT
#define CIRCUIT
#include <unordered_map>
#include <vector>
#include <utility> //pair
#include <tuple>
#include <memory>
#include <cstdint>
#include <iostream>

#include "util.hpp"
#include "component.hpp"
#include "circuitnode.hpp"
#include "named.hpp"

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
    void print() const;
    
    component& get_component(COMPONENT_HANDEL handel) const{
        return *(m_components.at(handel));
    }

    private:

        
        std::unordered_map<COMPONENT_HANDEL, std::unique_ptr<component>> m_components;
        std::unordered_map<NODE_HANDEL, std::unique_ptr<circuitnode>> m_nodes;
        std::unordered_map<std::pair<NODE_HANDEL, NODE_HANDEL>, std::tuple<COMPONENT_HANDEL, TERMINAL_HANDEL, TERMINAL_HANDEL>, pair_hash> m_connections;
        
};

#else
struct circuit;
#endif /* CIRCUIT */
