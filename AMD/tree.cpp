#include <AMD/tree.hpp>
#include <boost/log/trivial.hpp>

namespace AMD { namespace detail {

Tree::Tree (const std::string& info, 
            const boost::shared_ptr<Tree>& left, 
            const boost::shared_ptr<Tree>& right)
{
    try{
        ///if binop then no null lhs or rhs allowed
        if (info == "+" || info == "*"
        || info == "o") {
            if ((left) && (right)){
                this->d_info = info;
                this->d_left = left;
                this->d_right = right;
            }
            else {
                throw;
            }
        }
        ///if unary op then check for lhs non-null rhs null
        else if (info == "'" || info == "_"
        || info == "tr" || info == "lgdt") {
            if ((left) && !(right)){
                this->d_info = info;
                this->d_left = left;
                this->d_right = right;
            }
            else {
                throw;
            }
        }
        ///for special case of neg/subtraction op
        ///check if lhs is non-null
        else if (info == "-"){
            if ((left)) {
                this->d_info = info;
                this->d_left = left;
                this->d_right = right;
            }
            else{
                throw;
            }
        }
        ///if any double string or name of a matrix then just check null child
        else if (!(left) && !(right)){
            this->d_info = info;
            this->d_left = left;
            this->d_right = right;
        }
        
        else {
            throw;
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
            throw;
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
    // Root information
    if (other.d_info != this->d_info) return false;

    // Children pointers are equal
    if ((other.d_right == this->d_right) && (other.d_left == this->d_left))
        return true;

    // One tree has a child where the other has a null pointer
    if ((!(other.d_right) && this->d_right) 
         || (other.d_right && !(this->d_right))
         || (!(other.d_left) && this->d_left)
         || (other.d_left && !(this->d_left))) return false;

    if (!other.d_right && !other.d_right)
        return *(other.d_left) == *(this->d_left); 
    else if (!other.d_left && !this->d_left) 
        return *(other.d_right) == *(this->d_right);
    else
    {
        return (*(other.d_right) == *(this->d_right))
           && (*(other.d_left) == *(this->d_left));
    }
}

bool Tree::operator!=(const Tree& other) const
{
     return !(other == *this);
}

} } // namespace AMD::detail
