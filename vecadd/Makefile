all: clean comp run

clean:
	rm -rf a.out

comp:
	nvcc vecAdd.cpp -I/usr/local/cuda/include -L/usr/local/cuda/lib64/ -lcuda -lcudart

run:
	./a.out
	
