#include <iostream>
#include <string>
#include <exception>

#include <boost/lexical_cast.hpp>

#include <AMD/expression.hpp>
#include <AMD/log.hpp>

int main()
{
    std::cout << "/////////////////////////////////////////////////////////\n";
    std::cout << "Expression parser...\n";
    std::cout << "/////////////////////////////////////////////////////////\n";

    std::string logLevel;
    std::cout << "Enter a logging level [1,2,3,4,5]: ";
    std::getline (std::cin, logLevel);
    AMD::setLogLevel(boost::lexical_cast<int>(logLevel));

    std::cout << "Type an expression...or [q or Q] to quit\n\n";
    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        LOG_DEBUG << "Entered string is : " << str;

        try {
            AMD::Expression myExpr = AMD::generateExpression(str);
            std::cout << "Parsing succeeded: " << *myExpr << "\n";
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Bye... :-) \n\n";
    return 0;
}
