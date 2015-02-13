#include <AMD/exception.hpp>
#include <AMD/tree.hpp>

#define BOOST_TEST_MODULE TreeTest

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

typedef class AMD::detail::Tree Tree;
typedef std::runtime_error runtime_error;
// typedef std::exception exception; FIXME: typdef not useable
using namespace boost; //shared_ptr, make_shared


BOOST_AUTO_TEST_CASE( InvalidMatrixTreeCreationFailure )
{  
    shared_ptr<Tree> lhs =  make_shared<Tree>("L");
    shared_ptr<Tree> rhs =  make_shared<Tree>("R");
    shared_ptr<Tree> null;
    //AMD_START_TRY_BLOCK();
    
    Tree plusInvalidTree("+", lhs, null);
    
    //AMD_END_TRY_BLOCK();

    
    BOOST_CHECK_THROW(Tree plusInvalidTree("+", lhs, null), runtime_error);
    BOOST_CHECK_THROW(Tree plusInvalidTree("+", null, null),runtime_error);
    BOOST_CHECK_THROW(Tree plusInvalidTree("+", rhs, null), runtime_error);
    BOOST_CHECK_THROW(Tree invalidTree("A", lhs, null), std::exception);
    BOOST_CHECK_THROW(Tree invalidTree2("A", rhs, lhs), std::exception);
    BOOST_CHECK_THROW(Tree negInvalidTree("-", null, rhs), std::exception);
    BOOST_CHECK_THROW(Tree invInvalidTree("_", lhs, rhs), std::exception);
    BOOST_CHECK_THROW(Tree tranInvalidTree("'"),std::exception);
    BOOST_CHECK_THROW(Tree binInvalidTree("+"),std::exception);
    BOOST_CHECK_THROW(Tree blankTree("", lhs, rhs),std::exception);
    BOOST_CHECK_THROW(Tree blankTree2(""), std::exception);
    //AMD_END_TRY_BLOCK();
    //AMD_CATCH_AND_PRINT();
}

BOOST_AUTO_TEST_CASE( ValidMatrixTreeCreationSuccess )
{
    shared_ptr<Tree> lhs =  make_shared<Tree>("L");  
    
    shared_ptr<Tree> rhs = make_shared<Tree>("R");  
    shared_ptr<Tree> bTree = make_shared<Tree>("B");  
    shared_ptr<Tree> regTreeShared =  make_shared<Tree>("A");
    shared_ptr<Tree> null;
    shared_ptr<Tree> negA = make_shared<Tree>("-", regTreeShared, null);
    shared_ptr<Tree> tranA = make_shared<Tree>("'", regTreeShared, null);

    //needs to be ' null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(Tree transTree("'",regTreeShared, null));
    
    //needs to be _ null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(Tree invTree("_", regTreeShared, null));
    
    //needs to be - null A in terms of parent lhs rhs or - A B
    BOOST_CHECK_NO_THROW(Tree negTree("-", regTreeShared, null));
    BOOST_CHECK_NO_THROW(Tree negTree("-", bTree, regTreeShared));
    
    //needs to be tr null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(Tree traceTree("tr", regTreeShared, null));
    
    //needs to be lgdt null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(Tree logdetTree("lgdt", regTreeShared, null));
    
    //needs to be * 'A 'B in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(Tree mulTree("*", negA, tranA));
}
///Test attempts to create a variety of valid trees composed of several tree nodes
///checks that no exception is thrown by the tree constructor

