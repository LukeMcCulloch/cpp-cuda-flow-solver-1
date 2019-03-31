#include <cassert>
#include <iostream>
#include <limits>

#include "etops1.hpp"
#include "etscalar.hpp"
#include "etmatrix.hpp"
#include "etops2.hpp"

// #include "array_template.hpp"
// #include "arrayops.hpp"

using namespace std;


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


int etarraybasic (){

    int np = 3;
    Array<double> x(np,np), y(np,np), z(np,np);
    //Array2D<double> x(np,np), y(np,np), z(np,np);

    // initialize arrays with some values
    for (int i=0; i<np; ++i) {
         for (int j=0; j<np; ++j) {
            x(i,j) = static_cast <double>(i*(j+1));
            x(i,j) = x(i,j) + 5.;
            y(i,j) = x(i,j)+x(i,j);
            z(i,j) = x(i,j)+y(i,j);
         }
    }
    //...
    
    std::cout << "x: ";
    print(x);

    std::cout << "y: ";
    print(y);

    std::cout << "z: ";
    print(z);

    std::cout << "z = y + x: \n";
    std::cout.flush();
    z = y + x;
    std::cout << "z = y + x done \n";
    std::cout.flush();
    print(z);
    
    //x = 1.2 * x;  //no support for scalars just yet:: but scalar(i,j) <=> scalar
    // so in principle it should be possible
    std::cout << "x: ";
    print(x);

    std::cout << "x = z * x";
    x = z * x;
    print(x);
    std::cout << "x = z * x: ";
    print(x);

    x = 1.2*x + x*y;
    std::cout << "1.2*x + x*y: ";
    print(x);

    x = y;
    std::cout << "after x = y: ";
    print(x);
    return 0;

}