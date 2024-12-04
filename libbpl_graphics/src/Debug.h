//
// Created by Bradley Remedios on 11/24/24.
//
#ifndef BPL_GRAPHICS_DEBUG_H
#define BPL_GRAPHICS_DEBUG_H

#include <iostream>

//#define __ENABLE_BPL_GRAPHICS_DEBUG    1

#define ERROR_MSG(msg)  { std::cerr << __PRETTY_FUNCTION__ << ":" << msg << std::endl; }

#if defined(__ENABLE_BPL_GRAPHICS_DEBUG)
    #define DEBUG_MSG(msg)  { std::cout << __PRETTY_FUNCTION__ << ":" << msg << std::endl; }
#else
    #define DEBUG_MSG(cmd)
#endif // __ENABLE_BPL_GRAPHICS_DEBUG

#endif //BPL_GRAPHICS_DEBUG_H