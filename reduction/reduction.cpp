#define N 1024
#define BLOCK 4
#include <iostream>
#include <cuda_runtime.h>
#include<vector>

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


void displayArray(int* buffer, int n){

    std::cout<<"Displaying buffer -> \n";
    for(int i=0; i<n; i++){
        std::cout<<buffer[i]<<std::endl;
    }    
}

__global__ void reduce(int *buffer, int n){
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


void displayGrid(int block, int n){
    // display grid structure
    std::cout<<"Grid size: ("<<(n-1+2*block)/(2*block)<<", 1, 1)\n";
    std::cout<<"Block size:("<<block<<", 1, 1)\n";
}


int getGrid(int block, int n){
    return (n-1+2*block)/(2*block);
}
    

__global__ void reduceBlock(int *buffer, int* aux_buffer, int n){
  
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

int* deviceReduction(int*d_buffer, int*d_aux_buffer, int n, int stack){
   
    int* result_ptr;
    size_t size = n*sizeof(int);
    int gd = getGrid(BLOCK, n);
    int bid = 0;

    dim3 block(BLOCK, 1, 1);
    dim3 grid(gd, 1, 1);

    int* buffer_read;
    int* aux_buffer_read;
    buffer_read = (int*)malloc(n*sizeof(int));
    aux_buffer_read = (int*) malloc(n*sizeof(int));


    ////////////////////
    // Pre reduction ///
    ////////////////////

    cudaMemcpy(buffer_read, d_buffer, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(aux_buffer_read, d_aux_buffer, size, cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();
    printf("****************************\nstack=%d\n****************************\n",stack);
    printf("---------------------\nPre-reduction\n---------------------\n");    
    printf("\tBuffer:\n\t");

    for(int i=0; i<n; i++){
        if(i%(2*BLOCK)==0){
            printf(" ||| ");
        }
        printf(" %d ,", buffer_read[i]);
        
    }    
    printf(" ||| ");
    printf("\t\nAuxillary Buffer:\n\t");
    
    for(int i=0; i<n; i++){
        printf(" %d ,", aux_buffer_read[i]);
    }
    ///////////////////////////////////////
     
    reduceBlock<<<grid, block>>>(d_buffer, d_aux_buffer, n);
    cudaDeviceSynchronize();

    //////////////////////////////
    ////// Post reduction ////////
    //////////////////////////////
    cudaMemcpy(buffer_read, d_buffer, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(aux_buffer_read, d_aux_buffer, size, cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();

    printf("\n---------------------\nPost-reduction\n---------------------\n");    
    printf("\tBuffer:\n\t");

    for(int i=0; i<n; i++){
        if(i%(2*BLOCK)==0){
            printf(" ||| ");
        }
        printf(" %d ,", buffer_read[i]);
        
    }    
    printf(" ||| ");
    printf("\t\nAuxillary Buffer:\n\t");
    
    for(int i=0; i<n; i++){
        printf(" %d ,", aux_buffer_read[i]);
    }
    printf("\n\n\n");
    ///////////////////////////////////////////

    if(gd==1){
        return d_aux_buffer;
    }
    else{
        result_ptr = deviceReduction(d_aux_buffer, d_buffer, gd, stack + 1);
        return result_ptr;
    }

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
   cudaMalloc((void**)&d_buffer, size);
   cudaMalloc((void**)&d_aux_buffer, size);

   // Copy data into d_buffer
   cudaMemcpy((void*)d_buffer, (void*)h_buffer, size, cudaMemcpyHostToDevice);

   // Call reduction function
   d_result = deviceReduction(d_buffer, d_aux_buffer, N, 0); 

    // Synchronize global context 
    cudaDeviceSynchronize();

   // Copy result[0] to sum
   cudaMemcpy(&sum, d_buffer, sizeof(int), cudaMemcpyDeviceToHost);

   std::cout<<"The computed sum is: "<<sum<<std::endl;
}

