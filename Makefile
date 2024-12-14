compile_offload: 
	clang++ -O3 -fopenmp --offload-arch=native for_each_offload.cpp -o for_each_offload
	clang++ -O3 -fopenmp --offload-arch=native transform_reduce.cpp -o transform_reduce_offload
	clang++ -O3 -fopenmp --offload-arch=native fill_offload.cpp -o fill_offload
	clang++ -O3 -fopenmp --offload-arch=native copy_offload.cpp -o copy_offload
	clang++ -O3 -fopenmp --offload-arch=native any_of_offload.cpp -o any_of_offload
	clang++ -O3 -fopenmp --offload-arch=native count_offload.cpp -o count_offload

compile_omp_cpu:
	clang++ -O3 -fopenmp for_each_offload.cpp -o for_each_omp
	clang++ -O3 -fopenmp transform_reduce.cpp -o transform_reduce_omp
	clang++ -O3 -fopenmp fill_offload.cpp -o fill_omp
	clang++ -O3 -fopenmp copy_offload.cpp -o copy_omp
	clang++ -O3 -fopenmp any_of_offload.cpp -o any_of_omp
	clang++ -O3 -fopenmp count_offload.cpp -o count_omp

compile_cpu:
	clang++ -O3 for_each_offload.cpp -o for_each_cpu
	clang++ -O3 transform_reduce.cpp -o transform_reduce_cpu
	clang++ -O3 fill_offload.cpp -o fill_cpu
	clang++ -O3 copy_offload.cpp -o copy_cpu
	clang++ -O3 any_of_offload.cpp -o any_of_cpu
	clang++ -O3 count_offload.cpp -o count_cpu

run_offload:
	./for_each_offload
	./transform_reduce_offload
	./fill_offload
	./copy_offload
	./any_of_offload
	./count_offload

run_omp_cpu:
	./for_each_omp
	./transform_reduce_omp
	./fill_omp
	./copy_omp
	./any_of_omp
	./count_omp

run_cpu:
	./for_each_cpu
	./transform_reduce_cpu
	./fill_cpu
	./copy_cpu
	./any_of_cpu
	./count_cpu

all: compile_offload compile_omp_cpu compile_cpu
run: run_offload run_omp_cpu run_cpu