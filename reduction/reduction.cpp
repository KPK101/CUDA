#define N 32
#define BLOCK 2
#include <iostream>
#include <cuda_runtime.h>
#include<vector>

inline void checkCUDAErrors(cudaError_t err, const char* file, int line){
    if(err!=cudaSuccess){
        std::cerr << "CUDA error at " << file << ":" << line << ":" << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE); 
    }
}

#define CHECK_CUDA(call) checkCUDAErrors(call, __FILE__, __LINE__)


inline void checkMalloc(int *ptr, int size, const char* file, int line){
    if(ptr==nullptr){
        std::cerr << "Memory allocation failed at " << file << ":" << line << std::endl;
        std::cerr << "Failed to allocate " << size << "bytes" << std::endl;
        exit(EXIT_FAILURE);
    }
}

# define CHECK_MALLOC(ptr, size) checkMalloc(ptr, size, __FILE__, __LINE__)
/*

Input array is of size N
Assign N/2 threads initially
Each block will compute reduction of 2*BLOCK sized input tile 

EXAMPLE ARRAY:-


    BLOCK 0      |     BLOCK 1

    ***************************
    * 0, 1, 2, 3 * 4, 5, 6, 7 *
    ***************************

Threads will execute as follows for eachs stride:

******************
* (s) | Threads  *
******************

(1)   |     |      |     |
(2)   |            |
(4)   |

*/


void displayArray(const int* buffer, int n){

    std::cout<<"Displaying buffer -> \n";
    for(int i=0; i<n; i++){
        std::cout<<buffer[i]<<std::endl;
    }    
}



void displayGrid(int block, int n){
    // display grid structure
    std::cout<<"Grid size: ("<<(n-1+2*block)/(2*block)<<", 1, 1)\n";
    std::cout<<"Block size:("<<block<<", 1, 1)\n";
}


int getGrid(int block, int n){
    return (n-1+2*block)/(2*block);
}

template<typename T>
__global__ void reduce(T *buffer, int n){
    int tid = threadIdx.x + blockIdx.x*blockDim.x;
    int index;
    for(int s=1; s<=BLOCK; s*=2){
        // check if thread ids are divisible by 2*s 
        index = 2*tid*s;
        if(index+s<n){
            buffer[index] += buffer[index+s];
        }
        __syncthreads();
    }
}

template<typename T>
__global__ void reduceBlock(T *buffer, T* aux_buffer, int n){
  
    int bid = 2;

    int bstart = blockIdx.x*2*blockDim.x;
    int tid = threadIdx.x;
    int index;


    for(int s=1; s<=BLOCK; s*=2){
        
        index = 2*tid*s + bstart; 
        if(index+s<n){
            buffer[index] += buffer[index+s];  
        }      

        __syncthreads();

    }
    
    if(threadIdx.x==0){
        aux_buffer[blockIdx.x] = buffer[tid + bstart];
    }

}

template<typename T>
__global__ void reduceBlock_SharedMemory(T *buffer, T *aux_buffer, int n){
  
    int bid = 2;

    int bstart = blockIdx.x*2*blockDim.x;
    int tid = threadIdx.x;
    int sindex;

    __shared__ int sm[2*BLOCK];

    // Load into shared memory
    for(int i=0; i<2; i++){
        int gindex = blockIdx.x*2*blockDim.x + threadIdx.x + i*BLOCK;
        if(gindex < n){
            sm[threadIdx.x + i*BLOCK] = buffer[gindex];
        }
        else{
            sm[threadIdx.x + i*BLOCK] = 0;
        }        
     }
    __syncthreads();



    // perform reduction in shared memory
    for(int s=1; s<=BLOCK; s*=2){
        sindex = 2*tid*s;   
        if(sindex+s<n){

            sm[sindex] += sm[sindex+s];
        }      
        __syncthreads();
    }
    
    if(threadIdx.x==0){
        aux_buffer[blockIdx.x] = sm[0];
    }

}

