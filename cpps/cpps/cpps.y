
%{
    #include <iostream>
    #include <cstdlib>
    #include <string>

    #include "cpps/cpps.tab.hpp"
    #include "cpps/Parser.h"

    double ex( node::Node* nodePtr );
    int cpps_lex( void );

    void cpps_error( YYLTYPE* location, cpps::Parser* context, const std::string& message );
    int cpps_lex( YYSTYPE* lval, YYLTYPE* location, void* scanner );

    #define scanner parser->getScanner()

    double symbols[ 'z' - 'a' ];
%}

%code requires {

    #include "cpps/cpps.h"

    namespace cpps {
        class Parser;
    }
}

%pure-parser
%name-prefix="cpps_"
%locations
%defines
%parse-param { cpps::Parser* parser }
%lex-param { void* scanner }

%union {
    int     integerValue;
    double  doubleValue;
    int     symbolIndex;
    node::Node* nodePtr;
};

%token <integerValue>   INTEGER
%token <doubleValue>    REAL
%token <symbolIndex>    VARIABLE
%token WHILE IF PRINT
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nodePtr> stmt expr stmt_list
%type <doubleValue> function

%%

program
    : function          { }
    ;

function
    : function stmt     { $$ = ex( $2 ); delete $2; }
    |                   { $$ = 0; }
    ;

stmt
    : ';'                               { $$ = new node::Node( ';', 2, NULL, NULL ); }
    | expr ';'                          { $$ = $1; }
    | PRINT expr ';'                    { $$ = new node::Node( PRINT, 1, $2 ); }
    | WHILE '(' expr ')' stmt           { $$ = new node::Node( WHILE, 2, $3, $5 ); }
    | IF '(' expr ')' stmt %prec IFX    { $$ = new node::Node( IF, 2, $3, $5 ); }
    | IF '(' expr ')' stmt ELSE stmt    { $$ = new node::Node( IF, 3, $3, $5, $7 ); }
    | '{' stmt_list '}'                 { $$ = $2; }
    ;

stmt_list
    : stmt              { $$ = $1; }
    | stmt_list stmt    { $$ = new node::Node( ';', 2, $1, $2 ); }
    ;

expr
    : INTEGER               { $$ = new node::Node( $1 ); }
    | REAL                  { $$ = new node::Node( $1 ); }
    | VARIABLE              { $$ = new node::Node( (char)$1 ); }
    | VARIABLE '=' expr     { $$ = new node::Node( '=', 2, new node::Node( (char)$1 ), $3 ); }
    | '-' expr %prec UMINUS { $$ = new node::Node( UMINUS, 1, $2 ); }
    | expr '+' expr         { $$ = new node::Node( '+', 2, $1, $3 ); }
    | expr '-' expr         { $$ = new node::Node( '-', 2, $1, $3 ); }
    | expr '*' expr         { $$ = new node::Node( '*', 2, $1, $3 ); }
    | expr '/' expr         { $$ = new node::Node( '/', 2, $1, $3 ); }
    | expr '>' expr         { $$ = new node::Node( '>', 2, $1, $3 ); }
    | expr '<' expr         { $$ = new node::Node( '<', 2, $1, $3 ); }
    | expr GE expr          { $$ = new node::Node( GE, 2, $1, $3 ); }
    | expr LE expr          { $$ = new node::Node( LE, 2, $1, $3 ); }
    | expr EQ expr          { $$ = new node::Node( EQ, 2, $1, $3 ); }
    | expr NE expr          { $$ = new node::Node( NE, 2, $1, $3 ); }
    | '(' expr ')'          { $$ = $2; }
    ;

%%

void cpps_error( YYLTYPE* location, cpps::Parser* parser, const std::string& message ){
    std::cout << message << std::endl;
}
