//
//=================================
// include guard
#ifndef __SOLVERMANAGER_INCLUDED__
#define __SOLVERMANAGER_INCLUDED__

//#include "input.hpp"
//#include "geometry.hpp"


#include "../common/common.h"
#include <cuda_runtime.h>
#include <stdio.h>

#include "tests_etarray.cuh"


using namespace std;







class CUDA_handle{
public:
    int dev = 0;
    cudaDeviceProp deviceProp;

    void startCUDA(){

        // set up cuda device
        dev = 0;
        CHECK(cudaGetDeviceProperties(&deviceProp, dev));
        printf("using Device %d: %s\n", dev, deviceProp.name);
        CHECK(cudaSetDevice(dev));
        devprops();
    }

    void checkCUDA(){
        devprops();
    }



    void devprops(){

        int driverVersion = 0, runtimeVersion = 0;
        cudaDriverGetVersion(&driverVersion);
        cudaRuntimeGetVersion(&runtimeVersion);
        printf("  CUDA Driver Version / Runtime Version          %d.%d / %d.%d\n",
            driverVersion / 1000, (driverVersion % 100) / 10,
            runtimeVersion / 1000, (runtimeVersion % 100) / 10);
        printf("  CUDA Capability Major/Minor version number:    %d.%d\n",
            deviceProp.major, deviceProp.minor);
        printf("  Total amount of global memory:                 %.2f GBytes (%llu "
            "bytes)\n", (float)deviceProp.totalGlobalMem / pow(1024.0, 3),
            (unsigned long long)deviceProp.totalGlobalMem);
        printf("  GPU Clock rate:                                %.0f MHz (%0.2f "
            "GHz)\n", deviceProp.clockRate * 1e-3f,
            deviceProp.clockRate * 1e-6f);
        printf("  Memory Clock rate:                             %.0f Mhz\n",
            deviceProp.memoryClockRate * 1e-3f);
        printf("  Memory Bus Width:                              %d-bit\n",
            deviceProp.memoryBusWidth);

        if (deviceProp.l2CacheSize)
        {
            printf("  L2 Cache Size:                                 %d bytes\n",
                deviceProp.l2CacheSize);
        }

        printf("  Max Texture Dimension Size (x,y,z)             1D=(%d), "
            "2D=(%d,%d), 3D=(%d,%d,%d)\n", deviceProp.maxTexture1D,
            deviceProp.maxTexture2D[0], deviceProp.maxTexture2D[1],
            deviceProp.maxTexture3D[0], deviceProp.maxTexture3D[1],
            deviceProp.maxTexture3D[2]);
        printf("  Max Layered Texture Size (dim) x layers        1D=(%d) x %d, "
            "2D=(%d,%d) x %d\n", deviceProp.maxTexture1DLayered[0],
            deviceProp.maxTexture1DLayered[1], deviceProp.maxTexture2DLayered[0],
            deviceProp.maxTexture2DLayered[1],
            deviceProp.maxTexture2DLayered[2]);
        printf("  Total amount of constant memory:               %lu bytes\n",
            deviceProp.totalConstMem);
        printf("  Total amount of shared memory per block:       %lu bytes\n",
            deviceProp.sharedMemPerBlock);
        printf("  Total number of registers available per block: %d\n",
            deviceProp.regsPerBlock);
        printf("  Warp size:                                     %d\n",
            deviceProp.warpSize);
        printf("  Maximum number of threads per multiprocessor:  %d\n",
            deviceProp.maxThreadsPerMultiProcessor);
        printf("  Maximum number of threads per block:           %d\n",
            deviceProp.maxThreadsPerBlock);
        printf("  Maximum sizes of each dimension of a block:    %d x %d x %d\n",
            deviceProp.maxThreadsDim[0],
            deviceProp.maxThreadsDim[1],
            deviceProp.maxThreadsDim[2]);
        printf("  Maximum sizes of each dimension of a grid:     %d x %d x %d\n",
            deviceProp.maxGridSize[0],
            deviceProp.maxGridSize[1],
            deviceProp.maxGridSize[2]);
        printf("  Maximum memory pitch:                          %lu bytes\n",
            deviceProp.memPitch);
        //exit(EXIT_SUCCESS);
    }

};

class SolverManager{

    public:

        void input_discrete(int argc, char **argv);
        void driver(int argc, char **argv);
        void plate();
        void startMessage();
        void initcuda();
        

    private:

        int NI; // Number of x pts
        int NJ; // Number of y pts
        int nt; // number of time steps

        float  lx;  // Length of Plate in X
        float  ly;  // Length of Plate in Y
        float  Xo;  // 00 x
        float  Yo;  // 00 y
        float  C;   // courant number
        float  Re;  // reynolds num

        CUDA_handle cudahandle;
};


void SolverManager::driver(int argc, char *argv[]){

    startMessage();


    input_discrete(argc, argv);

    cout << "Hello plate?" << endl;
    plate();

    initcuda();
    
}

void SolverManager::startMessage(){
    cout << "-------------------------------------------";
    cout << "Startup:" << endl;
    cout << "Stream Function Vorticity Equation Scheme" ;
    cout << "" << endl;
    cout << "Soving the 2D NSE SFVF for Cavity Flow" << endl;
    cout << "-------------------------------------------" ;
}


void SolverManager::initcuda(){
    cout << "-------------------------------------------";
    cout << "Starting CUDA:" << endl;
    cout << "" << endl;
    cudahandle.startCUDA();
    cout << "-------------------------------------------" ;
    
}



#endif //__TESTS_ARRAY_INCLUDED__