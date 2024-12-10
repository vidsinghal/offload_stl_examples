#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <iostream>
#include <cassert>


void for_each(long *array, int size, long (*operation)(long));
long complex(long i);
#pragma omp declare target indirect to(complex)


int main() {
  
  int size = 2e8;	
  long *array = (long*) malloc(sizeof(long) * size);
  int val = 10;
  
  #pragma omp parallel for
  for(int i = 0; i < size; i++){
       array[i] = val;	
  }

  long (*func_ptr)(long) = complex;

  auto start = std::chrono::high_resolution_clock::now(); 

  for_each(array, size, func_ptr);
  
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;
  std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
  
  long sum = 0;
  #pragma omp parallel for reduction(+:sum)
  for (long i = 0; i < size; i++){
	int elem = array[i];  
  	assert(elem == complex(val) && "Element value not correct.");
	sum += elem;
  } 

  std::cout << "Sum: " << sum << std::endl;


}


long complex(long i){

 long j = i; 
 j = j * 1; 
 j = j + 1; 
 j = j * 10; 
 j = j / 4; 
 j = j + 1;

 for(int k = 1; k < 10000; k++){
   j = j * k;    
 } 

  return j;

}

void for_each(long *array, int size, long (*func_ptr)(long)){

        
	#pragma omp target teams distribute parallel for map(tofrom: array[0:size])
    	for(int i = 0; i < (size/5000); i++){
	   for(int j = 0; j < 5000; j++){	
		array[i*5000 + j] = func_ptr(array[i*5000 + j]);
	   }
	}  


}
