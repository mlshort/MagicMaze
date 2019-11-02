/**
 * @file       Common.h
 * @brief      Common type definitions
 * @author     Mark L. Short
 * @date       February 12, 2017
 *
 *
 * <b>Course:</b>       CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Magic Maze
 *
 * <b> Objective:</b>
 */

#pragma once

#if !defined(__COMMON_H__)
#define __COMMON_H__

#ifndef _INC_TCHAR
    #include <tchar.h>
#endif
#ifndef _IOSTREAM_
    #include <iostream>
#endif
#ifndef _STRING_
    #include <string>
#endif

#if !defined(_TSTRING_)
#define _TSTRING_
    #if defined(UNICODE) || defined(_UNICODE)
        #define tstring std::wstring
        #define tcout   std::wcout
        #define tcin    std::wcin
    #else
        #define tstring std::string
        #define tcout   std::cout
        #define tcin    std::cin
    #endif
#endif

#endif