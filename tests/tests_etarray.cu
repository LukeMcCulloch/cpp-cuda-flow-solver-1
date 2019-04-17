#include <cassert>
#include <iostream>
#include <limits>

#include <cmath>


#include <stdio.h>
#include "../common/common.h"
#include <cuda_runtime.h>

#include "../src/etops1.hpp"
#include "../src/etscalar.hpp"
#include "../src/etmatrix.hpp"
#include "../src/etops2.hpp"

#include "../src/array_template.hpp"
#include "../src/arrayops.hpp"
#include "../src/tests_etarray.cuh"



using namespace std;


//const int THREADWORK = 2;

//const int THREADWORK = 1024;// << 5;
//const int THREADWORK = 1 << 12;

//const int maxThreads = 1 << 20;



// void checkResult(float *hostRef, float *gpuRef, const int N){
    
//     double epsilon = 1.0E-8;
//     bool match = 1;

//     for (int i = 0; i < N; i++){

//         if (abs(hostRef[i] - gpuRef[i]) > epsilon){
        
//             match = 0;
//             printf("Arrays do not match!\n");
//             printf("host %5.2f gpu %5.2f at current %d\n", hostRef[i],
//                    gpuRef[i], i);
//             break;
//         }//else{
//           //  printf("host %5.2f gpu %5.2f at current %d\n", hostRef[i],
//             //       gpuRef[i], i);
//         //}
//     }

//     if (match) printf("Arrays match.\n\n");

//     return;
// }


template <typename T>
void print (T const& c){

    int ncol = c.getncols();
    int nrow = c.getnrows();
    for (int i=0; i<nrow; ++i) {
        std::cout << '\n';
        for (int j=0; j<ncol; ++j) {
            std::cout << c(i,j) << ' ';
        }
    }
    std::cout << "\ndone \n" << std::endl;
}

template <typename T, typename R>
void compare (T const& c, R const& z, 
                const std::string& input){
    // this string pass makes a copy ;-)

    int ncols = c.getncols();
    int nrows = c.getnrows();
    std::cout << "checking simple " << input <<"\n";
    for (size_t i = 0; i < nrows; i++) {
        for (size_t j = 0; j < ncols; j++) {
            assert( c(i,j) == z(i,j) );
        }
    }
    std::cout << "simple " <<  input <<" OK \n\n";
}




// __global__ void sumArraysOnGPU(float *A, float *B, float *C, const int N){

//     // 1D general case: keeps working when arrays get big:
//     int i = blockIdx.x * blockDim.x + threadIdx.x;
//     while (i < N){ 
//         C[i] = A[i] + B[i];
//         i += blockDim.x*gridDim.x;
//     }
// }


__global__ void helloFromGPUthread(){

    int i = threadIdx.x;
    printf("Hellow World GPU id %d \n", i);
}

void helloFromCpu(){

    printf("---------------------\n");
    for (int i =0; i<1; i++)
    {
        printf("Hello World from CPU!\n");
    }
    printf("---------------------\n");
}



void devprops(int dev, 
                int driverVersion, 
                int runtimeVersion,
                cudaDeviceProp deviceProp){
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
    exit(EXIT_SUCCESS);
}



