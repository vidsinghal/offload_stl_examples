#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <iostream>
#include <cassert>


void copy(long *array, int size, long *copied);

int main() {
  
  int size = 2e8;	
  long *array = (long*) malloc(sizeof(long) * size);
  long *copied = (long*) malloc(sizeof(long) * size);
  
  int val = 10;
  
  #pragma omp parallel for
  for(int i = 0; i < size; i++){
       array[i] = val;	
  }

  auto start = std::chrono::high_resolution_clock::now(); 

  copy(array, size, copied);
  
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;
  std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
  
  long sum = 0;
  #pragma omp parallel for 
  for (long i = 0; i < size; i++){
  	assert(array[i] == copied[i] && "Element value not correct.");
	sum += copied[i];
  } 

  std::cout << "Sum: " << sum << std::endl;


}


void copy(long *array, int size, long *copied){

        
	 #pragma omp target teams distribute parallel for map(from: array[0:size]) map(to: copied[0:size]) 
	 for(int i = 0; i < (size/5000); i++){
           for(int j = 0; j < 5000; j++){
                array[i*5000 + j] = copied[i*5000 + j];
           }
         }  


}
