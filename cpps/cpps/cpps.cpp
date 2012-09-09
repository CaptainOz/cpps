
#include <iostream>

#include "cpps/cpps.h"
#include "cpps/cpps.tab.hpp"
#include "cpps/Parser.h"

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

int main( void ){
    cpps::Parser parser;
    if( !cpps_parse( &parser ) ){
        std::cout << parser.result << std::endl;
    }
    return 0;
}
