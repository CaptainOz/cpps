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

#include <cpps/cpps.h>

#include <string>
#include <iostream>

using namespace cpps;
using namespace std;

void tokenTest_one( void );
void tokenTest_two( void );
void tokenTest_three( void );

int main( void )
{
    tokenTest_one();
    tokenTest_two();
    tokenTest_three();
    return 0;
}

void tokenTest_one( void )
{
    string code = "'hello world'";
    Tokenizer tokenizer( code );
    Token::List tokenList;

    cout << "Basic parse test (" << code << "): ";

    do
    {
        tokenList.push_back( tokenizer.getNextToken() );
    } while( tokenList[ tokenList.size() - 1 ].getType() != Token::EndOfFile );
    tokenList.pop_back();

    if( tokenList.size() < 1 )
        cout << "Error: Too few tokens found. Expected 1, found "
             << tokenList.size() << endl;

    else if( tokenList.size() > 1 )
        cout << "Error: Too many tokens found. Expected 1, found "
             << tokenList.size() << endl;
    else
    {
        Token& token = tokenList.at(0);
        if( token.getType() != Token::StringLiteral )
            cout << "Error: Wrong token type found. Expected StringLiteral, found "
                 << token.getTypeString() << endl;

        else if( token.getString() != "hello world" )
            cout << "Error: Wrong token string found. Expected 'hello world', found '"
                 << token.getString() << "'" << endl;

        else
            cout << "Pass!" << endl;
    }
}

void tokenTest_two( void )
{
    string code = "::;:,||&&?{}()[]==!=>=<==+=-=.=*=/=%=&=^=|=<<=>>=++--!~"
                  ">><<->><+-*/%.&^|";
    Tokenizer tokenizer( code );

    cout << "Token extraction order test: ";

    bool error = false;
    int type;
    for( type = (int)Token::Scope; type < (int)Token::Break; ++type )
    {
        const Token& token = tokenizer.getNextToken();
        const Token::Type& tokenType = token.getType();
        if( tokenType != Token::EndOfFile && tokenType != (Token::Type)type )
        {
            cout << "Error: Expected " << Token::getTypeString( (Token::Type)type )
                 << ", found " << token.getTypeString() << endl;
            error = true;
        }
    }
    if( !error && type == (int)Token::BitwiseOr + 1 )
        cout << "Pass!" << endl;
}

void tokenTest_three( void )
{
    string code =
        "break;        case;        catch;    class;      const;      continue;\
         default;      delete;      do;       else;       enum;       false;   \
         for;          foreach;     friend;   function;   if;         include; \
         instanceof;   namespace;   new;      null;       operator;   private; \
         protected;    public;      return;   sizeof;     static;     struct;  \
         switch;       this;        throw;    true;       try;        typedef; \
         typename;     union;       using;    while;      var;";
    Tokenizer tokenizer( code );

    cout << "Operator extraction test: ";

    bool error = false;
    int type;
    for( type = (int)Token::Break; type != Token::EndOfFile; )
    {
        const Token& token = tokenizer.getNextToken();
        const Token::Type& tokenType = token.getType();
        if( tokenType == Token::Semicolon )
            ++type;
        else if( tokenType != Token::EndOfFile && tokenType != (Token::Type)type )
        {
            cout << "Error: Expected " << Token::getTypeString( (Token::Type)type )
                 << ", found " << token.getTypeString() << endl;
            error = true;
        }
    }
    if( !error && type == (int)Token::Var + 1 )
        cout << "Pass!" << endl;
}


