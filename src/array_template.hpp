
//=================================
// include guard
#ifndef __ARRAY_TEMPLATE_INCLUDED__
#define __ARRAY_TEMPLATE_INCLUDED__

//=================================
// array class
#include <cassert>
#include <iostream>
#include <limits>

//=================================
//CUDA:
#include "../common/common.h"
#include <cuda_runtime.h>
#include <stdio.h>

//=================================
using namespace std;



template <class T>
class Array2D; //fwd declaration



// undefine to disable range checking
#define RANGE_CHECK


class overdetermined : public std::domain_error{

   public:
     overdetermined() 
        : std::domain_error("solution is over-determined")
     {}
};

class underdetermined : public std::domain_error{

   public:
      underdetermined() 
         : std::domain_error("solution is under-determined")
      {}
};



//bracket_proxy is parameterized with Array2D
template <typename ArrayClass, typename Result>
class bracket_proxy{
    public:
        bracket_proxy(ArrayClass& A, int r): A(A), r(r){}

        Result& operator[](int c){return A(r,c); }
    private:
        ArrayClass& A;
        int r;
};



/*Helper class --- expression template (not used)
*/
// template <typename LHS, typename RHS>
// class MatrixSum{
// public:
//     using value_type = typename LHS::value_type;

//     MatrixSum(const LHS& lhs, const RHS& rhs) : rhs(rhs), lhs(lhs) {}
    
//     value_type operator() (int x, int y) const  {
//         return lhs(x, y) + rhs(x, y);
//     }
// private:
//     const LHS& lhs;
//     const RHS& rhs;
// };

//MatrixSum<Matrix<double>, Matrix<double> > SumAB(a, b);





template <class T>
class Array2D{

    void check_indices(int i, int j) const{
        assert(i >= 0 && i < nrows);
        assert(j >= 0 && j < ncols);
    }

    void check_size(int other_nrows,int other_ncols) const { 
        assert(nrows == other_nrows);
        assert(ncols == other_ncols); 
    }

    void check_index(int i) const { assert(i >= 0 && i < nrows); }

    void check_size(int i) const { assert(i >= 0 && i < storage_size); }

    private:
        int nBytes;

    public:

        // set up data size of matrix
        int nrows, ncols;
        int storage_size;

        // malloc host memory
        T* array;
        
        // explicit constructor declaring size nrow,ncol:
        explicit Array2D(int numrows, int numcols): 
                        nrows(numrows), ncols(numcols){
            //cout << "building \n" << endl;
            build();
            //cout << "built \n" << endl;
            //initialize();
            //cout << "initialized \n" << endl;
        }
            
        Array2D();
        
        //copy constructor 
        Array2D(const Array2D& A);

        // destructor
        ~Array2D ();

        //methods:
        void build();
        void buildWithParameters(int, int);
        //void initialize();
        void setonce( T data);
        void print();

       
        void cache() const {}

        // Array2D& val() const {
        //     return *this;
        // }
        Array2D<T> val() const {
            return *this;
        }

        //
        size_t getnrows() const {
            return nrows;
        }
        size_t getncols() const {
            return ncols;
        }
        // return size
        size_t size() const {
            return storage_size;
        }
        
        // Operators:
        T& operator() (int row, int col);        // Subscript operators in pairs
        const T&  operator() (int row, int col) const;  
        
        T& operator() (int i);        // Subscript operator
        const T&  operator() (int i) const;  
        
        
        Array2D operator = (const Array2D&);
        Array2D operator = (const T a);


        // for linear algebra operations see: arrayops.hpp
        
        
        // array[][] access:
        bracket_proxy<Array2D, T> operator[](int r){
            return bracket_proxy<Array2D, T>(*this, r);
        }
};


template<class T>
Array2D<T>::~Array2D(){
    //fixme: CHECK(cudaFree())
    cudaFree(array);
    //delete[] array;
}

template <class T>
Array2D<T>::Array2D(){
    nrows = 4;
    ncols = 4;
    cout << "build \n" << endl;
    build();
    // cout << "initialize\n" << endl;

    memset(array, 0, nBytes);
    // initialize();
    // cout <<"done with init\n"<<endl;
};