BOOST_AUTO_TEST_CASE( ValidSwapSuccess )
{ 
    ///Creates some basic standalone tree nodes to serve as lhs/rhs args
    shared_ptr<Tree> bTree =  make_shared<Tree>("B");  
    shared_ptr<Tree> aTree =  make_shared<Tree>("A");  
    shared_ptr<Tree> null;
    
    ///makes two duplicate trace trees on A
    Tree trTreeA("tr", aTree, null);
    Tree trTreeA2("tr", aTree, null);
    
    ///makes two duplicate trace trees on B
    Tree trTreeB("tr", bTree, null);
    Tree trTreeB2("tr", bTree, null);
    
    ///makes two duplicate multiplication trees on A,B
    Tree mulTree("*", aTree, bTree);
    Tree mulTree2("*", bTree, aTree);
    
    ///makes a multiplication tree of A, A
    Tree mulTreeA("*", aTree, aTree);
    
    ///checks equality of all duplicate trees
    BOOST_CHECK(trTreeA == trTreeA2);
    BOOST_CHECK(trTreeB == trTreeB2);
    BOOST_CHECK(mulTree == mulTree2);
    
    ///swaps each with their duplicates
    trTreeA.swap(trTreeA2);
    trTreeB.swap(trTreeB2);
    mulTree.swap(mulTree2);
    
    ///confirms equality wasn't changed
    BOOST_CHECK(trTreeA == trTreeA2);
    BOOST_CHECK(trTreeB == trTreeB2);
    BOOST_CHECK(mulTree == mulTree2);
    
    ///swaps A with B
    trTreeA.swap(trTreeB);
    
    ///confirms inequality for duplicates
    ///and equality for swapped pairs 
    BOOST_CHECK(trTreeA != trTreeA2);
    BOOST_CHECK(trTreeB != trTreeB2);
    BOOST_CHECK(trTreeB == trTreeA2);
    BOOST_CHECK(trTreeA == trTreeB2);
    
    ///swaps duplicate of A with duplicate of B
    ///essentially completing the swap of A,A2 with B,B2
    trTreeA2.swap(trTreeB2);
    
    ///confirms equality is restored for duplicates
    ///and inequality exists for non-duplicates
    BOOST_CHECK(trTreeA == trTreeA2);
    BOOST_CHECK(trTreeB == trTreeB2);
    BOOST_CHECK(trTreeB != trTreeA2);
    BOOST_CHECK(trTreeA != trTreeB2);
    
    ///confirms inequality exists for two different trees
    BOOST_CHECK(mulTreeA != mulTree);
    
    ///swaps one of the duplicate trees with a different binop tree
    mulTreeA.swap(mulTree);
    
    ///confirms equality conditions
    BOOST_CHECK(mulTreeA != mulTree);
    BOOST_CHECK(mulTreeA == mulTree2);
    BOOST_CHECK(mulTree != mulTree2);
    
    ///finishes swap, now mulTreeA's value is stored in mulTree2
    ///while the duplicate multrees are in mulTreeA and mulTree
    mulTree2.swap(mulTree);
    
    ///confirms appropriate equality
    BOOST_CHECK(mulTreeA == mulTree);
    BOOST_CHECK(mulTreeA != mulTree2);
    BOOST_CHECK(mulTree != mulTree2);
}

BOOST_AUTO_TEST_CASE( ValidEqualsSuccess )
{
    shared_ptr<Tree> nil;
    shared_ptr<Tree> node1 = make_shared<Tree>("M",nil,nil);
    shared_ptr<Tree> node2 = make_shared<Tree>("M",nil,nil);
    shared_ptr<Tree> node3 = make_shared<Tree>("N",nil,nil);
    shared_ptr<Tree> node4 = make_shared<Tree>("*",node1,node1);
    shared_ptr<Tree> node5 = make_shared<Tree>("*",node1,node2);
    shared_ptr<Tree> node6 = make_shared<Tree>("*",node1,node3);
    shared_ptr<Tree> node7 = make_shared<Tree>("'",node5,nil);
    shared_ptr<Tree> node8 = make_shared<Tree>("'",node4,nil);

    BOOST_CHECK (*node1 == *node2);
    // Single equal node

    BOOST_CHECK (!(*node1 == *node3));
    // Single unequal node

    BOOST_CHECK (*node4 == *node5);
    //* Different tree with different children pointers that hold same values

    BOOST_CHECK (!(*node4 == *node6));
    // Same value in root but different children values

    BOOST_CHECK (!(*node7 == *node6));
    // Different depths

    BOOST_CHECK (*node8 == *node7);
    //* Deeper trees.  Different children pointers with same values
}
// BOOST_AUTO_TEST_CASE( InvalidEqualsFails )
// {
//     Tree testTree(" ", shared_ptr<Tree>(),
//                                 shared_ptr<Tree>());
// }
// BOOST_AUTO_TEST_CASE( DestructorSuccess )
// {
//     Tree testTree(" ", shared_ptr<Tree>(),
//                                 shared_ptr<Tree>());
// }
// BOOST_AUTO_TEST_CASE( MirrorEqualsSuccess )
// {
//     Tree testTree(" ", shared_ptr<Tree>(),
//                                 shared_ptr<Tree>());
// }
// BOOST_AUTO_TEST_CASE( MirrorEqualsFail )
// {

// }


