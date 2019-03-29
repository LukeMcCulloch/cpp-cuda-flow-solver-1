
//=================================
// include guard
#ifndef __MATRIX_TEMPLATE_INCLUDED__
#define __MATRIX_TEMPLATE_INCLUDED__


#include <stddef.h>
#include <cassert>
#include "array_template.hpp"

template <typename T, typename Rep = Array2D<T> >
class Array {
  private:
    Rep expr_rep;   // (access to) the data of the array

  public:
    // create array with initial size
    explicit Array (size_t s, size_t t)
     : expr_rep(s,t) {
    }

    // create array from possible representation
    Array (Rep const& rb)
     : expr_rep(rb) {
    }

    // assignment operator for same type
    Array& operator= (Array const& b) { 
        assert(size()==b.size());
        for (size_t idx = 0; idx<b.size(); ++idx) {
            expr_rep[idx] = b[idx];
        }
        return *this;
    }

    // assignment operator for arrays of different type
    template<typename T2, typename Rep2>
    Array& operator= (Array<T2, Rep2> const& b) { 
        assert(size()==b.size());
        for (size_t idx = 0; idx<b.size(); ++idx) {
            expr_rep[idx] = b[idx];
        }
        return *this;
    }


    // size is size of represented data
    size_t getnrows() const {
        return expr_rep.getnrows();
    }
    size_t getncols() const {
        return expr_rep.getncols();
    }

    size_t size() const {
        return expr_rep.size();
    }

    // parens ops:
    T operator()(size_t i, size_t j) const {
        assert(i<getnrows());
        assert(i<getncols());
        return expr_rep.array[i*getncols() + j];
    }
    // self uses this!
    T& operator()(size_t i, size_t j) {
        assert(i<getnrows());
        assert(i<getncols());
        return expr_rep.array[i*getncols() + j];
    }

    // index operator for constants and variables
    // TODO:
    // index operator for constants and variables
    // T operator[] (size_t idx) const {
    //     assert(idx<size());
    //     return expr_rep[idx];
    // }
    // T& operator[] (size_t idx) {
    //     assert(idx<size());
    //     return expr_rep[idx];
    // }

    // return what the array currently represents
    Rep const& rep() const {
        return expr_rep;
    }
    Rep& rep() {
        return expr_rep;
    }
};

#endif //__MATRIX_TEMPLATE_INCLUDED__