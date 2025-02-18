# CUDA

This is a repository of CUDA kernels written in native CUDA and PyCUDA.

# Current Work:

### GEMM
 - Matrix Multiplication kernels
 - Optimizations included memory coalescing, shared memory
 - TBD: thread coarsening
### Reduction
  - Reduction kernel
  - Blockwise computation done using an auxillary buffer
  - TBD: thread pattern change to reduce divergence, shared memory

