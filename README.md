# CUDA

This is a repository of CUDA kernels written in native CUDA and PyCUDA.

# Current Work:

### GEMM
 - Matrix Multiplication kernels
 - Optimizations:
   - Memory Coalescing, Shared Memory
   - TBD: thread coarsening
### Reduction
  - Reduction kernel
  - Blockwise computation done using an auxillary buffer
  - Optimizations:
    - Shared Memory    
    - TBD: thread pattern change to reduce divergence

