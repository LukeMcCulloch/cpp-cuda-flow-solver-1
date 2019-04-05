#include <cassert>
#include <iostream>
#include <limits>

#include "etops1.hpp"
#include "etscalar.hpp"
#include "etmatrix.hpp"
#include "etops2.hpp"

//#include "array_template.hpp"
//#include "arrayops.hpp"

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
    Array<double> a(np,np), b(np,np), c(np,np), d(np,np);

    //Array2D<double> x(np,np), y(np,np), z(np,np);

    // initialize arrays with some values
    for (int i=0; i<np; ++i) {
         for (int j=0; j<np; ++j) {
            a(i,j) = static_cast <double>(i*(j+1));
            a(i,j) = 1.;//a(i,j) + 5.;
            b(i,j) = a(i,j)+a(i,j);
            c(i,j) = a(i,j)+b(i,j);

            // x(i,j) = static_cast <double>(i*(j+1));
            // x(i,j) = 1.;//x(i,j) + 5.;
            // y(i,j) = x(i,j)+x(i,j);
            // z(i,j) = x(i,j)+y(i,j);
         }
    }
    //...
    

    std::cout << "b: ";
    print(b);

    std::cout << "c: ";
    print(c);

    c = matmul(a,b);
    std::cout << "after c=matmul(a,b) ";
    print(c);
    d = 1.;

    // illegal mixing, need type match:
    // z = matmul(a,x);
    // std::cout << "after z=matmul(a,x) ";
    // print(z);

    std::cout << "c = b + a: \n";
    std::cout.flush();
    c = b + a;
    std::cout << "c = b + a done \n";
    std::cout.flush();
    print(c);
    
    // a = 1.2 * a;  //eapression template supports scalars
    // std::cout << "1.2*a ";
    // print(a);

    // std::cout << "a = c * a";
    // a = c * a;
    // print(a);
    // std::cout << "a = c * a: ";
    // print(a);

    // a = 1.2*a + a*b;
    // std::cout << "1.2*a + a*b: ";
    // print(a);

    // a = b;
    // std::cout << "after a = b: ";
    // print(b);
    // print(a);

    // c = (a*b)+c;
    // std::cout << "after c= a*b+c ";
    // print(c);

    c = (a+b)+c;
    std::cout << "after c= (a+b)+c ";
    print(c);
    
    // c=1.;
    // c = matmul(d,c);
    // std::cout << "after c=matmul(d,c) ";
    // print(c);
    
    
    // std::cout << "b: ";
    // print(b);
    // d = .5*b;
    // c = matmul(d,c);
    // //c = matmul(c+b,d); //still no support for combined & cached terms
    // std::cout << "after c=matmul((1.+b),c) ";
    // print(c);

    // b=1;
    
    // c=1.;
    // c = matmul(b,c);
    // std::cout << "after b=1.;c=1; c=matmul(b,c); c:";
    // print(c);



    return 0;

}