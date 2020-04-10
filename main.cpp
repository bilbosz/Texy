#include "Interpreter.hpp"
#include <iostream>

int main( int argc, char* argv[] )
{
    if( argc <= 1 )
    {
        std::cout << "Text Machine\nUsage: text-machine cmd [arg] ...";
        return EXIT_SUCCESS;
    }
    Interpreter interpreter;
    Stack stack{};
    for( int i = 2; i < argc; ++i )
    {
        stack.push_back( argv[i] );
    }
    interpreter.Interpret( argv[1], stack );
    return EXIT_SUCCESS;
}
