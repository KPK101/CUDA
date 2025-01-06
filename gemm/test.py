"""
Author: Pranav Kumar Kota
year: 2024
"""
import pycuda.autoinit
import pycuda.driver as cuda
import pycuda.gpuarray as gpuarray
import numpy as np
from pycuda.compiler import SourceModule

BLOCK = (32, 32, 1)
GRID = lambda M, N, BLOCK=BLOCK, : (int(np.ceil(M/BLOCK[0])), int(np.ceil(N/BLOCK[1])), 1)

def gen_matrices(M, K, N):
    A = np.random.randn(M, K).astype(np.float32)
    B = np.random.randn(K, N).astype(np.float32)
    return A, B

def cpu_mm(A, B):
    C = np.dot(A, B)
    return C

def load_module(file):
    kernel = r'{}'.format(open(file).read())
    return SourceModule(kernel)

def naive_mm(A, B, M, K, N, func):
    M = np.int32(M)
    N = np.int32(N)
    K = np.int32(K)
    C = np.zeros((M, N)).astype(np.float32)
    func(M, N, K, cuda.In(A), cuda.In(B), cuda.Out(C), block=BLOCK, grid=GRID(M, N))
    cuda.Context.synchronize()
    return C

def shared_mm(A, B, M, K, N, func):
    M = np.int32(M)
    N = np.int32(N)
    K = np.int32(K)
    C = np.zeros((M, N)).astype(np.float32)
    shared_size = 2 * BLOCK[0] * BLOCK[1] * np.dtype(np.float32).itemsize
    func(M, N, K, cuda.In(A), cuda.In(B), cuda.Out(C), block=BLOCK, grid=GRID(M, N), shared=shared_size)
    return C


def test(BLOCK=BLOCK, dims=[32, 64, 128, 256, 512, 1024]):
    mod = load_module('kernels.cu')
    naive_func = mod.get_function('naive_kernel')
    shared_func = mod.get_function('shared_kernel')
    print("*"*20)
    print(f"BLOCK = {BLOCK}")
    print("*"*20)
    for d in dims:
        M, K, N = d, d, d
        A, B = gen_matrices(M, K, N)
        C_naive = naive_mm(A, B, M, K, N, naive_func)
        C_shared = shared_mm(A, B, M, K, N, shared_func)
        diff = np.abs(C_naive - C_shared)
        print(f"dim = {d} : grid = {GRID(M, N)}: avg diff = {np.mean(diff):.3f}")
        try:
            assert np.allclose(C_naive, C_shared)
            print(f"\033[32mPassed!\033[0m")
        except:
            print(f"\033[31mFailed!\033[0m")

if __name__ == '__main__':
    test()