#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

void test_fill(std::vector<int> &v) {
                
}


int main() {

    int arraySize = 512; 
    std::vector<int> *A = new std::vector<int>(arraySize);
    //std::for_each(A->begin(), A->end(), add);
    std::fill(std::execution::par_unseq,A->begin(), A->end(), 0);
    //test_fill(*A);
    delete A;
}