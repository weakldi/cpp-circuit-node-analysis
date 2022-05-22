#include "component.hpp"


component::component()
 : named("COMPONENT_"+ std::to_string(id_<component>::next_id)), give_id<component>()
{

}

component::component(std::string_view p_name)
    : named(p_name)
    {

    }