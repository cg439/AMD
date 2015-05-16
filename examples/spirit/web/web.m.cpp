#include <iostream>
#include <string>
#include <exception>
#include <cctype>

#include <boost/lexical_cast.hpp>

#include <AMD/expression.hpp>
#include <AMD/log.hpp>
#include <AMD/derivative.hpp>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>

using namespace std;
using namespace cgicc;

int main()
{
    Cgicc formData;
    string input, dif;
    form_iterator fi = formData.getElement("input");  
    if( !fi->isEmpty() && fi != (*formData).end()) {  
        input = **fi; 
    }else{
        input = "No input entered";
    }
   /* fi = formData.getElement("dif");
    if( !fi->isEmpty() && fi != (*formData).end()) {  
        dif = **fi; 
    }else{
        dif = "No dif term entered";
    }*/
//    input = getenv("QUERY_STRING");
    //input = "tr(X+X)";
    dif = "X";

    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>AMD - Automatic Matrix Differentiation</title>\n";

    cout <<   "<link type=\"text/css\" rel=\"stylesheet\" href=\"http://pkambadu.github.io/AMD/css/style.css\"<link type=\"text/css\" rel=\"stylesheet\" href=\"http://pkambadu.github.io/AMD/css/grid.css\"><link type=\"text/css\" rel=\"stylesheet\" href=\"http://pkambadu.github.io/AMD/fonts/stylesheet.css\">";
    cout << "</head>\n";

    cout << "<p> Input was " << input << "\n Dif was " << dif << "</p>"; 



    AMD::setLogLevel(1);

    AMD::Expression myExpr, derivative;
    
    try {
        myExpr = AMD::generateExpression(input);
       // std::cout << "Parsing succeeded: " << *myExpr << "\n";
    } catch (const std::exception& e) {
       // std::cout << e.what() << std::endl;
    }
    try {
        //default target matrix is X
	derivative = AMD::generateDerivativeExpression(myExpr, "X");
	//std::cout << "Differentiation succeeded: " << *derivative << "\n";
    } catch (const std::exception& e) {
       // std::cout << e.what() << std::endl;
    } 

    cout << "<p>";

    cout << "Parsed expression is :" << *myExpr << "\n";
    cout << "Differentiated expression is :" << *derivative << "\n";

    cout << "</p>";
    cout << "</body>\n";
    cout << "</html>\n";
}
