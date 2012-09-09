
%{
    #include <iostream>
    #include <cstdlib>
    #include <string>

    #include "cpps/Parser.h"

    void cpps_error( YYLTYPE* location, cpps::Parser* context, const std::string& message );
%}

%top {

    namespace cpps {
        class Parser;
    }
    #define YY_EXTRA_TYPE   cpps::Parser*
}

%option reentrant
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno
%option nounput

%option header-file = "cpps/cpps.lex.h"
%option prefix      = "cpps_"

%{
    #define YY_USER_ACTION  yylloc->first_line = yylineno;
    #define YY_INPUT( buf, result, maxSize ){   \
        char c;                                 \
        yyextra->getStream() >> c;              \
        if( yyextra->getStream().eof() ){               \
            result = 0;                         \
        }                                       \
        else {                                  \
            buf[ 0 ] = c;                       \
            result = 1;                         \
        }                                       \
    }
%}

DIGIT       [0-9]
OCT_DIGIT   [0-8]
HEX_DIGIT   [0-9a-fA-F]
BIN_DIGIT   [01]
INTEGER     [1-9][0-9]*
LETTER      [a-zA-Z_]
IDENTIFIER  [a-zA-Z][a-zA-Z_0-9]*

%%

(0|{INTEGER})       {

                        yylval->integerValue = std::atoi( yytext );
                        return INTEGER;
                    }

({INTEGER}\.{DIGIT}*|\.{DIGIT}+)    {
                        yylval->doubleValue = std::atof( yytext );
                        return REAL;
                    }

[\-()<>=+*/;{}\.]   {
                        return *yytext;
                    }

">="                    return GE;
"<="                    return LE;
"=="                    return EQ;
"!="                    return NE;

{IDENTIFIER}        {
                        int keyword = yyextra->lookupKeyword( yytext );
                        if( keyword ){
                            return keyword;
                        }
                        yylval->symbolIndex = *yytext - 'a';
                        return VARIABLE;
                    }

[ \t\n]+            ; // Ignore whitespace.

.                   cpps_error( NULL, NULL, std::string( "Unknown token: " ) + std::string( yytext ) );

%%
