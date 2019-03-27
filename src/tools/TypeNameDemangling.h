/*
* TypeNameDemangling.h
*
*  Created on: 21.12.2011
*      Author: jvogelges
*/

#ifndef TYPENAMEDEMANGLING_H_
#define TYPENAMEDEMANGLING_H_

#include <string>

#ifdef __GNUC__
#include <cxxabi.h>
#include <typeinfo>
#endif
#include <string>
#include <stdlib.h>
#if __cplusplus > 199711L
//typeindex needs cxx11
#include <typeindex>
#endif

/**
* small helper to get nice (demangled) typenames from gcc
*/

template<class Type>
std::string demangledTypeName(const Type* p)
{
#ifdef __GNUC__
    char* p_nice_name = abi::__cxa_demangle(typeid(*p).name(),NULL,NULL,NULL);
#else
    char* p_nice_name = (char*)typeid(*p).name();
#endif
    std::string result(p_nice_name);
    free(p_nice_name);
    return result;
}

template<class Type>
std::string demangledTypeName(const Type& p)
{
#ifdef __GNUC__
    char* p_nice_name = abi::__cxa_demangle(typeid(p).name(),NULL,NULL,NULL);
#else
    char* p_nice_name = (char*)typeid(p).name();
#endif
    std::string result(p_nice_name);
    free(p_nice_name);
    return result;
}

#if __cplusplus > 199711L
inline static std::string demangledTypeName(const std::type_index& type)
{
    char* p_nice_name = abi::__cxa_demangle(type.name(),NULL,NULL,NULL);
    std::string result(p_nice_name);
    free(p_nice_name);
    return result;
}

#endif

#endif /* TYPENAMEDEMANGLING_H_ */