int etarraybasic (){


    /* set up device: 
       nvcc required! */
//     int dev = 0, driverVersion = 0, runtimeVersion = 0;
//     cudaDeviceProp deviceProp;
//     CHECK(cudaGetDeviceProperties(&deviceProp, dev));
//     printf("Using Device %d: %s\n", dev, deviceProp.name);
//     CHECK(cudaSetDevice(dev));



    int np = 5;
    //int nrows = np;
    //int ncols = np;
    Array<double> a(np,np), b(np,np), c(np,np), d(np,np);

    Array2D<double> x(np,np), y(np,np), z(np,np), w(np,np);

    // initialize arrays with some values
    for (int i=0; i<np; ++i) {
         for (int j=0; j<np; ++j) {
            a(i,j) = static_cast <double>(i*(j+1));
            a(i,j) = 1.;//a(i,j) + 5.;
            b(i,j) = a(i,j)+a(i,j);
            c(i,j) = a(i,j)+b(i,j);

            x(i,j) = static_cast <double>(i*(j+1));
            x(i,j) = 1.;//x(i,j) + 5.;
            y(i,j) = x(i,j)+x(i,j);
            z(i,j) = x(i,j)+y(i,j);
         }
    }
    //...
    
    std::cout << "\n\n-----------------------------\n";
    std::cout << "\n\n-----------------------------\n";
    std::cout << "\n\n Welcome to the Test Folder! \n";
    std::cout << "\n\nTesting basic array class  \n";
    std::cout << "against  \n";
    std::cout << "Expression Template array class  \n";
    std::cout << "-----------------------------\n\n";
    std::cout << "\n\n-----------------------------\n";

    std::cout << "b: ";
    print(b);

    std::cout << "c: ";
    print(c);


    std::cout << "y: ";
    print(y);

    std::cout << "z: ";
    print(z);



    z = matmul(x,y);
    std::cout << "xfter z=matmul(x,y) ";
    print(z);
    d = 1.;

    c = matmul(a,b);
    std::cout << "after c=matmul(a,b) ";
    print(c);
    d = 1.;

    compare(c,z,"matmul");

    std::cout << "c = b + a: \n";
    std::cout.flush();
    c = b + a;
    std::cout << "c = b + a done \n";
    std::cout.flush();
    print(c);

    std::cout << "z = y + x: \n";
    std::cout.flush();
    z = y + x;
    std::cout << "z = y + x done \n";
    std::cout.flush();
    print(z);


    compare(c,z,"elementwise addition");

    
    a = 1.2 * a;  //expression template supports scalars
    std::cout << "1.2*a ";
    print(a);

    x = 1.2 * x;  //expression template supports scalars
    std::cout << "1.2*x ";
    print(x);


    compare(a,x,"scalar + matrix addition");

    std::cout << "a = c * a";
    a = c * a;
    print(a);
    std::cout << "a = c * a: ";
    print(a);


    std::cout << "x = z * x";
    x = z * x;
    print(x);
    std::cout << "x = z * x: ";
    print(x);

    compare(a,x,"elementwise matrix multiplication");


    a = 1.2*a + a*b;
    std::cout << "1.2*a + a*b: ";
    print(a);


    x = 1.2*x + x*y;
    std::cout << "1.2*x + x*y: ";
    print(x);

    compare(a,x,"scalar * matrix multiplication");

    a = b;
    std::cout << "after a = b: ";
    print(b);
    print(a);

    x = y;
    std::cout << "xfter x = y: ";
    print(y);
    print(x);

    compare(a,y,"crossed eualtiy");
    compare(b,x,"crossed equality");

    c = (a*b)+c;
    std::cout << "after c= (a*b)+c ";
    print(c);


    z = (x*y)+z;
    std::cout << "xfter z= (x*y)+z ";
    print(z);
    compare(c,z,"(mat * mat) + mat combined");


    c = (a+b)+c;
    std::cout << "after c= (a+b)+c ";
    print(c);
    
    z = (x+y)+z;
    std::cout << "xfter z= (x+y)+z ";
    print(z);

    compare(c,z,"(mat + mat) + mat combined");


    d=1.;
    c = matmul(d,c);
    std::cout << "after c=matmul(d,c) ";
    print(c);

    w=1.;
    z = matmul(w,z);
    std::cout << "xfter z=matmul(w,z) ";
    print(z);
    
    compare(c,z,"(matmul");
    



    std::cout << "b: ";
    print(b);
    //d = .5*b;
    compare(b,y,"b,y");

    //c = matmul(d,c);
    c = matmul((c+.5*d),d); //still no support for combined & cached terms
    std::cout << "after c=matmul((1.+b),c) ";
    print(c);

    
    std::cout << "y: ";
    print(y);
    //w = .5*y;
    compare(d,w,"d,w");

    //z = matmul(w,z);
    z = matmul((z+.5*w),w); //still no support for zomyinew & zxzhew terms
    std::cout << "xfter z=matmul((1.+y),z) ";
    print(z);


    compare(c,z,"compound mat + (scalar * mat )matmul mat");



    b=1;
    
    c=1.;
    c = matmul(b,c);
    std::cout << "after b=1.;c=1; c=matmul(b,c); c:";
    print(c);


    y=1;
    
    z=1.;
    z = matmul(y,z);
    std::cout << "xfter y=1.;z=1; z=matmul(y,z); z:";
    print(z);


    compare(c,z,"matmul");


    
    std::cout << "\n\n-----------------------------\n";
    std::cout << "\n\nTesting basic array class  \n";
    std::cout << "against  \n";
    std::cout << "Expression Template array class  \n";

    std::cout << "result:  \n";
    std::cout << "         all tests pass  \n";
    std::cout << "-----------------------------\n\n";


    // printf("---------------------\n");
    // // GPU call:
    // helloFromGPU<<<1, 10>>>();
    // //CHECK(cudaDeviceSynchronize());
    // helloFromGPUthread<<<1, 10>>>();
    // CHECK(cudaDeviceReset());
    // printf("---------------------\n");



    helloFromCpu();
    helloFromGPUthread<<<1, 10>>>();
    CHECK(cudaDeviceReset());

    return 0;

}