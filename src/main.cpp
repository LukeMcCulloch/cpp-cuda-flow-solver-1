
#include <cassert>
#include <iostream>
#include <limits>

#include "array_template.hpp"
#include "SolverManager.hpp"
#include "input.hpp"
#include "tests_array.hpp"

using namespace std;

int main (int argc, char **argv) {

    SolverManager SM = SolverManager();
    SM.driver(argc, argv);

    arraybasic();

    return 0;
}