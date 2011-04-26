/**
 * @file cppscli.cpp
 *
 * @brief Main file for the CPPS Command Line Interpreter.
 *
 * @author Nate Lillich
 */

#include <iostream>
#include <cpps/cpps.h>

using namespace cpps;
using namespace std;

int main( int argc, const char* argv[] )
{
    Scope scope;
    Interpreter interp;
    
    cout << interp.exec( "Hello World!", scope ).toString() << endl;

    return 0;
}

