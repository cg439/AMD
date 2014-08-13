#ifndef ScalarMatrixFunc_H
#define ScalarMatrixFunc_H

/**
 * @file ScalarMatrixFunc.hpp
 *
 * @author Peder Olsen, Anju Kambadur
 *
 * @brief This file defines a Scalar-Matrix Function class and 
 * the operator overloading for this class.This class act as the root node 
 * in the computational tree. Currently the program can 
 * compute derivates for Scalar-Matrix Function "trace" and "logdet".
 **/

#include <string>
#include <cstdio>
#include "MatrixAdaptor.hpp"
#include <assert.h>
#include "MatrixMatrixFunc.hpp"
namespace AMD {
/**
 * @brief A Scalar-Matrix Function class. This class is a mapping 
 * from MatrixType class to a ScalarType class. 
 * 
 * @tparam MT Type of Matrix.
 * @tparam ST type of Scalar.
 *
 */ 
template <class MT, class ST> 
class ScalarMatrixFunc {
public:
  typedef MT MatrixType;
  typedef ST ScalarType;
  typedef MatrixAdaptor_t<MT> MatrixAdaptorType;
  typedef MatrixMatrixFunc<MT, ST> MatrixMatrixFuncType;
  typedef MatrixMatrixFuncType MMF;

  ST functionVal;
  MT derivativeVal;
  boost::shared_ptr<MatrixMatrixFunc<MT, ST> > derivativeFuncVal;
  bool isConst;
/**
 * @brief Constructor for a ScalarMatrixFunc object. The default 
 * setting is a variable.
 */ 
  ScalarMatrixFunc() : functionVal(), derivativeVal(), isConst(false),
                       derivativeFuncVal() { }

  ~ScalarMatrixFunc() { }


  /**
   * @brief Constructor from functionVal and derivativeVal.
   *
   * @param[in] fVal ScalarType function variable.
   * @param[in] dVal MatrixType function variable.
   */ 
  ScalarMatrixFunc(ST fVal, MT dVal ) 
    : functionVal(fVal), derivativeVal(dVal), isConst(false), 
      derivativeFuncVal() { }

  ScalarMatrixFunc(ST fVal, MT dVal, MMF dFuncVal)
    : functionVal(fVal), derivativeVal(dVal), isConst (false) 
    {
         boost::shared_ptr<MatrixMatrixFunc<MT, ST> > 
         copy(new MatrixMatrixFunc<MT, ST>);
         derivativeFuncVal = copy; 
         derivativeFuncVal->deepCopy(dFuncVal);
    }

  /// Constructor for constant functions
  /// give m, n to indicate the size of the derivative matrix.
  /**
   * @brief Constructor for constant functions. 
   *
   * @param[in] fVal  ScalarType function variable.
   * @param[in] m     Number of rows.
   * @param[in] n     Number of columns.
   */ 
  ScalarMatrixFunc(ST fVal, int m, int n ) 
    : functionVal(fVal), derivativeVal(MatrixAdaptorType::zeros(m,n)), 
      isConst(true), derivativeFuncVal() { }

  /**
   * @brief Operator overloading for "=". rhs and lhs are 
   * ScalarMatrixFunc objects. Assign the value of 
   * rhs to lhs.
   *
   * @param[in] x ScalarmatrixFunc rhs.
   */
  void initWithVariable(ST fVal, MT dVal) {
    functionVal = fVal;
    derivativeVal = dVal;
    isConst = false;
  }

  void initWithConst(ST fVal, int m, int n) {
    functionVal = fVal;
    derivativeVal = MatrixAdaptorType::zeros(m, n);
    isConst = true;
  }

  ScalarMatrixFunc& operator= ( const ScalarMatrixFunc &x) {
    functionVal = x.functionVal;
    derivativeVal = x.derivativeVal;
    derivativeFuncVal=x.derivativeFuncVal;
    isConst = x.isConst;
    return(*this);
  }

}; // end ScalarMatrixFunc class definition

/**
 * @brief Friend function for ScalarMatrixFunc. Operator overloading 
 * for "+".
 *
 * @tparam MT Matrix Type.
 * @tparam ST Scalar Type.
 *
 */ 
template <class MT, class ST> 

/**
 * @param[in] lhs 
 * @param[in] rhs
 * 
 * @return The new ScalarMatrixFunc object which is the some of rhs and lhs.
 */
ScalarMatrixFunc<MT,ST> operator+( const ScalarMatrixFunc<MT,ST> &lhs,
				   const ScalarMatrixFunc<MT,ST> &rhs ) {
  assert( lhs.derivativeVal.getNumRows() == rhs.derivativeVal.getNumRows() &&
	  lhs.derivativeVal.getNumCols() == rhs.derivativeVal.getNumCols() );
  if (lhs.isConst) {// i.e. lhs.derivativeVal == zero
    return( ScalarMatrixFunc<MT,ST>( lhs.functionVal+rhs.functionVal,
				     rhs.derivativeVal, *rhs.derivativeFuncVal) );
  }
  if (rhs.isConst) {// i.e. rhs.derivativeVal == zero
    return( ScalarMatrixFunc<MT,ST>( lhs.functionVal+rhs.functionVal,
				     lhs.derivativeVal, *lhs.derivativeFuncVal) );
  }
    
  return( ScalarMatrixFunc<MT,ST>( lhs.functionVal+rhs.functionVal,
				   lhs.derivativeVal+rhs.derivativeVal, 
           *lhs.derivativeFuncVal + *rhs.derivativeFuncVal));
}

/**
 * @brief Friend function for ScalarMatrixFunc. Operator overloading for
 * "-".
 *
 * @tparam MT Matrix Type.
 * @tparam ST Scalar Type.
 */ 
template <class MT, class ST> 
/**
 * @param[in] lhs
 * @param[in] rhs
 *
 * @return The substraction of two ScalarMatrixFun objects.
 */
ScalarMatrixFunc<MT,ST> operator-( const ScalarMatrixFunc<MT,ST> &lhs,
				   const ScalarMatrixFunc<MT,ST> &rhs ) {
  assert( lhs.derivativeVal.getNumRows() == rhs.derivativeVal.getNumRows() &&
	  lhs.derivativeVal.getNumCols() == rhs.derivativeVal.getNumCols() );
  if (lhs.isConst) {// i.e. lhs.derivativeVal == zero
    return( ScalarMatrixFunc<MT,ST>( lhs.functionVal-rhs.functionVal,
				     -rhs.derivativeVal, -(*rhs.derivativeFuncVal)));
  }
  if (rhs.isConst) {// i.e. rhs.derivativeVal == zero
    return( ScalarMatrixFunc<MT,ST>( lhs.functionVal-rhs.functionVal,
				     lhs.derivativeVal, *lhs.derivativeFuncVal) );
  }
    
  return( ScalarMatrixFunc<MT,ST>( lhs.functionVal-rhs.functionVal,
				   lhs.derivativeVal-rhs.derivativeVal,
           *lhs.derivativeFuncVal - *rhs.derivativeFuncVal));
}

