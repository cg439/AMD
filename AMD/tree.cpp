#include <AMD/tree.hpp>

namespace AMD { namespace detail {

Tree::Tree (const std::string& info, 
            const boost::shared_ptr<Tree>& left, 
            const boost::shared_ptr<Tree>& right)
{
    this->d_info = info;
    this->d_left = left;
    this->d_right = right;
}

Tree::Tree (const std::string& info)
{
    boost::shared_ptr<Tree> null;
    this->d_info = info;
    this->d_left = null;
    this->d_right = null;
}
                   
Tree::~Tree()
{

}

void Tree::swap(Tree& other)
{
    ///check for null nodes otherwise swap and recurse
   /* if (!(*this) || !(*other)) {
        return;
    }*/
    std::swap(other.d_info, this->d_info);
    this->d_left.swap(other.d_left);
    this->d_right.swap(other.d_right);
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
    ///NULL == NULL
   /* if (!(*other) && !(*this)) {
        return true;
    }    
    ///NULL == something or something == NULL
    else if (!this || !other) {
        return false;
    }*/
    ///check if 
    ///A:strings match match,
    ///and
    /// B: if l1 != l2 && r1 != r2
    ///and if l1 != r2 && l2 != r1
    ///essentially ensure that the values are same and structure is same
    ///if both A and B are true then the trees must be equal
    return ((other.d_info) == (this->d_info) &&
            (*(other.d_left) == *(this->d_left) &&
            *(other.d_right) == *(this->d_right)) ||
            (*(other.d_left) == *(this->d_right) &&
            *(other.d_right) == *(this->d_left)));
}

bool Tree::operator!=(const Tree& other) const
{
     return !(other == *this);
}

} } // namespace AMD::detail
