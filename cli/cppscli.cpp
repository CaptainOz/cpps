/**
 * @file cppscli.cpp
 *
 * @brief Main file for the CPPS Command Line Interpreter.
 *
 * @author Nate Lillich
 */

#include <string>
#include <iostream>
#include <cpps/cpps.h>

using namespace cpps;
using namespace std;

int main( int argc, const char* argv[] )
{
    Parser parser;
    string line;
    string code;

    cout << "cpps > ";
    while( getline( cin, line ).good() )
    {
        int semicolonPos = line.find( ';' );

        // No semi-colon yet? Tack the line on and keep pulling.
        if( semicolonPos == string::npos )
        {
            code += '\n' + line;
            cout << "     > ";
        }
        else
        {
            // We have a semicolon! Execute the code.
            code += line.substr( 0, semicolonPos + 1 );
            parser.exec( code );

            // Clear the code and reset the line.
            code.clear();
            line = line.substr( semicolonPos );
            cout << "cpps > ";
        }
    }
    cout << endl;
    return 0;
}

