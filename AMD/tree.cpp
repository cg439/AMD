#include <AMD/log.hpp>
#include <AMD/tree.hpp>

namespace AMD { namespace detail {

Tree::Tree (const std::string& info, 
            const boost::shared_ptr<Tree>& left, 
            const boost::shared_ptr<Tree>& right)
{
    LOG_INFO << "Constructing Tree from " << info;
    this->d_info = info;
    this->d_left = left;
    this->d_right = right;
}
                   
Tree::~Tree()
{
}

void Tree::swap(Tree& other)
{
    LOG_INFO << "Swapping with another node";
    if (&other == NULL) return;
    std::swap(other.d_info, this->d_info);
    std::swap(other.d_left, this->d_left);
    std::swap(other.d_right, this->d_right);
}

std::string Tree::info() const
{
    return this->d_info;
}

boost::shared_ptr<Tree> Tree::left () const 
{
    return this->d_left;
}

boost::shared_ptr<Tree> Tree::right () const 
{
    return this->d_right;
}

void Tree::setInfo(const std::string& info)
{
    this->d_info = info;
}

void Tree::setLeftChild(const boost::shared_ptr<Tree>& left)
{
    this->d_left = left;
}

void Tree::setRightChild(const boost::shared_ptr<Tree>& right)
{
    this->d_right = right;
}

bool Tree::operator==(const Tree& other) const
{
    LOG_TRACE << "Checking Tree Equality";
    if (other.d_info != this->d_info) return false;

    if ((other.d_right == this->d_right) && (other.d_left == this->d_left))
        return true;

    if ((!(other.d_right) && this->d_right) 
         || (other.d_right && !(this->d_right))
         || (!(other.d_left) && this->d_left)
         || (other.d_left && !(this->d_left))) return false;

    if (!other.d_right && !this->d_right) 
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
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Tree& tree)
{
    LOG_TRACE << "Printing Tree";
    tree.print(os);
    return os;
}

} } // namespace AMD::detail
