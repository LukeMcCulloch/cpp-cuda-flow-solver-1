
#include <cassert>
#include <iostream>
#include <limits>

#include "array_template.hpp"
#include "SolverManager.hpp"
#include "input.hpp"
#include "geometry.hpp"

#include "tests_array.hpp"
#include "tests_etarray.cuh"

#include "../common/common.h"
#include <cuda_runtime.h>
#include <stdio.h>

using namespace std;

int main (int argc, char **argv) {



    // set up cuda device
    int dev = 0;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("using Device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));


    SolverManager SM = SolverManager();
    SM.driver(argc, argv);


    char type;
    do
    {
        cout << "Run some (quick!) tests? (y/n)" << endl;
        cin >> type;
    }
    while( !cin.fail() && type!='y' && type!='n' );

    if ( type =='y' ) {
        //array basic tests
        arraybasic();
        //expression tempalte (et) array basic tests
        etarraybasic();
    }


    // reset cuda device
    CHECK(cudaDeviceReset());

    return 0;
}