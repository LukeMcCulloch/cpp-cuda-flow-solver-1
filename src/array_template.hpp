
//=================================
// include guard
#ifndef __ARRAY_TEMPLATE_INCLUDED__
#define __ARRAY_TEMPLATE_INCLUDED__

// array class
#include <cassert>
#include <iostream>
#include <limits>

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



/*Helper class --- expression tempalte
*/
template <typename LHS, typename RHS>
class MatrixSum{
public:
    using value_type = typename LHS::value_type;

    MatrixSum(const LHS& lhs, const RHS& rhs) : rhs(rhs), lhs(lhs) {}
    
    value_type operator() (int x, int y) const  {
        return lhs(x, y) + rhs(x, y);
    }
private:
    const LHS& lhs;
    const RHS& rhs;
};

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
    public:
        int nrows, ncols;
        T** array;
        explicit Array2D(int numrows, int numcols): 
                    nrows(numrows), ncols(numcols){
            build();initialize();
            }
        Array2D();
        //Array2D(int numrows,int numrows);
        //copy constructor of some kind
        Array2D(const Array2D& A);
        ~Array2D ();// {delete array;}

        //methods:
        void build();
        void initialize();
        void print();

       
        // Operators:
        T& operator() (int row, int col);        // Subscript operators in pairs
        const T&  operator() (int row, int col) const;  
        
        Array2D operator = (const Array2D&);
        //Array2D operator + ()  //not a class member!

        
        bracket_proxy<Array2D, T> operator[](int r){
            return bracket_proxy<Array2D, T>(*this, r);
        }
};


template<class T>
Array2D<T>::~Array2D(){
    delete array[0];
    delete array;
}

template <class T>
Array2D<T>::Array2D(){
//Array2D::Array2D(){
    nrows = 4;
    ncols = 4;
    cout << "build \n" << endl;
    build();
    cout << "initialize\n" << endl;
    initialize();
    cout <<"done with init\n"<<endl;
};

// template <class T>
// Array2D<T>::Array2D(int numrows, int numcols){
// //Array2D::Array2D(int numrows, int numcols){
//     nrows = numrows;
//     ncols = numcols;
//     cout << "build \n" << endl;
//     build();
//     cout << "initialize\n" << endl;
//     initialize();
//     cout <<"done with init\n"<<endl;
// };

// copy constructor:
template <class T>
Array2D<T>::Array2D(const Array2D& other)
    : nrows(other.nrows), ncols(other.ncols){
    //nrows = other.nrows;
    //ncols = other.ncols;
    int j = 0;
    int size= nrows*ncols;
    array = new T*[nrows];
    T *adata = new T[size];
    for(j= 0; j < nrows; j++) {
        array[j]= adata + ncols*j;
    }
};



template <class T>
T& Array2D<T>::operator()(int i, int j) {
	check_indices(i,j);
    return array[i][j];
}
template <class T>
const T& Array2D<T>::operator()(int i, int j) const {
	check_indices(i,j);
    return array[i][j];
}


template <class T>
Array2D<T> Array2D<T>::operator=(const Array2D& that) {
	assert(that.nrows == nrows);
	assert(that.ncols == ncols);
    int i, j;
	for ( i=0; i<nrows; ++i){
        for ( j=0; j<ncols;){
    	    array[i][j] = that.array[i][j];
        }
    }
    return *this;
}

// template <class T>
// void Array2D<T>::build(){
// //void Array2D::build(){
//     int j = 0;
//     int size = nrows*ncols;
//     array = new T*[nrows];
//     array[0]= new T[size];
//     for( j= 1; j < nrows; j++) {
//         array[j]= &array[0][j*ncols];
//     }
// };

template <class T>
void Array2D<T>::build(){
//void Array2D::build(){
    int j = 0;
    int size= nrows*ncols;

    array = new T*[nrows];
    T *adata = new T[size];
    for(j= 0; j < nrows; j++) {
        array[j]= adata + ncols*j;
    }
};


// template <class T>
// void Array2D<T>::build(){
// //void Array2D::build(){
//     int i = 0;
//     int size = nrows*ncols;
//     T **array = NULL;
//     T *adata = NULL;
//     array = (T**)malloc(nrows*sizeof(T*));
//     adata = (T*)malloc(size*sizeof(T));
//     for( i= 0; i < nrows; i++) array[i]= adata+ncols*i;
// };


template <class T>
void Array2D<T>::initialize(){
//void Array2D::initialize(){
    int i = 0;
    int j = 0;

    for(i=0; i<nrows; i++){
        for(j=0; j<ncols; j++) {
            int nn = i+j;
            T num = T(10.167);
            array[i][j] = num;//10.167;
        }
    }
};

/*  TODO, use this: 
template <class T>
void Array2D<T>::initialize(T data){
//void Array2D::initialize(){
    int i = 0;
    int j = 0;

    for(i=0; i<nrows; i++){
        for(j=0; j<ncols; j++) {
            array[i][j] = data;
            data++;
        }
    }
};
/**/




template <class T>
Array2D<T> // not tied to one matrix!
operator+(const Array2D<T>& lhs, const Array2D<T>& rhs) {
	assert(lhs.nrows == rhs.nrows);
	assert(lhs.ncols == rhs.ncols);
    int nrows = lhs.nrows;
    int ncols = lhs.ncols;

    Array2D<T> result;

    int i, j;
	for ( i=0; i<nrows; ++i){
        for ( j=0; j<ncols; ++j){
    	    result.array[i][j] = lhs.array[i][j] + rhs.array[i][j];
        }
    }
    return result;
}



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
//void Array2D::print(){
    int i,j;
    int oldp= cout.precision(numeric_limits<T>::digits10 + 1);
    for( i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++) {
            cout << i << " " << j << " " << &array[i][j] << endl;
            cout << array[i][j] << endl;
            //printf("val = %f",array[i][j],"\n" );
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