//
// Created by ake on 02.04.2020.
//

#include "Variables.hpp"

void Variables::Set( std::string_view name, std::string_view value )
{
    // TODO use find
    m_registred[static_cast< std::string >( name )] = value;
}

std::string Variables::Get( std::string_view name )
{
    return m_registred[static_cast< std::string >( name )];
}

void Variables::Remove( std::string_view name ) {
    auto it = m_registred.find( name );
    assert( it != m_registred.cend() );
    m_registred.erase( it );
}
