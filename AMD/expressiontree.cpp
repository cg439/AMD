#include <AMD/expressiontree.hpp>
#include <AMD/exception.hpp>

namespace AMD { namespace detail {

int ExpressionTree::initComplete = 0;
std::tr1::unordered_set<std::string> ExpressionTree::binaryOp; 
std::tr1::unordered_set<std::string> ExpressionTree::unaryOp;
std::tr1::unordered_set<std::string> ExpressionTree::commutativeOp; 

ExpressionTree::ExpressionTree (const std::string& info, 
                                const boost::shared_ptr<Tree>& left, 
                                const boost::shared_ptr<Tree>& right) :
                                Tree(info, left, right)
{
    if (!ExpressionTree::initComplete) {
        ExpressionTree::initComplete = 1;
        binaryOp.insert("+");
        binaryOp.insert("-");
        binaryOp.insert("o");

        unaryOp.insert("'");
        unaryOp.insert("_");
        unaryOp.insert("tr");
        unaryOp.insert("lgdt");
       
        commutativeOp.insert("+");
        commutativeOp.insert("o");
    }
    if (binaryOp.count(info)) {
        // binary op check
        if (!(left) || !(right)) {
            throw AMD::ExceptionImpl(
                APPEND_LOCATION("from ExpressionTree constructor"),
                "Incorrect use of binary operator",
                AMD_INVALID_EXPRESSION);
        }
    } else if (unaryOp.count(info)) {
        // unary op check
        if (!(left) || (right)) {
            throw AMD::ExceptionImpl(
                APPEND_LOCATION("from ExpressionTree constructor"),
                "Incorrect use of unary operator",
                AMD_INVALID_EXPRESSION);
        }
    } else if (info == "-") {
        // negation or minus case
        if (!(left)) {
            throw AMD::ExceptionImpl(
                APPEND_LOCATION("from ExpressionTree constructor"),
                "Incorrect use of negation operator",
                AMD_INVALID_EXPRESSION);
        }
    } else if ((left) || (right)) {
        // leaf node
        throw AMD::ExceptionImpl(
            APPEND_LOCATION("from ExpressionTree constructor"),
            "No operator and not matrix or float",
            AMD_INVALID_EXPRESSION);
    } 

    this->d_info = info;
    this->d_left = left;
    this->d_right = right;
}

ExpressionTree::~ExpressionTree()
{
}

bool ExpressionTree::operator==(const ExpressionTree& other) const 
{
    // Root information
    if (other.d_info != this->d_info) return false;

    int isCommutative = commutativeOp.count(this->d_info);

    // Children pointers are equal
    if (((other.d_right == this->d_right) && (other.d_left == this->d_left))
       || (isCommutative && (other.d_right == this->d_left) && 
            (other.d_left == this->d_right)))
         return true;

    //FIXME: Not sure if we need to do anything special for the case of commutative ops
    // One tree has a child where the other has a null pointer
    if ((!(other.d_right) && this->d_right) 
         || (other.d_right && !(this->d_right))
         || (!(other.d_left) && this->d_left)
         || (other.d_left && !(this->d_left))) return false;

    //check equality where needed avoiding null shared pointer deref
    if (!other.d_right && !this->d_right)
        return *(other.d_left) == *(this->d_left); 
    else if (!other.d_left && !this->d_left) 
        return *(other.d_right) == *(this->d_right);
    else if (isCommutative)
    {
        return ((*(other.d_right) == *(this->d_right))
           && (*(other.d_left) == *(this->d_left)) ||
           (*(other.d_right) == *(this->d_left)) &&
           (*(other.d_left) == *(this->d_right)));
    }
    else {
        return (*(other.d_right) == *(this->d_right))
           && (*(other.d_left) == *(this->d_left));

    }
}


} } // namespace AMD::detail
