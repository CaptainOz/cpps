
%{
    #include <cstdlib>
    #include "cpps.h"
    #include "cpps.tab.hpp"

    void cpps_error( YYLTYPE* location, LexerContext* context, const char* message );
%}

%option reentrant
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno

%option prefix="cpps_"

%{
    #define YY_EXTRA_TYPE   LexerContext*
    #define YY_USER_ACTION  yylloc->first_line = yylineno;
    #define YY_INPUT( buf, result, maxSize ){   \
        char c;                                 \
        (*yyextra->is) >> c;                    \
        if( yyextra->is->eof() ){               \
            result = NULL;                      \
        }                                       \
        else {                                  \
            buf[ 0 ] = c;                       \
            result = 1;                         \
        }                                       \
    }
%}

%%

[a-z]               {
                        yylval->symbolIndex = *yytext - 'a';
                        return VARIABLE;
                    }

[0-9][0-9]*         {
                        yylval->integerValue = std::atoi( yytext );
                        return INTEGER;
                    }

[\-()<>=+*/;{}\.]   {
                        return *yytext;
                    }

">="                    return GE;
"<="                    return LE;
"=="                    return EQ;
"!="                    return NE;
"while"                 return WHILE;
"if"                    return IF;
"else"                  return ELSE;
"print"                 return PRINT;

[ \t\n]+                ; // Ignore.

.                       cpps_error( NULL, NULL, "Unknown character." );

%%

void LexerContext::initScanner( void ){
    cpps_lex_init( &scanner );
    cpps_set_extra( this, scanner );
}

void LexerContext::destroyScanner( void ){
    cpps_lex_destroy( scanner );
}

