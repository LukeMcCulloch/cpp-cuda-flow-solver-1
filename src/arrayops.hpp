

//=================================
// include guard
#ifndef __ARRAYOPS_TEMPLATE_INCLUDED__
#define __ARRAYOPS_TEMPLATE_INCLUDED__

// template <class T>
// class Array2D; //fwd declaration

// #include "array_template.hpp"


// addition of two Array2Ds
template <class T>
Array2D<T> 
operator+(const Array2D<T>& a, const Array2D<T>& b) {
	assert(a.nrows == b.nrows);
	assert(a.ncols == b.ncols);

    Array2D<T> result(a.nrows,a.ncols);

    int size = a.storage_size;
    for(size_t i=0; i < size; i++) {
    	result.array[i] = a.array[i] + b.array[i];
    }
    return result;
}


// multiplication of two Array2Ds
template <class T>
Array2D<T> 
operator*(const Array2D<T>& a, const Array2D<T>& b) {
	assert(a.nrows == b.nrows);
	assert(a.ncols == b.ncols);

    Array2D<T> result(a.nrows,a.ncols);

    int size = a.storage_size;
    for(size_t i=0; i < size; i++) {
    	result.array[i] = a.array[i] * b.array[i];
    }
    return result;
}



// matmul of two Array2D into a third
template <class T>
Array2D<T> 
//matmul(const Array2D<T>& a, const Array2D<T>& b, Array2D<T>& c) {
matmul(const Array2D<T>& a, const Array2D<T>& b) {

	assert(a.ncols == b.nrows);
    //assert(a.nrows == c.nrows);
	//assert(b.ncols == c.ncols);

    Array2D<T> c(a.nrows,b.ncols);
    c = 0.;

    for (size_t i = 0; i < a.nrows; i++) {
        for (size_t k = 0; k < a.ncols; k++) {
            for (size_t j = 0; j < b.ncols; j++) {
                c(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return c;
}


// multiplication of scalar and Array2D
template<typename T>
Array2D<T> operator* (T const& s, Array2D<T> const& a)
{
    Array2D<T> result(a.nrows,a.ncols);
    for (size_t k = 0; k<a.size(); ++k) {
        result[k] = s*a.array[k];
    }
    return result;
}

// multiplication of Array2D and scalar
// addition of scalar and Array2D
// addition of Array2D and scalar
//...




#endif //__ARRAYOPS_TEMPLATE_INCLUDED__