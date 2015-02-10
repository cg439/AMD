#include <AMD/tree.hpp>
#include <boost/log/trivial.hpp>
#include <exception>
#include <stdexcept>

namespace AMD { namespace detail {

Tree::Tree (const std::string& info, 
            const boost::shared_ptr<Tree>& left, 
            const boost::shared_ptr<Tree>& right)
{
    
    try{
        ///if binop then no null lhs or rhs allowed
        if (d_info == "+" || d_info == "*"
        || d_info == "o") {
            if ((left) && (right)){
                this->d_info = info;
                this->d_left = left;
                this->d_right = right;
            }
            else {
                throw std::runtime_error("Invalid parameters detected.");
            }
        }
        ///if unary op then check for lhs non-null rhs null
        else if (d_info == "'" || d_info == "_"
        || d_info == "tr" || d_info == "lgdt") {
            if ((left) && !(right)){
                this->d_info = info;
                this->d_left = left;
                this->d_right = right;
            }
            else {
                throw std::runtime_error("Invalid parameters detected.");
            }
        }
        ///for special case of neg/subtraction op
        ///check if lhs is non-null
        else if (d_info == "-"){
            if ((left)) {
                this->d_info = info;
                this->d_left = left;
                this->d_right = right;
            }
            else{
                throw std::runtime_error("Invalid parameters detected.");
            }
        }
        ///if any double string or name of a matrix then just check null child
        else if (!(left) && !(right)){
            this->d_info = info;
            this->d_left = left;
            this->d_right = right;
        }
        
        else {
            throw std::runtime_error("Invalid parameters detected."); 
        }
    }
    catch (std::exception& e) {
    ///    BOOST_LOG_TRIVIAL(error) << "Invalid string parameters not accepted for Tree";
    }
}

Tree::Tree (const std::string& info)
{
    boost::shared_ptr<Tree> null;
    try {
        ///invalid string not accepted
        if ((info == "") || (info == "'") || (info == "_") || (info == "-") || 
        (info == "+") || (info == "*") || (info == "o") || (info == "tr") ||
        (info == "lgdt")) {
            throw std::runtime_error("Invalid parameters detected."); 
        }
        this->d_info = info;
        this->d_left = null;
        this->d_right = null;
    }
    catch (std::exception& e) {
    ///    BOOST_LOG_TRIVIAL(error) << "Invalid string parameters not accepted for Tree";
    }
}
                   
Tree::~Tree()
{

}

void Tree::swap(Tree& other)
{
    ///check for null nodes otherwise swap and recurse
    /*if (!(other)){ 
        return;
    }*/
    std::swap(other.d_info, this->d_info);
    this->d_left.swap(other.d_left);
    this->d_right.swap(other.d_right);
}

bool Tree::isLeafNode()
{
    return !(this->d_left) && !(this->d_right);

}

std::string Tree::info() const
{
    return this->d_info;
}

void Tree::setInfo(const std::string& info)
{
    this->d_info = info;
}

bool Tree::operator==(const Tree& other) const
{

    return other.d_info == this->d_info &&
        other.d_left == this->d_left &&
        other.d_right == this->d_right;
    /* commented out the attempted expansion on the logic for equality
    ///comparison with NULL is false
    if (!other) {
        return false;
    }    
    ///check that neither side is null
    else if ((this->d_left) && (this->d_right) 
               && (other->d_left) && (other->d_right)){
        ///check if A:strings match and
        ///either if l1 != l2 && r1 != r2
        ///and if l1 != r2 && l2 != r1
        ///essentially ensure that the values are same and structure is same
        ///if both A and B are true then the trees must be equal
        return 
        ((other.d_info) == (this->d_info) &&
        ((other.d_left) == *(this->d_left) &&
        (other.d_right) == *(this->d_right)) ||
        ((other.d_left) == *(this->d_right) &&
        (other.d_right) == *(this->d_left)));
    }
    ///check if rhs is null in case of unary operator trees
    else if ( (this->d_left) && (other->d_left) && 
              !(this->d_right) && !(other->d_right)){
        return ((other.d_info) == (this->d_info) &&
            (other.d_left) == *(this->d_left);
    }    
    else {
        bool infoCheck = (this->d_info) == (other->d_info);
        bool childCheck = (this->d_left) == (other->d_left) 
                        && (this->d_right) == (other->d_right) ||
                        (this->d_left) == (other->d_right) 
                        && (this->d_right) == (other->d_left);
    }*/
}

bool Tree::operator!=(const Tree& other) const
{
     return !(other == *this);
}

} } // namespace AMD::detail
