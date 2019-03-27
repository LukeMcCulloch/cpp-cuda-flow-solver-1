//
//=================================
// include guard
#ifndef __SOLVERMANAGER_INCLUDED__
#define __SOLVERMANAGER_INCLUDED__

//#include "input.hpp"


class SolverManager{

    public:

        void input_discrete(int argc, char **argv);
        void driver(int argc, char **argv);
        void startMessage();

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


void SolverManager::driver(int argc, char *argv[]){

    startMessage();

    input_discrete(argc, argv);
    
}

void SolverManager::startMessage(){
    cout << "-------------------------------------------";
    cout << "Startup:" << endl;
    cout << "Stream Function Vorticity Equation Scheme" ;
    cout << "" << endl;
    cout << "Soving the 2D NSE SFVF for Cavity Flow" << endl;
    cout << "-------------------------------------------" ;
}

#endif //__TESTS_ARRAY_INCLUDED__