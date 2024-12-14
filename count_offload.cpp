#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <iostream>
#include <cassert>

void count(long *array, int size, int *result, long (*operation)(long));
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
  int result = 0;
  auto start = std::chrono::high_resolution_clock::now(); 

  count(array, size, &result, func_ptr);
  
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;
  std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

  std::cout << "Count: " << result << std::endl;


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

void count(long *array, int size, int *result, long (*func_ptr)(long)) {
	#pragma omp target teams distribute parallel for map(tofrom: array[0:size])
  for(int i = 0; i < (size/5000); i++) {
    for(int j = 0; j < 5000; j++) {
      if (array[i*5000 + j] == func_ptr(array[i*5000 + j])) {
        *result += *result + 1;
      }
    }
  }
}
