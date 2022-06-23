#pragma once
#ifdef __AVR__
#include <alloca.h>
#define cli() __asm volatile( "cli" ::: "memory" )
#define sei() __asm volatile( "sei" ::: "memory" )

#endif