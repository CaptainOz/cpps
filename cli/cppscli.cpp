///
/// @file cppscli.cpp
///
/// @brief Main file for the CPPS Command Line Interpreter.
///
/// @author Nate Lillich
///

#include <exception>
#include <iostream>
#include <string>
#include <cpps/cpps.h>

using namespace cpps;
using namespace std;

int main( int argc, const char* argv[] ){
    Parser parser;
    Scope global( true ); // Interpreter mode
    string line;
    string code;
    const string& CPPS_PROMPT = "cpps > ";

    parser.setGlobal( global );

    cout << CPPS_PROMPT;
    while( getline( cin, line ).good() ){
        bool lineDone = false;
        for( unsigned int semicolonPos = line.find( ';' );
             semicolonPos != line.npos;
             semicolonPos = line.find( ';' ) ){
            lineDone = true;
            // We have a semicolon! Execute the code.
            code += line.substr( 0, semicolonPos + 1 );

            // Try to execute this code.
            try {
                parser.exec( code );
            }
            catch( exception* e ){
                cout << "ERROR: " << e->what() << endl;
                delete e;
            }

            // Grab any code off the end of line
            code.clear();
            line = line.substr( semicolonPos + 1 );
        }

        // Line completed?
        if( lineDone ){
            cout << CPPS_PROMPT;
        }

        // No semi-colon yet? Tack the line on and keep pulling.
        else {
            code += '\n' + line;
            cout << "     > ";
        }

    }
    cout << endl;
    return 0;
}

