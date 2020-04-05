//
// Created by ake on 01.04.2020.
//

#include "TexyInterpreter.hpp"
#include <cassert>
#include <iostream>

void TexyInterpreter::Interpret( std::string_view code, Stack& stack )
{
    Evaluate( Parse( code ), stack );
}

Symbols TexyInterpreter::Parse( std::string_view code )
{
    Symbols symbols;
    auto it = code.cbegin();
    while( it < code.cend() )
    {
        if( *it == '{' )
        {
            ++it;
            auto level = 1;
            auto begin = it;
            while( it < code.cend() )
            {
                //TODO Make it little bit efficient e.g. store brackets on vector
                if( level == 1 && *it == '}' && *( it - 1 ) != '\\' )
                {
                    ++it;
                    break;
                }
                else if( *it == '{' )
                {
                    ++level;
                }
                else if( *it == '}' && *( it - 1 ) != '\\' )
                {
                    --level;
                    assert( level >= 1 );
                }
                ++it;
            }
            assert( level == 1 && it <= code.cend() );
            auto end = it;
            symbols.emplace_back( begin - 1, end - begin + 1 );
        }
        else if( *it == '}' )
        {
            assert( false );
        }
        else if( isspace( *it ) )
        {
            ++it;
            while( it < code.cend() )
            {
                if( !isspace( *it ) )
                {
                    break;
                }
                ++it;
            }
        }
        else
        {
            auto begin = it;
            while( it < code.cend() )
            {
                if( *it == '\\' )
                {
                    it += 2;
                    assert( it <= code.cend() );
                    continue;
                }
                if( isspace( *it ) || *it == '{' || *it == '}' )
                {
                    break;
                }
                ++it;
            }
            auto end = it;
            symbols.emplace_back( begin, end - begin );
        }
    }
    return symbols;
}

void TexyInterpreter::Evaluate( const Symbols& symbols, Stack& stack )
{
    auto it = symbols.cbegin();
    while( it != symbols.cend() )
    {
        if( ( *it )[0] == '{' )
        {
            stack.emplace_back( it->cbegin() + 1, it->cend() - 1 );
//            std::cout << "Added {" << stack.back() << "}\n";
//            DumpStack( stack );
//            Dummy();
        }
        else
        {
//            std::cout << "Executing " << *it << "\n";
//            DumpStack( stack );
            ExecuteCommand( *it, stack );
        }
        ++it;
    }
//    std::cout << "Finished executing" << "\n";
//    DumpStack( stack );
}

void TexyInterpreter::ExecuteCommand( const std::string_view& command, Stack& stack )
{
    m_commands.Get( command )( stack );
}

TexyInterpreter::TexyInterpreter() : m_commands( this ), m_variables() {}

void TexyInterpreter::DumpStack( Stack& stack )
{
    std::cout << "\tStack:\n";
    auto it = stack.rbegin();
    for( ; it != stack.rend(); ++it )
    {
        std::cout << "\t\t{" << *it << "}\n";
    }
}
