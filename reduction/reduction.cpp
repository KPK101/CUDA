#define N 3200
#define BLOCK 2
#include <iostream>
#include <cuda_runtime.h>
#include<vector>
#include <typeinfo>
#include<random>
#include<ctime>

inline void checkCUDAErrors(cudaError_t err, const char* file, int line){
    if(err!=cudaSuccess){
        std::cerr << "CUDA error at " << file << ":" << line << ":" << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE); 
    }
}

#define CHECK_CUDA(call) checkCUDAErrors(call, __FILE__, __LINE__)

template <typename T>
inline void checkMalloc(T *ptr, int size, const char* file, int line){
    if(ptr==nullptr){
        std::cerr << "Memory allocation failed at " << file << ":" << line << std::endl;
        std::cerr << "Failed to allocate " << size << "bytes" << std::endl;
        exit(EXIT_FAILURE);
    }
}

# define CHECK_MALLOC(ptr, size) checkMalloc(ptr, size, __FILE__, __LINE__)

// #define DEBUG

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

template<typename T>
void displayArray(const T* buffer, size_t n){

    std::cout<<"Displaying buffer -> \n";
    for(size_t i=0; i<n; i++){
        std::cout<<buffer[i]<<std::endl;
    }    
}



void displayGrid(size_t block, size_t n){
    // display grid structure
    std::cout<<"Grid size: ("<<(n-1+2*block)/(2*block)<<", 1, 1)\n";
    std::cout<<"Block size:("<<block<<", 1, 1)\n";
}


int getGrid(size_t block, size_t n){
    return (n-1+2*block)/(2*block);
}


