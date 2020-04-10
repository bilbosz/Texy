//
// Created by ake on 01.04.2020.
//

#include "Commands.hpp"
#include "Interpreter.hpp"
#include <boost/lexical_cast.hpp>
#include <fstream>

Commands::Commands( Interpreter* interpreter ) : m_interpreter( interpreter )
{
    m_registred["set"] = [this]( Stack& stack ) { Set( stack ); };
    m_registred["get"] = [this]( Stack& stack ) { Get( stack ); };
    m_registred["do"] = [this]( Stack& stack ) { Do( stack ); };
    m_registred["ref"] = [this]( Stack& stack ) { Ref( stack ); };
    m_registred["lt"] = [this]( Stack& stack ) { Lt( stack ); };
    m_registred["if"] = [this]( Stack& stack ) { If( stack ); };
    m_registred["pick"] = [this]( Stack& stack ) { Pick( stack ); };
    m_registred["add"] = [this]( Stack& stack ) { Add( stack ); };
    m_registred["print"] = [this]( Stack& stack ) { Print( stack ); };
    m_registred["do_file"] = [this]( Stack& stack ) { DoFile( stack ); };
}

CommandExecutable Commands::Get( std::string_view name )
{
    auto it = m_registred.find( name );
    return it != m_registred.cend() ? it->second : nullptr;
}

void Commands::Set( Stack& stack )
{
    std::string name = stack.back();
    stack.pop_back();
    std::string value = stack.back();
    stack.pop_back();
    m_interpreter->GetVariables().Set( name, value );
}

void Commands::Get( Stack& stack )
{
    std::string name = stack.back();
    stack.pop_back();
    stack.emplace_back( m_interpreter->GetVariables().Get( name ) );
}

void Commands::Do( Stack& stack )
{
    std::string code = stack.back();
    stack.pop_back();
    m_interpreter->Interpret( code, stack );
}

void Commands::Ref( Stack& stack )
{
    auto n = boost::lexical_cast< int >( stack.back() );
    stack.pop_back();
    assert( n >= 1 && n <= stack.size() );
    stack.emplace_back( *( stack.end() - n ) );
}

void Commands::Lt( Stack& stack )
{
    auto a = boost::lexical_cast< int >( stack.back() );
    stack.pop_back();
    auto b = boost::lexical_cast< int >( stack.back() );
    stack.pop_back();
    stack.emplace_back( a < b ? "1" : "" );
}

void Commands::If( Stack& stack )
{
    auto test = stack.back();
    stack.pop_back();
    auto trueValue = stack.back();
    stack.pop_back();
    auto falseValue = stack.back();
    stack.pop_back();
    stack.emplace_back( test.empty() ? falseValue : trueValue );
}

void Commands::Pick( Stack& stack )
{
    auto n = boost::lexical_cast< int >( stack.back() );
    assert( n >= 1 && n <= stack.size() );
    auto it = stack.end() - n - 1;
    std::swap( *it, stack.back() );
    stack.erase( it );
}

void Commands::Add( Stack& stack )
{
    auto a = boost::lexical_cast< int >( stack.back() );
    stack.pop_back();
    auto b = boost::lexical_cast< int >( stack.back() );
    stack.pop_back();
    stack.emplace_back( std::to_string( a + b ) );
}

void Commands::Print( Stack& stack )
{
    auto message = stack.back();
    stack.pop_back();
    std::cout << message;
}

void Commands::DoFile( Stack& stack )
{
    auto filename = stack.back();
    stack.pop_back();
    std::ifstream file( filename );
    std::ostringstream stringstream;
    stringstream << file.rdbuf();
    std::string str = stringstream.str();
    m_interpreter->Interpret( str, stack );
}
