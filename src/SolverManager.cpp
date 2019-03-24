// class to manage solver data
#include <cassert>
#include <iostream>
#include <limits>
#include "input.hpp"
#include "array_template.hpp"

using namespace std;


class SolverManager{

    public:
        void input_discrete(int , char **);

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