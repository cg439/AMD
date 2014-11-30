" Test MatrixMatrixFunc and ScalarMatrixFunc Python binding. "

from setup import *

def test_SymMMF():
    row, col = 128, 128
    
    X = SymMat("X", row, col)
    fX = SymMMF(X, False)

    A = SymMat("A", row, col)
    fA = SymMMF(A, False) #TODO make 2nd argument True when exceptions are fixed
    
    try :
        func = trace(fX*fA)

    except AMDExceptionType, e:
        print 'type = ', type(e)
        print 'e = ', e
        print 'e.args = ', e.args
        print 'e.message = ', e.message
        exception_obj = e.args

    print 'fA = ', fA 
    print 'fX = ', fX

def main():
    """ Test MatrixMatrixFunc and ScalarMatrixFunc Python binding """
    test_SymMMF()
    print 'Done'

if __name__ == '__main__':
    main()