template<typename T>
__global__ void reduceBlock(T *buffer, T* aux_buffer, size_t n){
    /*
        Kernel reduces a single thread block
        Each thread block of size B processes an input tile of size 2*B
        Optimizations:
            This is a naive kernel with many inefficiencies
            It is a good starting point to implement parallel reduction
    */

    int bstart = blockIdx.x*2*blockDim.x;
    size_t tid = threadIdx.x;
    size_t index;


    for(size_t s=1; s<=BLOCK; s*=2){
        
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
__global__ void reduceBlock_SharedMemory(T *buffer, T *aux_buffer, size_t n){
    /*
        Kernel is built on naive kernel and is optimized for shared memory usage
        Each thread block loads the input tile it processes into shared memory (size = 2*BLOCK)
        Reduction is performed in shared memory which reduces global memory traffic - improving latency of read/writes
        Optimizations:
            Shared Memory
        Issues:
            Usage of shared memory introduces bank conflicts
            This needs to be addressed for better usage of shared memory bandwidth
    */
    
    int bstart = blockIdx.x*2*blockDim.x;
    size_t tid = threadIdx.x;
    int sindex;

    __shared__ T sm[2*BLOCK];

    // Load into shared memory
    for(int i=0; i<2; i++){
        size_t gindex = blockIdx.x*2*blockDim.x + threadIdx.x + i*BLOCK;
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
T* deviceReduction(T *d_buffer, T *d_aux_buffer, size_t n, size_t stack){
    /*
        This is a host function that recursively calls reduction kernels on input array
        At each recursion step, the input array is reduced blockwise and sum is stored in 0th index of each block
        The sum of each block is stored in an auxillary array (ith index in this array holds sum of ith block)
        
        Design:
            We want two arrays - one input and one auxillary in each recursion call
            It is optimal to make use of the first two device arrays created 
            This can be done by switching the role of buffer and aux_buffer for each new call
            This works because at the end of each call the input needed to be reduced is stored in aux and we do not need buffer data anymore
    */
    
    T* result_ptr;
    size_t size = n*sizeof(T);
    int gd = getGrid(BLOCK, n);

    dim3 block(BLOCK, 1, 1);
    dim3 grid(gd, 1, 1);

    #ifdef DEBUG

    // debug array declarations
    // arrays to read and display buffer and aux_buffer data
    
    T* buffer_read;
    T* aux_buffer_read;
    buffer_read = (T*)malloc(n*sizeof(T));
    aux_buffer_read = (T*) malloc(n*sizeof(T));
    CHECK_MALLOC(buffer_read, n);
    CHECK_MALLOC(aux_buffer_read, n);
    
    #endif
    
    
    ////////////////////
    // Pre reduction ///
    ////////////////////
    #ifdef DEBUG

    CHECK_CUDA(cudaMemcpy(buffer_read, d_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaMemcpy(aux_buffer_read, d_aux_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaDeviceSynchronize());

    std::cout << "****************************\nstack="<< stack <<"\n****************************\n";
    std::cout << "---------------------\nPre-reduction\n---------------------\n";    
    std::cout << "\tBuffer:\n\t";

    for(size_t i=0; i<n; i++){
        if(i%(2*BLOCK)==0){
            std::cout << " ||| ";
        }
        std::cout << " "<< buffer_read[i] << " ,";
        
    }   

    std::cout << " ||| \n";
    std::cout << "\tAuxillary Buffer:\n\t";
    
    for(size_t i=0; i<n; i++){
        std::cout << " "<< aux_buffer_read[i] << " ,";
    }

    #endif
    /////////////////////////////
    /////////////////////////////
    /////////////////////////////
 
    reduceBlock<<<grid, block>>>(d_buffer, d_aux_buffer, n);
    CHECK_CUDA(cudaGetLastError());
    CHECK_CUDA(cudaDeviceSynchronize());

    //////////////////////////////
    ////// Post reduction ////////
    //////////////////////////////

    #ifdef DEBUG 

    CHECK_CUDA(cudaMemcpy(buffer_read, d_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaMemcpy(aux_buffer_read, d_aux_buffer, size, cudaMemcpyDeviceToHost));
    CHECK_CUDA(cudaDeviceSynchronize());
    
    std::cout << "\n---------------------\nPost-reduction\n---------------------\n";    
    std::cout << "\tBuffer:\n\t";

    for(size_t i=0; i<n; i++){
        if(i%(2*BLOCK)==0){
            std::cout << " ||| ";
        }
        std::cout << " "<< buffer_read[i] << " ,";
        
    }    
    std::cout << " ||| \n";
    std::cout << "\tAuxillary Buffer:\n\t";
    
    for(size_t i=0; i<n; i++){
        std::cout << " "<< aux_buffer_read[i] << " ,";
    }
    std::cout << "\n\n\n";

    #endif

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
    
    #ifdef DEBUG

    // free host data
    free(buffer_read);
    free(aux_buffer_read);

    #endif

}

template<typename T>
T getRandom(){
    //Thanks GPT!
    static std::mt19937 rng(static_cast<unsigned int>(std::time(0)));  // Random number generator

    if constexpr (std::is_integral_v<T>) {
        // If type is integral (like int, long, etc.)
        std::uniform_int_distribution<T> dist(1, 100);  
        return dist(rng);
    }
    else if constexpr (std::is_floating_point_v<T>) {
        // If type is floating-point (like float, double)
        std::uniform_real_distribution<T> dist(0.0, 1.0); 
        return dist(rng);
    }
    else {
        // If type is not supported, throw an error (or handle differently)
        throw std::invalid_argument("Unsupported type for random generation.");
    }
}

template<typename T>
T cpuComp(T *buffer, size_t n){
    // test function - checks if computed sum is correct
    T sum = 0;
    for(size_t i=0; i<n; i++){
        sum += buffer[i];
    }

    return sum;
}

template<typename T>
bool testComp(T* buffer, size_t n, T gpuSum, double atol=1e-5, double rtol=1e-5){
    T cpuSum = cpuComp(buffer, n);
    T diff = abs(cpuSum - gpuSum);

    if(diff<atol){
        std::cout << "GPU sum is correct!\n";
        return true;
    } 
    else{    
        std::cout << "GPU sum is wrong :(\n";
        std::cout << "\tAbsolute difference: "<<diff<<"\n";
        std::cout << "\tRelative difference: "<<diff/n<<"\n";
        return false;
    }
}

int main(){

    using bufferType = float;
    // define input host buffer 
    bufferType h_buffer[N];
    bufferType sum = 0;

    // define device buffer
    bufferType *d_buffer;
    bufferType *d_aux_buffer;
    bufferType* d_result;

    // fill input values - [1, N]
    for(size_t i=0; i<N; i++){
        // h_buffer[i] = static_cast<bufferType>(i+1);
        h_buffer[i] = getRandom<bufferType>();
    }

    size_t size = N*sizeof(bufferType);
    size_t a_n = getGrid(BLOCK, N); // Initial aux buffer length - #blocks

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
    CHECK_CUDA(cudaMemcpy(&sum, d_result, sizeof(bufferType), cudaMemcpyDeviceToHost));

    cudaFree(d_buffer);
    cudaFree(d_aux_buffer);

   std::cout<<"The computed sum is: "<<sum<<std::endl;

   bool valid = testComp<bufferType>(h_buffer, N, sum);
}

