
#include <iostream>
#include "cpps.h"
#include "cpps.tab.hpp"

double ex( node::Node* nodePtr ){
    if( nodePtr == NULL ){
        return 0;
    }

    switch( nodePtr->type ){
        case type::INTEGER:     return nodePtr->integer.value;
        case type::REAL:        return nodePtr->real.value;
        case type::IDENTIFIER:  return symbols[ nodePtr->identifier.index ];
        case type::OPERATOR:
            switch( nodePtr->operatr.operatorId ){
                case WHILE:
                    while( ex( nodePtr->operatr.operands[0] ) ){
                        ex( nodePtr->operatr.operands[1] );
                    }
                    return 0;

                case IF:
                    if( ex( nodePtr->operatr.operands[0] ) ){
                        ex( nodePtr->operatr.operands[1] );
                    }
                    else if( nodePtr->operatr.operandCount > 2 ){
                        ex( nodePtr->operatr.operands[2] );
                    }
                    return 0;

                case PRINT:
                    std::cout << ex( nodePtr->operatr.operands[0] ) << std::endl;
                    return 0;

                case ';':
                    ex( nodePtr->operatr.operands[0] );
                    return ex( nodePtr->operatr.operands[1] );

                case '=':
                    return symbols[ nodePtr->operatr.operands[0]->identifier.index ] = ex( nodePtr->operatr.operands[1] );

                case UMINUS:
                    return -ex( nodePtr->operatr.operands[0] );

                case '+':
                    return ex( nodePtr->operatr.operands[0] ) + ex( nodePtr->operatr.operands[1] );

                case '-':
                    return ex( nodePtr->operatr.operands[0] ) - ex( nodePtr->operatr.operands[1] );

                case '*':
                    return ex( nodePtr->operatr.operands[0] ) * ex( nodePtr->operatr.operands[1] );

                case '/':
                    return ex( nodePtr->operatr.operands[0] ) / ex( nodePtr->operatr.operands[1] );

                case '<':
                    return ex( nodePtr->operatr.operands[0] ) < ex( nodePtr->operatr.operands[1] );

                case '>':
                    return ex( nodePtr->operatr.operands[0] ) > ex( nodePtr->operatr.operands[1] );

                case GE:
                    return ex( nodePtr->operatr.operands[0] ) >= ex( nodePtr->operatr.operands[1] );

                case LE:
                    return ex( nodePtr->operatr.operands[0] ) <= ex( nodePtr->operatr.operands[1] );

                case EQ:
                    return ex( nodePtr->operatr.operands[0] ) == ex( nodePtr->operatr.operands[1] );

                case NE:
                    return ex( nodePtr->operatr.operands[0] ) != ex( nodePtr->operatr.operands[1] );
            }
    }

    return 0;
}

int LexerContext::lookupKeyword( const std::string& str ){
    if( str == "while" ){
        return WHILE;
    }
    else if( str == "if" ){
        return IF;
    }
    else if( str == "else" ){
        return ELSE;
    }
    else if( str == "print" ){
        return PRINT;
    }
    else {
        return 0;
    }
}

int main( void ){
    LexerContext context;
    if( !cpps_parse( &context ) ){
        std::cout << context.result << std::endl;
    }
    return 0;
}
