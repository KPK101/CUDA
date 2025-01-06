/*
Author: Pranav Kumar Kota
year: 2024
*/

__global__ void naive_kernel(int M, int N, int K, float *A, float *B, float *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < M && col < N) {
        float sum = 0;
        for (int i = 0; i < K; i++) {
            sum += A[row * K + i] * B[i * N + col];
        }
        C[row * N + col] = sum;
    }
}


__global__ void shared_kernel(int M, int N, int K, float *A, float *B, float *C){
    /*
    It is assumde that the block is square. To generalize validity, add additional checks (TBD)
    */

    int globalRow = blockIdx.y*blockDim.y + threadIdx.y;
    int globalCol = blockIdx.x*blockDim.x + threadIdx.x;

    int localRow = threadIdx.y;
    int localCol = threadIdx.x;

    // define shared memory to load tiles of input matrices A & B
    extern __shared__ float sm[];
    float *ATile = sm;
    float *BTile = sm + blockDim.x*blockDim.y;

    // thread sum for output index
    float sum = 0.0f;
    int phases = (K + blockDim.x - 1)/blockDim.x;

    if(globalRow==0 && globalCol==0){
        printf("Phases: %d\n", phases);
    }
    for(int p=0; p<phases; p++){
        __syncthreads();
        // load A into shared memory
        if(globalRow<M && p*blockDim.x + localCol < K){
            ATile[localRow*blockDim.x + localCol] = A[globalRow*K + p*blockDim.x + localCol];
        }
        else{
            ATile[localRow*blockDim.x + localCol] = 0.0f;
        }
        // load B into shared memory
        if(p*blockDim.y + localRow < K && globalCol < N){
            BTile[localRow*blockDim.x + localCol] = B[(p*blockDim.y + localRow)*N + globalCol];
        }
        else{
            BTile[localRow*blockDim.x + localCol] = 0.0f;
        }
        // sync to wait for all data to be loaded
        __syncthreads();
        // perform matrix multiplication between loaded tiles and update sum
        for(int j=0; j<blockDim.x; j++){
            sum += ATile[localRow*blockDim.x + j]*BTile[j*blockDim.x + localCol];
        }
    }

    if(globalRow<M && globalCol<N){
        C[globalRow*N + globalCol] = sum;
    }
}
