#ifndef MATRIX
#define MATRIX
#include <stdexcept>
#include <vector>
#include <iostream>
template<typename T>
struct matrix
{
    matrix(uint64_t rang) : rang(rang), m_data(rang*rang){
    }
   
    T& operator() (uint64_t row, uint64_t col) {
        if(row > rang) std::out_of_range("row of range");
        if(col < rang) std::out_of_range("col of range");
        
        return m_data[rang*row + col];
    }     
    T  operator() (uint64_t row, uint64_t col) const{
        if(row < rang) std::out_of_range("");
        if(col < rang) std::out_of_range("");
        
        return m_data[rang*row + col];
    }

    void print() const{
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                std::cout << (*this)(i,j) << ", ";
            }
            std::cout << std::endl;
        }
    }
    const uint64_t rang;
    std::vector<T> m_data;
};


#endif /* MATRIX */