template<typename T>
T* deviceReduction(T*d_buffer, T*d_aux_buffer, int n, int stack){
   
    T* result_ptr;
    size_t size = n*sizeof(T);
    int gd = getGrid(BLOCK, n);
    int bid = 0;

    dim3 block(BLOCK, 1, 1);
    dim3 grid(gd, 1, 1);

    T* buffer_read;
    T* aux_buffer_read;
    buffer_read = (T*)malloc(n*sizeof(T));
    aux_buffer_read = (T*) malloc(n*sizeof(T));
    CHECK_MALLOC(buffer_read, n);
    CHECK_MALLOC(aux_buffer_read, n);
    ////////////////////
    // Pre reduction ///
    ////////////////////

    CHECK_CUDA(cudaMemcpy(buffer_read, d_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaMemcpy(aux_buffer_read, d_aux_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaDeviceSynchronize());


    std::cout << "****************************\nstack="<< stack <<"\n****************************\n";
    std::cout << "---------------------\nPre-reduction\n---------------------\n";    
    std::cout << "\tBuffer:\n\t";

    for(int i=0; i<n; i++){
        if(i%(2*BLOCK)==0){
            std::cout << " ||| ";
        }
        std::cout << " "<< buffer_read[i] << " ,";
        
    }   

    std::cout << " ||| \n";
    std::cout << "\tAuxillary Buffer:\n\t";
    
    for(int i=0; i<n; i++){
        std::cout << " "<< aux_buffer_read[i] << " ,";
    }
    
    /////////////////////////////
    /////////////////////////////
    /////////////////////////////
 
    reduceBlock<<<grid, block>>>(d_buffer, d_aux_buffer, n);
    CHECK_CUDA(cudaGetLastError());
    CHECK_CUDA(cudaDeviceSynchronize());

    //////////////////////////////
    ////// Post reduction ////////
    //////////////////////////////

    CHECK_CUDA(cudaMemcpy(buffer_read, d_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaMemcpy(aux_buffer_read, d_aux_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaDeviceSynchronize());
     
    std::cout << "\n---------------------\nPost-reduction\n---------------------\n";    
    std::cout << "\tBuffer:\n\t";

    for(int i=0; i<n; i++){
        if(i%(2*BLOCK)==0){
            std::cout << " ||| ";
        }
        std::cout << " "<< buffer_read[i] << " ,";
        
    }    
    std::cout << " ||| \n";
    std::cout << "\tAuxillary Buffer:\n\t";
    
    for(int i=0; i<n; i++){
        std::cout << " "<< aux_buffer_read[i] << " ,";
    }
    std::cout << "\n\n\n";

    ///////////////////////////////
    ///////////////////////////////
    ///////////////////////////////

    if(gd==1){
        return d_aux_buffer;
    }
    else{
        result_ptr = deviceReduction(d_aux_buffer, d_buffer, gd, stack + 1);
        return result_ptr;
    }
    
    // free host data
    free(buffer_read);
    free(aux_buffer_read);
}

int main(){

    // define input host buffer 
    int h_buffer[N];
    int sum = 0;

    // define device buffer
    int *d_buffer;
    int *d_aux_buffer;
    int* d_result;

    // fill input values - [1, N]
    for(int i=0; i<N; i++){
        h_buffer[i] = i+1;
    }

    size_t size = N*sizeof(int);
    int a_n = getGrid(BLOCK, N); // Initial aux buffer length - #blocks

    // Allocate memory on device
    CHECK_CUDA(cudaMalloc((void**)&d_buffer, size));
    CHECK_CUDA(cudaMalloc((void**)&d_aux_buffer, size));

    // Copy data into d_buffer
    CHECK_CUDA(cudaMemcpy((void*)d_buffer, (void*)h_buffer, size, cudaMemcpyHostToDevice));

    // Call reduction function
    d_result = deviceReduction(d_buffer, d_aux_buffer, N, 0); 

    // Synchronize global context 
    CHECK_CUDA(cudaDeviceSynchronize());

    // Copy result[0] to sum
    CHECK_CUDA(cudaMemcpy(&sum, d_result, sizeof(int), cudaMemcpyDeviceToHost));

    cudaFree(d_buffer);
    cudaFree(d_aux_buffer);

   std::cout<<"The computed sum is: "<<sum<<std::endl;
}