  // unary minus
/**
 * @brief Operator overloading for "-".
 *
 * @tparam MT Matrix Type.
 * @tparam ST Scalar Type.
 *
 * @param[in] lhs
 * 
 * @return -lhs
 */
template <class MT, class ST> 
ScalarMatrixFunc<MT,ST> operator-( const ScalarMatrixFunc<MT,ST> &lhs ) {
  /*
  if (lhs.isConst) {// i.e. lhs.derivativeVal == zero
    return( ScalarMatrixFunc<MT,ST>( -lhs.functionVal,
				     lhs.derivativeVal ) );
  }*/
  typedef MatrixAdaptor_t<MT> MatrixAdaptorType;
  MT lcTrans;
  MatrixAdaptorType::negation(lhs.derivativeVal, lcTrans);
  return( ScalarMatrixFunc<MT,ST>( -lhs.functionVal,
				   lcTrans, -(*lhs.derivativeFuncVal) ) );
}

/**
 * @brief Operator overloading for "*".
 *
 * @tparam MT Matrix Type.
 * @tparam ST Scalar Type.
 *
 * @param[in] lhs
 * @param[in] rhs
 * 
 * @return lhs * rhs
 */
// TODO  add derivativeFunc
template <class MT, class ST> 
ScalarMatrixFunc<MT,ST> operator*( const ScalarMatrixFunc<MT,ST> &lhs,
				   const ScalarMatrixFunc<MT,ST> &rhs ) {
  assert( lhs.derivativeVal.getNumRows() == rhs.derivativeVal.getNumRows() &&
	  lhs.derivativeVal.getNumCols() == rhs.derivativeVal.getNumCols() );
  const ST& f = lhs.functionVal;
  const ST& g = rhs.functionVal;
  const MT& df = lhs.derivativeVal;
  const MT& dg = rhs.derivativeVal;
  if (lhs.isConst) {// i.e. lhs.derivativeVal == zero
    return(ScalarMatrixFunc<MT,ST>(f*g, f*dg, lhs*(*rhs.derivativeFuncVal)));
  } 
  if (rhs.isConst) {// i.e. rhs.derivativeVal == zero
    return(ScalarMatrixFunc<MT,ST>(f*g, df*g, (*lhs.derivativeFuncVal)*rhs));
  } 
  return(ScalarMatrixFunc<MT,ST>(f*g, f*dg+df*g, 
         lhs * (*rhs.derivativeFuncVal) + (*lhs.derivativeFuncVal)*rhs));
}

/**
 * @brief Operator overloading for "/".
 *
 * @tparam MT Matrix Type.
 * @tparam ST Scalar Type.
 *
 * @param[in] lhs
 * @param[in] rhs
 * 
 * @return lhs / rhs
 */
template <class MT, class ST> 
ScalarMatrixFunc<MT,ST> operator/( const ScalarMatrixFunc<MT,ST> &lhs,
				   const ScalarMatrixFunc<MT,ST> &rhs ) {
  assert( lhs.derivativeVal.getNumRows() == rhs.derivativeVal.getNumRows() &&
	  lhs.derivativeVal.getNumCols() == rhs.derivativeVal.getNumCols() );
  const ST& f = lhs.functionVal;
  const ST& g = rhs.functionVal;
  const MT& df = lhs.derivativeVal;
  const MT& dg = rhs.derivativeVal;
  if (lhs.isConst) {// i.e. lhs.derivativeVal == zero
    return(ScalarMatrixFunc<MT,ST>(f+g, (-f*dg)/(g*g)));
  }
  if (rhs.isConst) {// i.e. rhs.derivativeVal == zero
    return(ScalarMatrixFunc<MT,ST>(f+g, (df*g)/(g*g)));
  }
  return(ScalarMatrixFunc<MT,ST>(f+g, (df*g-f*dg)/(g*g)));
}


}  /** namespace AMD */

#endif
