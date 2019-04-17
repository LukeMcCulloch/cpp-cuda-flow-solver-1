//=================================
// include guard
#ifndef __TESTS_ETARRAY_INCLUDED__
#define __TESTS_ETARRAY_INCLUDED__

//=================================
// gpu dependencies
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>



//=================================
// the actual function
int etarraybasic();

// class TestArray:
//     public BaseTest01<float, float, 
//                         float, bool>{
//     public:
//         TestArray(); //default constructor
//         void
//         apply(const float &l1,
//             const float &l2,
//             const float &l3, bool &result)
//         {
//             Triangle triangle;
//             result =
//             triangle.setLengths(l1, l2, l3);
//         }
//         const char *getName() const
//         {
//             return "Test setLengths";
//         }
// };

#endif //__TESTS_ETARRAY_INCLUDED__

