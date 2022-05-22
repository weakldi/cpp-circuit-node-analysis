#ifndef COMPONENT
#define COMPONENT
#include <unordered_map>
#include "named.hpp"
#include "circuitnode.hpp"
#include "circuitterminal.hpp"
#include "matrix.hpp"
#include "id.hpp"

typedef uint64_t COMPONENT_HANDEL;
struct component : named, give_id<component>
{
    component();
    component(std::string_view p_name);
    const std::unordered_map<id_<circuitterminal> ,std::unique_ptr<circuitterminal>, id_<circuitterminal>::hash>& get_terminals() const {return m_terminals;};
    virtual double get_resistance(id_<circuitterminal> from, id_<circuitterminal> to) const = 0;
    virtual double get_current(id_<circuitterminal> from, id_<circuitterminal> to) const { return 0;}
    virtual double get_voltage(id_<circuitterminal> from, id_<circuitterminal> to) const { return 0;}
    
    
    COMPONENT_HANDEL get_handel() const {return m_handel;}

    protected:
        virtual void   add_coefficents(matrix<long double>& A, std::vector<long double>& b,int i, int j,id_<circuitterminal> from, id_<circuitterminal> to) const = 0;
        virtual void   add_coefficents_zero(matrix<long double>& A, std::vector<long double>& b,int i,id_<circuitterminal> from, id_<circuitterminal> to)   const = 0;
        
        const COMPONENT_HANDEL m_handel;
        std::unordered_map<id_<circuitterminal> ,std::unique_ptr<circuitterminal>, id_<circuitterminal>::hash> m_terminals;

        static COMPONENT_HANDEL next_handel;
        friend struct circuit;
       
};

#else
struct component;
typedef uint64_t COMPONENT_HANDEL;
#endif /* COMPONENT */
