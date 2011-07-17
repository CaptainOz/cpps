// Generated by Bisonc++ V2.4.8 on Sat, 16 Jul 2011 18:47:15 -0700

#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "Parserbase.h"
#include "Tokenizer.h"

// $insert namespace-open
namespace cpps
{

#undef Parser
class Parser: public ParserBase
{
private:
    Tokenizer* m_tokenizer;

    void error(char const *msg);    // called on (syntax) errors
    int lex();                      // returns the next token from the
                                    // lexical scanner. 
    void print();                   // use, e.g., d_token, d_loc

// support functions for parse():
    void executeAction(int ruleNr);
    void errorRecovery();
    int lookup(bool recovery);
    void nextToken();

public:
    Parser( void );

    int parse();
    void exec( const std::string& code );
};


/*****************************************************************************/


inline Parser::Parser( void )
    : m_tokenizer( NULL )
{
}


/*****************************************************************************/


inline void Parser::error(char const *msg)
{
    std::cerr << msg << std::endl;
}

// $insert lex

inline void Parser::print()      // use d_token, d_loc
{}

// $insert namespace-close
}

#endif
