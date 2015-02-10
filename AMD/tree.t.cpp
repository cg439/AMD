#include <AMD/tree.hpp>

#define BOOST_TEST_MODULE TreeTest
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <stdexcept>

BOOST_AUTO_TEST_CASE( InvalidMatrixTreeCreationFailure )
{  
    boost::shared_ptr<AMD::detail::Tree> lhs = 
        boost::make_shared<AMD::detail::Tree>("L");  
    boost::shared_ptr<AMD::detail::Tree> rhs = 
        boost::make_shared<AMD::detail::Tree>("R");  
	boost::shared_ptr<AMD::detail::Tree> null;

    BOOST_CHECK_THROW(AMD::detail::Tree plusInvalidTree("+", lhs, null),
                                                        std::runtime_error);
    BOOST_CHECK_THROW(AMD::detail::Tree plusInvalidTree("+", null, null),
                                                        std::runtime_error);
	BOOST_CHECK_THROW(AMD::detail::Tree plusInvalidTree("+", rhs, null),
                                                        std::runtime_error);
	BOOST_CHECK_THROW(AMD::detail::Tree invalidTree("A", lhs, null),
                                                        std::exception);
	BOOST_CHECK_THROW(AMD::detail::Tree invalidTree2("A", rhs, lhs),
                                                        std::exception);
	BOOST_CHECK_THROW(AMD::detail::Tree negInvalidTree("-", null, rhs),
                                                        std::exception);
	BOOST_CHECK_THROW(AMD::detail::Tree invInvalidTree("_", lhs, rhs),
                                                        std::exception);
	BOOST_CHECK_THROW(AMD::detail::Tree tranInvalidTree("'"),std::exception);
	BOOST_CHECK_THROW(AMD::detail::Tree binInvalidTree("+"),std::exception);
	BOOST_CHECK_THROW(AMD::detail::Tree blankTree("", lhs, rhs),
                                                    std::exception);
	BOOST_CHECK_THROW(AMD::detail::Tree blankTree2(""), std::exception);
}

BOOST_AUTO_TEST_CASE( ValidMatrixTreeCreationSuccess )
{
	boost::shared_ptr<AMD::detail::Tree> lhs = 
        boost::make_shared<AMD::detail::Tree>("L");  
    boost::shared_ptr<AMD::detail::Tree> rhs = 
        boost::make_shared<AMD::detail::Tree>("R");  
	boost::shared_ptr<AMD::detail::Tree> bTree = 
        boost::make_shared<AMD::detail::Tree>("B");  
	boost::shared_ptr<AMD::detail::Tree> regTreeShared = 
        boost::make_shared<AMD::detail::Tree>("A");
	boost::shared_ptr<AMD::detail::Tree> null;
	boost::shared_ptr<AMD::detail::Tree> negA = 
        boost::make_shared<AMD::detail::Tree>("-", regTreeShared, null);
	boost::shared_ptr<AMD::detail::Tree> tranA = 
        boost::make_shared<AMD::detail::Tree>("'", regTreeShared, null);
    //needs to be ' null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(AMD::detail::Tree transTree("'",regTreeShared, null));
	
    //needs to be _ null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(AMD::detail::Tree invTree("_", regTreeShared, null));
	
    //needs to be - null A in terms of parent lhs rhs or - A B
	BOOST_CHECK_NO_THROW(AMD::detail::Tree negTree("-", regTreeShared, null));
	BOOST_CHECK_NO_THROW(AMD::detail::Tree negTree("-", bTree, regTreeShared));
	
    //needs to be tr null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(AMD::detail::Tree traceTree("tr", regTreeShared, 
                                                                    null));
	
    //needs to be lgdt null A in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(AMD::detail::Tree logdetTree("lgdt", regTreeShared, 
                                                                    null));
	
	//needs to be * 'A 'B in terms of parent lhs rhs
    BOOST_CHECK_NO_THROW(AMD::detail::Tree mulTree("*", negA, tranA));
}
///Test attempts to create a variety of valid trees composed of several tree nodes
///checks that no exception is thrown by the tree constructor

BOOST_AUTO_TEST_CASE( ValidSwapSuccess )
{ 
	///Creates some basic standalone tree nodes to serve as lhs/rhs args
	boost::shared_ptr<AMD::detail::Tree> bTree = 
        boost::make_shared<AMD::detail::Tree>("B");  
	boost::shared_ptr<AMD::detail::Tree> aTree = 
        boost::make_shared<AMD::detail::Tree>("A");  
	boost::shared_ptr<AMD::detail::Tree> null;
	
	///makes two duplicate trace trees on A
	AMD::detail::Tree trTreeA("tr", aTree, null);
	AMD::detail::Tree trTreeA2("tr", aTree, null);
	
	///makes two duplicate trace trees on B
	AMD::detail::Tree trTreeB("tr", bTree, null);
	AMD::detail::Tree trTreeB2("tr", bTree, null);
	
	///makes two duplicate multiplication trees on A,B
	AMD::detail::Tree mulTree("*", aTree, bTree);
	AMD::detail::Tree mulTree2("*", bTree, aTree);
	
	///makes a multiplication tree of A, A
	AMD::detail::Tree mulTreeA("*", aTree, aTree);
	
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

BOOST_AUTO_TEST_CASE( InvalidSwapFail )
{
    AMD::detail::Tree testTree(" ", boost::shared_ptr<AMD::detail::Tree>(),
                                boost::shared_ptr<AMD::detail::Tree>());
}

/*
BOOST_AUTO_TEST_CASE( ValidEqualsSuccess )
{
    AMD::detail::Tree testTree(" ", boost::shared_ptr<AMD::detail::Tree>(),
                                boost::shared_ptr<AMD::detail::Tree>());
}
BOOST_AUTO_TEST_CASE( InvalidEqualsFails )
{
    AMD::detail::Tree testTree(" ", boost::shared_ptr<AMD::detail::Tree>(),
                                boost::shared_ptr<AMD::detail::Tree>());
}
BOOST_AUTO_TEST_CASE( DestructorSuccess )
{
    AMD::detail::Tree testTree(" ", boost::shared_ptr<AMD::detail::Tree>(),
                                boost::shared_ptr<AMD::detail::Tree>());
}
BOOST_AUTO_TEST_CASE( MirrorEqualsSuccess )
{
    AMD::detail::Tree testTree(" ", boost::shared_ptr<AMD::detail::Tree>(),
                                boost::shared_ptr<AMD::detail::Tree>());
}
BOOST_AUTO_TEST_CASE( MirrorEqualsFail )
{

}

*/
