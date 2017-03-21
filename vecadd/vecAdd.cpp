#include <iostream>
#include <stdio.h>

// For all cuda related functionality
#include <cuda_runtime_api.h>
#include <cuda.h>

// For random number generation
#include <cstdlib>

#define CHECK_ERROR(A) \
	do { \
		cudaError_t err = A; \
		if (err != cudaSuccess) { \
			printf("[ERROR]: %s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__); \
		} \
	} while(0)


// A stub function which does memory transfer and kernel computation
void vecAdd(float *A, float *B, float *C, int n) {

	// Step 1: Allocate memory on device for A, B and C
	// Memory on device is allocated using cudaMalloc
	// The CHECK_ERROR macro will read the error status and reports if there is any error during device call
	float *d_A, *d_B, *d_C;
	
	CHECK_ERROR(cudaMalloc((void **)&d_A, n * sizeof(float)));
	CHECK_ERROR(cudaMalloc((void **)&d_B, n * sizeof(float)));
	CHECK_ERROR(cudaMalloc((void **)&d_C, n * sizeof(float)));

	// Step 2: Copy input data to device using cudaMemCpy function
	cudaMemcpy(d_A, A, n * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, B, n * sizeof(float), cudaMemcpyHostToDevice);
	

	// Step 3: Invoke the kernal which does vector addition
	

	// Step 4: Copy the result in d_C back to host
	cudaMemcpy(d_C, C, n * sizeof(float), cudaMemcpyDeviceToHost);
	
	// Step 5: Free the memory on device
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}

int main(void) {
	
	float *A, *B, *C;
//	A = new float(1000);
//	B = new float(1000);
//	C = new float(1000);
	A = (float *)malloc(1000 * sizeof(float));
	B = (float *)malloc(1000 * sizeof(float));
	C = (float *)malloc(1000 * sizeof(float));
	srand(time(NULL));

	for (int i = 0; i < 1000; i++) {
		A[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		B[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	vecAdd(A, B, C, 1000);	
	return 0;
}
