#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <iostream>
#include <cassert>

void fill(int *array, long size, int val);

int main() {
  
  long size = 1000000000;	
  int *array = (int*) malloc(sizeof(int) * size);
  int val = 100000;
  
  auto start = std::chrono::high_resolution_clock::now(); 

  fill(array, size, val);
  
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;
  std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
  
  long sum = 0;
  for (long i = 0; i < size; i++){
  	assert(array[i] == val && "Element value not correct.");
	sum += array[i];
  } 

  std::cout << "Sum: " << sum << std::endl;


}


void fill(int *array, long size, int val){

        
	#pragma omp target teams distribute parallel for map(from: array[0:size])
    	for(long i = 0; i < (size/5000); i++){
	   for(long j = 0; j < 5000; j++){	
		array[i*5000 + j] = val;
	   }
	}  


}
