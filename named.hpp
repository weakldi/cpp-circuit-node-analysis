#ifndef NAMED
#define NAMED
#include <string>
struct named{
    public:
        named(std::string_view p_name) : m_name(p_name) {}
        std::string_view get_name() const { return m_name;}
    protected:
        std::string m_name;
};
#endif /* NAMED */
