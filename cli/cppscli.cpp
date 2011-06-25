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
        bool lineDone = false;
        for( int semicolonPos = line.find( ';' );
             semicolonPos != string::npos;
             semicolonPos = line.find( ';' ) )
        {
            lineDone = true;
            // We have a semicolon! Execute the code.
            code += line.substr( 0, semicolonPos + 1 );
            parser.exec( code );

            // Grab any code off the end of line
            code.clear();
            line = line.substr( semicolonPos + 1 );
        }

        // Line completed?
        if( lineDone )
            cout << "cpps > ";

        // No semi-colon yet? Tack the line on and keep pulling.
        else
        {
            code += '\n' + line;
            cout << "     > ";
        }

    }
    cout << endl;
    return 0;
}

