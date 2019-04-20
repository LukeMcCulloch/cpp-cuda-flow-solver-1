#pragma once

#include <stdio.h>
#include "../common/common.h"
#include <cuda_runtime.h>





extern "C" 
__global__ void 
sumArraysOnGPU_1Dgrid1Dblock(float *A, 
                    float *B, float *C, const int N)
{

    // 1D general case: keeps working when arrays get big!
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    while (i < N){ 
        C[i] = A[i] + B[i];
        i += blockDim.x*gridDim.x;
    }
}


// grid 2D block 2D
__global__ void sumMatrixGPU_2Dgrid2Dblock(float *MatA, float *MatB, 
                                           float *MatC, 
                                                        int nx,int ny)
{

    unsigned int ix = threadIdx.x + blockIdx.x * blockDim.x;
    unsigned int iy = threadIdx.y + blockIdx.y * blockDim.y;
    unsigned int idx = iy * nx + ix;

    if (ix < nx && iy < ny)
    {
        MatC[idx] = MatA[idx] + MatB[idx];
    }
}