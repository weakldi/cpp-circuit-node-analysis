#ifndef MATRIX
#define MATRIX
#include <stdexcept>
#include <vector>
#include <iostream>
template<typename T>
struct matrix
{
    matrix(uint64_t rang) : rang(rang){
        m_data.resize(rang);
        for(int i = 0; i < rang; i++){
            m_data[i].resize(rang);
        }
    }
   
    T& operator() (uint64_t row, uint64_t col) {
        if(row >= rang) throw std::out_of_range("row of range");
        if(col >= rang) throw std::out_of_range("col of range");
        
        //return m_data[rang*row + col];
        return m_data[row][col];
    }     
    T  operator() (uint64_t row, uint64_t col) const{
        if(row >= rang) throw std::out_of_range("row of range");
        if(col >= rang) throw std::out_of_range("col of range");
        
        //return m_data[rang*row + col];
        return m_data[row][col];
    }

    void resize(uint64_t new_rang){
        if(rang > new_rang) throw std::invalid_argument("rang to smal");
        m_data.resize(new_rang);
        for(int i = 0; i < new_rang; i++){
            m_data[i].resize(new_rang);
            
        }
        rang = new_rang;
    }

    void print() const{
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                std::cout << (*this)(i,j) << ", ";
            }
            std::cout << std::endl;
        }
    }
    uint64_t rang;
    //std::vector<T> m_data;
    std::vector<std::vector<T>> m_data;
};


#endif /* MATRIX */
