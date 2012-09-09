
#pragma once

#include <cstdarg>
#include <iostream>
#include <string>

namespace type {
    enum Type {
        INTEGER,
        REAL,
        IDENTIFIER,
        OPERATOR
    };
}

namespace node {
    struct Node;

    struct Integer {
        int value;
    };

    struct Real {
        double value;
    };

    struct Identifier {
        char index;
    };

    struct Operator {
        int     operatorId;
        int     operandCount;
        Node**  operands;
    };

    struct Node {
        type::Type type;
        union {
            Integer     integer;
            Real        real;
            Identifier  identifier;
            Operator    operatr;
        };

        Node( const int operatorId, const int operandCount, ... ):
            type( type::OPERATOR )
        {
            operatr.operatorId      = operatorId;
            operatr.operandCount    = operandCount;
            operatr.operands        = new Node*[ operandCount ];

            va_list args;
            va_start( args, operandCount );
            for( int i = 0; i < operandCount; ++i ){
                operatr.operands[ i ] = va_arg( args, Node* );
            }
            va_end( args );
        }

        Node( const char _identifer ):
            type( type::IDENTIFIER )
        {
            identifier.index = _identifer;
        }

        Node( const int value ):
            type( type::INTEGER )
        {
            integer.value = value;
        }

        Node( const double value ):
            type( type::REAL )
        {
            real.value = value;
        }

        ~Node( void ){
            if( type == type::OPERATOR ){
                for( int i = 0; i < operatr.operandCount; ++i ){
                    delete operatr.operands[ i ];
                }
                delete[] operatr.operands;
            }
        }
    };

}

extern double symbols[ 'z' - 'a' ];
