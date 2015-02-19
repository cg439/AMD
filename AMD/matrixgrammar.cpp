#include <AMD/matrixgrammar.hpp>

namespace AMD {
namespace detail {

void BinaryOp::operator()(ExpressionTree& parent, 
                          ExpressionTree const& rhs) const
{
    ExpressionTree lhs;
    lhs.swap(parent);
    parent.push_back(spirit::utf8_symbol_range_type(&d_op, &d_op+1));
    parent.push_back(lhs);
    parent.push_back(rhs);
}
///< Function used by the BinaryOp struct to process a binary op expression
///  Changes current node in tree to lhs arguement, pushes the operator 
///  followed by the expressions involved

void UnaryOp::operator()(ExpressionTree& expr, 
                         ExpressionTree const& rhs) const
{
    expr.clear();
    expr.push_back(spirit::utf8_symbol_range_type(&d_op, &d_op+1));
    expr.push_back(rhs);
}
///< Function used by the UnaryOp struct to process a unary op
///  As there is no lhs involved in a unary op, it pushes the operator
///  and the affected term

} // namespace detail

} // namespace AMD



