#include "bipole.hpp"

bipole::bipole(std::string_view p_name)
    : component(p_name) 
    { 
        auto positive = std::make_unique<circuitterminal>(*this,std::string(p_name) + ".+");
        auto negative = std::make_unique<circuitterminal>(*this,std::string(p_name) + ".-");

        m_positive = (positive.get())->id();
        m_negative = (negative.get())->id();

        m_terminals.emplace(m_positive, std::move(positive));
        m_terminals.emplace(m_negative, std::move(negative));
    }