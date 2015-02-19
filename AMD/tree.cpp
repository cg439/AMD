#include <AMD/tree.hpp>
#include <stdio.h>

namespace AMD { namespace detail {

Tree::Tree (const std::string& info, 
            const boost::shared_ptr<Tree>& left, 
            const boost::shared_ptr<Tree>& right)
{
    this->d_info = info;
    this->d_left = left;
    this->d_right = right;
}
                   
Tree::~Tree()
{
}

bool Tree::isLeafNode()
{
    return !(this->d_left) && !(this->d_right);
}

std::string Tree::printHelper(Tree& tree, std::string indentation) 
{
    if (&tree == NULL) return "";
    std::string tree_string = indentation + tree.d_info + "\n";
    tree_string += printHelper(*tree.d_left.get(),  indentation + "--");
    tree_string += printHelper(*tree.d_right.get(), indentation + "--");
    return tree_string;
}

void Tree::swap(Tree& other)
{
    if (&other == NULL) return;
    std::swap(other.d_info, this->d_info);
    std::swap(other.d_left, this->d_left);
    std::swap(other.d_right, this->d_right);
}

std::string Tree::info() const
{
    return this->d_info;
}

void Tree::setInfo(const std::string& info)
{
    this->d_info = info;
}

///FIXME: Need to see if it's necessary to memoize the equality checks
/// for the left and right child checks in case it ends up recursively
/// checking for equality, possibly use adjacency matrix with shared pointers?
bool Tree::operator==(const Tree& other) const
{
    // Root information
    if (other.d_info != this->d_info) return false;

    // Children pointers are equal
    if ((other.d_right == this->d_right) && (other.d_left == this->d_left)
        || (other.d_right == this->d_left) && (other.d_left == this->d_right))
        return true;

    // One tree has a child where the other has a null pointer
    if ((!(other.d_right) && this->d_right) 
         || (other.d_right && !(this->d_right))
         || (!(other.d_left) && this->d_left)
         || (other.d_left && !(this->d_left))) return false;

    //check equality where needed avoiding null shared pointer deref
    if (!other.d_right && !this.d_right)
        return *(other.d_left) == *(this->d_left); 
    else if (!other.d_left && !this->d_left) 
        return *(other.d_right) == *(this->d_right);
    else
    {
        return ((*(other.d_right) == *(this.d_right))
           && (*(other.d_left) == *(this.d_left)) ||
           (*(other.d_right) == *(this.d_left)) &&
           (*(other.d_left) == *(this.d_right)));
    }
}

bool Tree::operator!=(const Tree& other) const
{
    return !(*this == other);
}

} } // namespace AMD::detail
