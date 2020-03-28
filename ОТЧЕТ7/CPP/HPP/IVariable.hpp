#ifndef IVariable_HPP
#define IVariable_HPP

struct IVariable
{
 virtual float Get() = 0 ;
 virtual float Calculate(float code) = 0 ;
} ;
 #endif