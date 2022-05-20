#include <iostream>
#include "circuit.hpp"
#include "resistance.hpp"
int main(int argc, char**argv){
    std::cout << "Test\n";
    circuit c("test circuit");
    auto& r = c.make_component<resistance>("R1") ;
    auto& gnd = c.make_node<circuitnode>("GND");
    auto& vdd = c.make_node<circuitnode>("vdd");
    std::cout << r.get_name() << "\n";

    c.connect(gnd.get_handel(), vdd.get_handel(), {r.get_handel(), r.get_negative(), r.get_positive()});
    c.print();
    return 0;
}