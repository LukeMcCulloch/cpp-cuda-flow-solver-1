



#include <stddef.h>
#include <cassert>

// include helper class traits template to select whether to refer to an
// ``expression template node'' either ``by value'' or ``by reference.''
#include "etops1a.hpp"



using namespace std;

// class for objects that represent the addition of two operands
template <typename T, typename OP1, typename OP2>
class A_Add {
  private:
    typename A_Traits<OP1>::ExprRef op1;    // first operand
    typename A_Traits<OP2>::ExprRef op2;    // second operand

  public: 
    // constructor initializes references to operands
    A_Add (OP1 const& a, OP2 const& b)
     : op1(a), op2(b) {
    }

    //compute sum when value requested
    T operator()(size_t i, size_t j) const{
        assert(i<op1.getnrows());
        assert(j<op1.getncols());
        return op1(i,j) + op2(i,j);
    }

    // size is maximum size
    size_t size() const {
        assert (op1.size()==0 || op2.size()==0
                || op1.size()==op2.size());
        return op1.size()!=0 ? op1.size() : op2.size();
    }

    
      size_t getnrows() const {
          assert (op1.getnrows()==0 || op2.getnrows()==0
                || op1.getnrows()==op2.getnrows());
          return op1.getnrows()!=0 ? op1.getnrows() : op2.getnrows();
      }
      
      size_t getncols() const {
          assert (op1.getncols()==0 || op2.getncols()==0
                || op1.getncols()==op2.getncols());
          return op1.getncols()!=0 ? op1.getncols() : op2.getncols();
      }

      // size_t getnrows() const {
      //     return op1.getnrows();
      // }
      
      // size_t getncols() const {
      //     return op1.getncols();
      // }

};




// class for objects that represent the multiplication of two operands
template <typename T, typename OP1, typename OP2>
class A_Mult {
  private:
    typename A_Traits<OP1>::ExprRef op1;    // first operand
    typename A_Traits<OP2>::ExprRef op2;    // second operand

  public:
    // constructor initializes references to operands
    A_Mult (OP1 const& a, OP2 const& b)
     : op1(a), op2(b) {
    }


    // compute product when value requested
    T operator() (size_t i, size_t j) const {
        return op1(i,j) * op2(i,j);
    }

    // size is maximum size
    size_t size() const {
        assert (op1.size()==0 || op2.size()==0
                || op1.size()==op2.size());
        return op1.size()!=0 ? op1.size() : op2.size();
    }

    
      size_t getnrows() const {
          assert (op1.getnrows()==0 || op2.getnrows()==0
                || op1.getnrows()==op2.getnrows());
          return op1.getnrows()!=0 ? op1.getnrows() : op2.getnrows();
      }

      size_t getncols() const {
          assert (op1.getncols()==0 || op2.getncols()==0
                || op1.getncols()==op2.getncols());
          return op1.getncols()!=0 ? op1.getncols() : op2.getncols();
      }
};




// class for objects that represent the matrix multiplication of two operands
template <typename T, typename OP1, typename OP2>
class MatMult {
  private:
    typename A_Traits<OP1>::ExprRef op1;    // first operand
    typename A_Traits<OP2>::ExprRef op2;    // second operand

  public:

  
    // constructor initializes references to operands
    MatMult (OP1 const& a, OP2 const& b)
     : op1(a), op2(b) {
    }


    // compute product when value requested
    T operator() (size_t i, size_t j) const {
        return op1(i,j) * op2(i,j);
    }

    // size is maximum size
    size_t size() const {
        assert (op1.size()==0 || op2.size()==0
                || op1.size()==op2.size());
        return op1.size()!=0 ? op1.size() : op2.size();
    }

    
      size_t getnrows() const {
          assert (op1.getnrows()==0 || op2.getnrows()==0
                || op1.getnrows()==op2.getnrows());
          return op1.getnrows()!=0 ? op1.getnrows() : op2.getnrows();
      }

      size_t getncols() const {
          assert (op1.getncols()==0 || op2.getncols()==0
                || op1.getncols()==op2.getncols());
          return op1.getncols()!=0 ? op1.getncols() : op2.getncols();
      }
};
