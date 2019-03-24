//
//=================================
// include guard
#ifndef __SOLVERMANAGER_INCLUDED__
#define __SOLVERMANAGER_INCLUDED__

//#include "input.hpp"


class SolverManager{

    public:

        void input_discrete(int argc, char **argv);


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
};



#endif //__TESTS_ARRAY_INCLUDED__