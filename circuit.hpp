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
#include <algorithm>
#include <functional>

#include "util.hpp"
#include "component.hpp"
#include "bipole.hpp"
#include "circuitnode.hpp"
#include "named.hpp"


using connection_component_t = std::optional<std::tuple<id_<component>, id_<circuitterminal>, id_<circuitterminal>>>;
using connection_t = std::pair<id_<circuitnode>, id_<circuitnode>>;

struct circuit : named
{
    circuit(std::string_view p_name);

    template<class T, typename... Args>
    T& make_component(Args&& ... args){ 
        static_assert(std::is_base_of<component, T>());
        //T* c = new T(std::forward<Args>(args)...);
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *(component); //get reference before move
        m_components.emplace(component->id(), std::move(component));
        return ref;
    }

    template<class T, typename... Args>
    T& make_node(Args ... args){
        static_assert(std::is_base_of<circuitnode, T>());
        auto node = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *(node); //get reference before move
        m_nodes.emplace(node->id(), std::move(node));
        return ref;
    }

        void for_each_connection(const circuitnode& from,const circuitnode& to, std::function<void(const component&, id_<circuitterminal> t1, id_<circuitterminal> t2)> f) const{
            const auto  connection = has_connections(from, to);
            if(connection){
                auto [begin,end] = m_connections.equal_range(connection.value());
                auto [from_, to_] = connection.value();
                for(auto it = begin; it != end; it++){
                    auto [component_handel, t1, t2] = *(it->second);
                    // check polarity
                    // check for switch of direction
                    if(from_ != from.id()){
                            std::swap(t1,t2);
                    }
                    auto& component = m_components.at(component_handel);
                    f(*(component.get()), t1, t2);
                }            
            }
        }

    void connect(id_<circuitnode> from, id_<circuitnode> to, std::tuple<id_<component>, id_<circuitterminal>, id_<circuitterminal>> connection);
    void connect(circuitnode& from, circuitnode& to, std::tuple<const component&, id_<circuitterminal>, id_<circuitterminal>> connection);
    void connect(circuitnode& from, circuitnode& to, const bipole& component);
    
    void print() const;
    
    std::optional<connection_t> has_connections(const circuitnode& from,const circuitnode to) const;
    
    component& get_component(id_<component> handel) const{
        return *(m_components.at(handel));
    }

    void knotenpotenzial(id_<circuitnode> zero_handel) const;

    private:

        
        std::unordered_map<id_<component>, std::unique_ptr<component>> m_components;
        std::unordered_map<id_<circuitnode>, std::unique_ptr<circuitnode>, id_<circuitnode>::hash> m_nodes;
        using connection_map = std::unordered_multimap<connection_t, connection_component_t, pair_hash>;
        connection_map m_connections;
        
};
#else

struct circuit;
#endif /* CIRCUIT */
