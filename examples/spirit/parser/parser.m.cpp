#include <iostream>
#include <string>
#include <exception>

#include <AMD/expression.hpp>

int main()
{
    std::cout << "/////////////////////////////////////////////////////////\n";
    std::cout << "Expression parser...\n";
    std::cout << "/////////////////////////////////////////////////////////\n";
    std::cout << "Type an expression...or [q or Q] to quit\n\n";

    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        try {
            AMD::Expression myExpr = AMD::generateExpression(str);
            std::cout << "Parsing succeeded: " << myExpr << "\n";
            ((AMD::detail::Tree)*myExpr).print(std::cout);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}
