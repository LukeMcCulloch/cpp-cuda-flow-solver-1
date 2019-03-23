// reading a text file

#include "SolverManager.hpp"
//#include "input.hpp"
//#include "inputFunctionStyle.hpp"

using namespace std;

int main (int argc, char **argv) {

    SolverManager SM = SolverManager();
    SM.input_discrete(argc, argv);

    return 0;
}