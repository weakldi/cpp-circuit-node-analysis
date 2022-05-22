#include <iostream>
#include "circuit.hpp"
#include "resistance.hpp"
#include "voltagesource.hpp"
#include "math.hpp"
int main(int argc, char**argv){
    std::cout << "Test\n";

    //Circuit von https://de.wikipedia.org/wiki/Knotenpotentialverfahren beispiel 
    circuit c("test circuit");
    auto& r1   = c.make_component<resistance>("R1");
    auto& r2   = c.make_component<resistance>("R2");
    auto& r5   = c.make_component<resistance>("R5");
    auto& r7   = c.make_component<resistance>("R7");
    auto& v1   = c.make_component<voltagesource>("V1", 1, 1);
    auto& v2   = c.make_component<voltagesource>("V2", 1, 1);
    auto& v3   = c.make_component<voltagesource>("V3", 1, 1);
    auto& gnd  = c.make_node<circuitnode>("0");
    auto& phi1 = c.make_node<circuitnode>("phi1");
    auto& phi2 = c.make_node<circuitnode>("phi2");
    auto& phi3 = c.make_node<circuitnode>("phi3");
   
    c.connect(gnd,  phi1, r1);
    c.connect(gnd,  phi1, r2);
    c.connect(gnd,  phi2, v3);
    c.connect(gnd,  phi3, r7);
    c.connect(phi2, phi1, v2); //Currentsource on wikipedia
    c.connect(phi1, phi3, v1);
    c.connect(phi2, phi3, r5);

    c.print();

    c.knotenpotenzial(gnd.id());
    std::cout << "gnd  = " << gnd .get_voltage().value().second << "\n";
    std::cout << "phi1 = " << phi1.get_voltage().value().second << "\n";
    std::cout << "phi2 = " << phi2.get_voltage().value().second << "\n";
    std::cout << "phi3 = " << phi3.get_voltage().value().second << "\n";

    {
        circuit c2("test ideal voltage source"); //GDE1 3.6 Knotenanalyse
        auto& _0 = c2.make_node<circuitnode>("0");
        auto& _1 = c2.make_node<circuitnode>("1");
        auto& _2 = c2.make_node<circuitnode>("2");
        auto& _3 = c2.make_node<circuitnode>("3");
        auto& _r1   = c2.make_component<resistance>("R1");
        auto& _r2   = c2.make_component<resistance>("R2", 1);
        auto& _r3   = c2.make_component<resistance>("R3");
        auto& _v1   = c2.make_component<voltagesource>("V1",1,0);
        auto& _v2   = c2.make_component<voltagesource>("V2",1,0);

        c2.connect(_0,_1, _v1);
        c2.connect(_0,_2, _v2);
        c2.connect(_0,_3, _r3);

        c2.connect(_1,_3, _r1);
        c2.connect(_2,_3, _r2);

        c2.knotenpotenzial(_0.id());
        std::cout << "gnd  = " << _0.get_voltage().value().second << "\n";
        std::cout << "phi1 = " << _1.get_voltage().value().second << "\n";
        std::cout << "phi2 = " << _2.get_voltage().value().second << "\n";
        std::cout << "phi3 = " << _3.get_voltage().value().second << "\n";

        std::unordered_map<id_<component>,std::reference_wrapper<component>, id_<component>::hash> test;
        test.emplace(_r1.id(), _r1);
        test.at(_r1.id());

        auto& t2 = _r1;
    }
    


    

    return 0;
}