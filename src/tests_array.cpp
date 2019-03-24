#include <cassert>
#include <iostream>
#include <limits>

#include "array_template.hpp"

using namespace std;

int arraybasic() {

    cout.precision(20);

    cout << "int array \n" << endl;
    Array2D <int> self(2,2);
    //Array2D self(2,2);
    cout << "printing int array \n" << endl;
    self.print();

    cout << "float array \n" << endl;
    Array2D <float> yay(2.,2.);
    cout << "printing float array \n" << endl;
    yay.print();

    cout << "double array \n" << endl;
    Array2D <double> da(2.,2.);
    cout << "printing double array \n" << endl;
    da.print();

    //test copy constructor:
    Array2D<float> res = Array2D<float>(3,1);
    res.print();


    int i=5, j=6, k;
    double f=2.0, g=0.5, h;
    k=sum<int>(i,j);
    h=sum<double>(f,g);
    cout << k << '\n';
    cout << h << '\n';

    Array2D<float> smat = res + res;

    cout << "test () op \n" << endl;
    i = 0;
    j = 0;
    cout << i << " " << j << " " << res(i,j) << endl;
    cout << i << " " << j << " " << res.array[i][j] << endl;
    cout << i << " " << j << " " << res[i][j] << endl;
    cout << i << " " << j << " " << smat[i][j] << endl;
    return 0;
}