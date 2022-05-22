#include "component.hpp"

COMPONENT_HANDEL component::next_handel = 0;

component::component()
 : named("COMPONENT_" + std::to_string(component::next_handel)), give_id<component>(), m_handel(component::next_handel++)
{

}

component::component(std::string_view p_name)
    : named(p_name), m_handel(component::next_handel++)
    {

    }