#ifndef MATH
#define MATH
#include "matrix.hpp"

template<typename T>
std::vector<T> gauss(matrix<T>& A, std::vector<T>& b){
    if(A.rang != b.size()) throw std::bad_exception();
    T tmp;
    for(int col = 0; col < A.rang; col++){
        for(int row = col+1; row < A.rang; row++){
            T factor = A(row, col) / A(col, col); //todo sort colums A(i,i) = 0 will cause problems
            using std::cout;
            cout << "R " << row << " C" << col << " factor" << factor << std::endl;
            for(int i = 0; i < A.rang; i++){
                tmp = A(row, i) - factor*A(col, i);
                A(row, i) = tmp;
            }
            tmp = b[row] - factor*b[col];
            b[row] = tmp;
            /*A.print();
            std::cout << "\n";/**/
        }
    }
    //Back substituztion
    std::vector<T> solution(b.size());
   
    solution[A.rang-1] = b[A.rang-1]/A(A.rang-1,A.rang-1);
    
    for(int i = A.rang -1; i >= 0; i--){
        solution[i] = b[i];
        for(int j = i+1; j < A.rang; j++){
            solution[i] -= A(i,j) * solution[j];
        }
        solution[i] = solution[i]/A(i,i);
        
    }
    /*
    for(int i = 0; i < A.rang; i++){
        std::cout << i << " " << solution[i] << std::endl;
    }*/
    return solution;
}



#endif /* MATH */
