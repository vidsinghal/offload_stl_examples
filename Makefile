compile_offload: 
	clang++ -O3 -fopenmp --offload-arch=native for_each_offload.cpp -o for_each_offload
	clang++ -O3 -fopenmp --offload-arch=native transform_reduce.cpp -o transform_reduce_offload
	clang++ -O3 -fopenmp --offload-arch=native fill_offload.cpp -o fill_offload
	clang++ -O3 -fopenmp --offload-arch=native copy_offload.cpp -o copy_offload

compile_omp_cpu:
	clang++ -O3 -fopenmp for_each_offload.cpp -o for_each_omp
	clang++ -O3 -fopenmp transform_reduce.cpp -o transform_reduce_omp
	clang++ -O3 -fopenmp fill_offload.cpp -o fill_omp
	clang++ -O3 -fopenmp copy_offload.cpp -o copy_omp

compile_cpu:
	clang++ -O3 for_each_offload.cpp -o for_each_cpu
	clang++ -O3 transform_reduce.cpp -o transform_reduce_cpu
	clang++ -O3 fill_offload.cpp -o fill_cpu
	clang++ -O3 copy_offload.cpp -o copy_cpu

all: compile_offload compile_omp_cpu compile_cpu