// new array:
template <class T>
void Array2D<T>::build(){
    storage_size = nrows*ncols;
    nBytes = storage_size * sizeof(T);
    //array = new T[storage_size];

    //fixme:  use CHECK(cudaMallocManaged();):
    cudaMallocManaged((void **)&array, nBytes);

    //fixeme: use cudaMallocPitch for optimal array padding:
    //cudaMallocPitch(&array, &storage_size,
    //            ncols * sizeof(T), nrows);
};


template <class T>
void Array2D<T>::buildWithParameters(int numrows, int numcols){
    nrows = numrows;
    ncols = numcols;
    build();
};


// copy constructor:
template <class T>
Array2D<T>::Array2D(const Array2D& other)
    : nrows(other.nrows), ncols(other.ncols){
    storage_size = nrows*ncols;
    nBytes = storage_size * sizeof(T);

    //fixme:  see build() above
    cudaMallocManaged((void **)&array, nBytes);

    int i = 0;
    for(i=0; i < storage_size; i++) {
        array[i] = other.array[i];
    }
};



template <class T>
T& Array2D<T>::operator()(int i, int j) {
	check_indices(i,j);
    return array[i*ncols + j];
}
template <class T>
const T& Array2D<T>::operator()(int i, int j) const {
	check_indices(i,j);
    return array[i*ncols + j];
}


template <class T>
T& Array2D<T>::operator()(int i) {
	check_size(i);
    return array[i];
}
template <class T>
const T& Array2D<T>::operator()(int i) const {
	check_size(i);
    return array[i];
}


template <class T>
Array2D<T> Array2D<T>::operator=(const Array2D& that) {
	assert(that.nrows == nrows);
	assert(that.ncols == ncols);
    int i;
    for(i=0; i < storage_size; i++) {
    	array[i] = that.array[i];
    }
    return *this;
}
template <class T>
Array2D<T> Array2D<T>::operator=(const T a) {
    int i;
    for(i=0; i < storage_size; i++) {
    	array[i] = a;
    }
    return *this;
}





/**/  //TODO, use this: 
template <class T>
void Array2D<T>::setonce(T data){
    int i = 0;
    int j = 0;

    for(i=0; i<nrows; i++){
        for(j=0; j<ncols; j++) {
            array[i*ncols + j] = data;
            data++;
        }
    }
}
/**/




// template <class T>
// Array2D<T> 
// operator+(const Array2D<T>& lhs, const Array2D<T>& rhs) {
// 	assert(lhs.nrows == rhs.nrows);
// 	assert(lhs.ncols == rhs.ncols);
//     int nrows = lhs.nrows;
//     int ncols = lhs.ncols;

//     Array2D<T> result;

//     int size = nrows*ncols;
//     int i;
//     for(i=0; i < size; i++) {
//     	result.array[i] = lhs.array[i] + rhs.array[i];
//     }
//     return result;
// }



// // generic expression template helper:
//
// template <typename T1, typename T2>
// class vector_sum{
// public:
//     vector_sum(const V1& v1, const V2& v2): v1(v1) + v2(v2){}

//     using value_type = std::common_type_t<typename T1::value_type,
//                                           typename T2::value_type>;

//     value_type operator[](int i) const {return v1[i] + v2[i];}
// };
//
//
//
// // generic expression template:
//
// template <typename T1, typename T2>
// inline vector_sum<V1,V2> operator +(const V1& x, const V2& y){
//     return {x,y};
// }

// template <typename LHS, typename RHS>
// MatrixSum<LHS, RHS> operator+(const LHS& lhs, const LHS& rhs) {
//     return MatrixSum<LHS, RHS>(lhs, rhs);
// }

// template <class T>
// Array2D<T> operator+(const LHS& lhs, const LHS& rhs) {
//     return MatrixSum<LHS, RHS>(lhs, rhs);
// }




/*
Traits here?
*/
template <class T>
void Array2D<T>::print(){
    int i,j;
    int oldp = cout.precision(numeric_limits<T>::digits10 + 1);
    for( i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++) {
            cout << i << " " << j << " " << &array[i*ncols + j] << endl;
            cout << array[i*ncols + j] << endl;
        }
    }
    cout << "\n" << endl;
    cout.precision(oldp);
}



template <class T>
T sum (T a, T b){
  T result;
  result = a + b;
  return result;
}





#endif //__ARRAY_TEMPLATE_INCLUDED__