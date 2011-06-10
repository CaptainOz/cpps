/**
 * @file
 *
 * @brief The tokenizer test runs the Token::tokenizer method over a series of
 *        test scripts.
 *
 * The scripts tokenized are meant to test the various edge cases of tokenizing
 * C++Script code. As new edge cases and problem spots are found, tests for them 
 * should be added to this file.
 *
 * @author Nate Lillich
 */

#include <cpps/CPPS.h>

#include <string>
#include <iostream>

using namespace cpps;
using namespace std;

void tokenTest_one( void );

int main( void )
{
    tokenTest_one();
    return 0;
}

void tokenTest_one( void )
{
    string code = "'hello world'";
    Token::List tokenList = Token::tokenize( code );

    if( tokenList.size() < 1 )
        cout << "Error: Too few tokens found. Expected 1, found "
             << tokenList.size() << endl;

    if( tokenList.size() > 1 )
        cout << "Error: Too many tokens found. Expected 1, found "
             << tokenList.size() << endl;

    Token token = tokenList[0];
    if( token.getType() != Token::StringLiteral )
        cout << "Error: Wrong token type found. Expected StringLiteral, found "
             << token.getTypeString() << endl;

    if( token.getString() != "hello world" )
        cout << "Error: Wrong token string found. Expected 'hello world', found '"
             << token.getString() << "'" << endl;
}

