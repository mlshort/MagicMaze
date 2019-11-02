/**
 * @file       Console.h
 * @brief      Console helper function definitions
 * @author     Mark L. Short
 * @date       February 12, 2017
 *
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Magic Maze
 *
 * <b> Objective:</b>
 */

#pragma once

#if !defined(__CONSOLE_H__)
#define __CONSOLE_H__

#ifndef _INC_TCHAR
    #include <tchar.h>
#endif

void ClearConsole         ( void );
void PauseConsole         ( void );
int  GetConsoleBufferWidth( void );
void OutputConsoleText    ( const TCHAR* sz );
void OutputConsoleFillChar( int iChar );

#endif