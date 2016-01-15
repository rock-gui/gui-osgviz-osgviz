/*
 * TypeNameDemangling.h
 *
 *  Created on: 21.12.2011
 *      Author: jvogelges
 */

#ifndef TYPENAMEDEMANGLING_H_
#define TYPENAMEDEMANGLING_H_


#include <cxxabi.h>
#include <string>
#include <stdlib.h>
#include <typeindex> 

/**
 * small helper to get nice (demangled) typenames from gcc
 */

template<class Type>
std::string demangledTypeName(const Type* p)
{
   char* p_nice_name = abi::__cxa_demangle(typeid(*p).name(),NULL,NULL,NULL);
   std::string result(p_nice_name);
   free(p_nice_name);
   return result;
}

template<class Type>
std::string demangledTypeName(const Type& p)
{
   char* p_nice_name = abi::__cxa_demangle(typeid(p).name(),NULL,NULL,NULL);
   std::string result(p_nice_name);
   free(p_nice_name);
   return result;
}

std::string demangledTypeName(const std::type_index& type)
{
   char* p_nice_name = abi::__cxa_demangle(type.name(),NULL,NULL,NULL);
   std::string result(p_nice_name);
   free(p_nice_name);
   return result;  
}


#endif /* TYPENAMEDEMANGLING_H_ */
