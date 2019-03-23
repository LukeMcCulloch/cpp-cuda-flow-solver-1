// class to manage solver data

// #include <cassert>
// #include <iostream>
// #include <limits>

// using namespace std;


class SolverManager{

    public:
        void input_discrete(int argc, char **argv);

    private:
        int NI; // Number of x pts
        int NJ; // Number of y pts
        int nt; // number of time steps
};