/// @file expressiontree.hpp
/// Contains AMD::expressiontree

#ifndef AMD_EXPRESSION_TREE_HPP
#define AMD_EXPRESSION_TREE_HPP

#include <AMD/tree.hpp>
#include <tr1/unordered_set>

typedef std::tr1::unordered_set<std::string> stringSet;

namespace AMD { namespace detail {

class ExpressionTree : public Tree
{
public:
    explicit ExpressionTree (const std::string& info, 
                             const boost::shared_ptr<Tree>& left, 
                             const boost::shared_ptr<Tree>& right);
    virtual ~ExpressionTree();
    bool operator==(const ExpressionTree& other) const; 
private:
/*    static stringSet commutativeOp;
    static stringSet binaryOp;
    static stringSet unaryOp;
*/
    static std::tr1::unordered_set<std::string> commutativeOp;
    static std::tr1::unordered_set<std::string> binaryOp;
    static std::tr1::unordered_set<std::string> unaryOp;

    static int initComplete;
};

} } // namespace AMD::detail

#endif // AMD_EXPRESSION_TREE_HPP
