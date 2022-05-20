#include <iostream>
#include "circuit.hpp"
#include "resistance.hpp"
#include "voltagesource.hpp"
int main(int argc, char**argv){
    std::cout << "Test\n";

    //Circuit von https://de.wikipedia.org/wiki/Knotenpotentialverfahren beispiel 
    circuit c("test circuit");
    auto& r1   = c.make_component<resistance>("R1");
    auto& r2   = c.make_component<resistance>("R2");
    auto& r5   = c.make_component<resistance>("R5");
    auto& r7   = c.make_component<resistance>("R7");
    auto& v1   = c.make_component<voltagesource>("V1");
    auto& v2   = c.make_component<voltagesource>("V2");
    auto& v3   = c.make_component<voltagesource>("V3");
    auto& gnd  = c.make_node<circuitnode>("0");
    auto& phi1 = c.make_node<circuitnode>("phi1");
    auto& phi2 = c.make_node<circuitnode>("phi2");
    auto& phi3 = c.make_node<circuitnode>("phi3");
   
    c.connect(gnd,  phi1, r1);
    c.connect(gnd,  phi1, r2);
    c.connect(gnd,  phi2, v3);
    c.connect(gnd,  phi3, r7);
    c.connect(phi1, phi2, v2);
    c.connect(phi1, phi3, v1);
    c.connect(phi2, phi3, r5);

    c.print();

    c.knotenpotenzial(gnd);
    return 0;
}