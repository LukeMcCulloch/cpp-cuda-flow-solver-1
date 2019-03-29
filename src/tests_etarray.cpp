#include <iostream>


//#include "array_template.hpp"

#include "etops1.hpp"
#include "etscalar.hpp"
#include "etmatrix.hpp"
//#include "etops2.hpp"



template <typename T>
void print (T const& c){
    int ncol = c.getncols();
    int nrow = c.getnrows();
    for (int i=0; i<nrow; ++i) {
        for (int j=0; j<ncol; ++j) {
            std::cout << c(i,j) << ' ';
        }
    }
    std::cout << "..." << std::endl;
}


int etarraybasic (){

    cout.precision(20);
    int n1 = 10;
    int n2 = 20;
    //Array2D <int> self(n1,n2), other(n1,n2);
    //Array2D <int> dself(n1,n2), dother(n1,n2);
    Array <int> self(n1,n2), other(n1,n2);
    Array <float> fself(n1,n2), fother(n1,n2);
    Array <double> dself(n1,n2), dother(n1,n2);

    

    cout << "int array  \n" << endl;
    // initialize arrays with some values
    for (int i=0; i<n1; ++i) {
        for (int j=0; j<n2; ++j) {
        self(i,j) = i+j;
        other(i,j) = self(i,j) + self(i,j);
        }
    }

    cout << "float array  \n" << endl;
    // initialize arrays with some values
    for (int i=0; i<n1; ++i) {
        for (int j=0; j<n2; ++j) {
        fself(i,j) = i+j;
        fother(i,j) = fself(i,j) + fself(i,j);
        }
    }

    cout << "double array  \n" << endl;
    // initialize arrays with some values
    for (int i=0; i<n1; ++i) {
        for (int j=0; j<n2; ++j) {
        dself(i,j) = i+j;
        dother(i,j) = dself(i,j) + dself(i,j);
        }
    }

    
    std::cout << "self: ";
    print(self);
    std::cout << "fself: ";
    print(fself);
    std::cout << "dself: ";
    print(dself);
    // self.setonce(0);

    // cout << "printing int array \n" << endl;
    // self.print();


    // cout << "float array \n" << endl;
    // Array2D <float> yay(2.,2.);
    // cout << "printing float array \n" << endl;
    // yay.setonce(1.1);
    // yay.print();


    // cout << "double array \n" << endl;
    // Array2D <double> da(2.,2.);
    // cout << "printing double array \n" << endl;
    // da.setonce(2.2);
    // da.print();

    // cout << "test copy constructor \n" << endl;
    // Array2D<float> res = Array2D<float>(3,1);
    // res.setonce(42.);
    // cout << "done with copy constructor \n" << endl;
    // res.print();


    // int i=5, j=6, k;
    // double f=2.0, g=0.5, h;
    // k=sum<int>(i,j);
    // h=sum<double>(f,g);
    // cout << k << '\n';
    // cout << h << '\n';


    // cout << "test add\n" << endl;
    // Array2D<float> smat = res + res;
    // cout << "done with add\n" << endl;

    // cout << "test () op \n" << endl;
    // i = 0;
    // j = 0;
    // cout << i << " " << j << " " << res(i,j) << endl;
    // cout << i << " " << j << " " << res[i][j] << endl;
    // cout << i << " " << j << " " << smat[i][j] << endl;

    // std::cout.flush();
    return 0;

}