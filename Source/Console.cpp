/**
 * @file       Console.cpp
 * @brief      Console helper function implementation
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

#include <Windows.h>
#include <WinCon.h>
#include <conio.h>
#include "Common.h"

#include "Console.h"

int GetConsoleBufferWidth( void )
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int iBufferWidth = 0;

    if ( GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi ) )
    {
        iBufferWidth = csbi.dwSize.X;
    }

    return iBufferWidth;
}


void PauseConsole( void )
{
    tcout << _T( "Press any key to continue..." ) << std::endl;
    _getch();
}

void ClearConsole( void )
{
    COORD  topLeft = { 0, 0 };
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      dwWritten;

    GetConsoleScreenBufferInfo( hConsole, &csbi );
    FillConsoleOutputCharacter( hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, topLeft, &dwWritten );

    FillConsoleOutputAttribute( hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
                                csbi.dwSize.X * csbi.dwSize.Y, topLeft, &dwWritten );

    SetConsoleCursorPosition( hConsole, topLeft );
}

void OutputConsoleFillChar( int iChar )
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      dwWritten;

    if ( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
    {
        int iBufferWidth = csbi.dwSize.X;

        COORD coord = csbi.dwCursorPosition;
        coord.X = 0;

        FillConsoleOutputCharacter( hConsole, iChar, iBufferWidth, coord, &dwWritten );

        coord = csbi.dwCursorPosition;
        coord.X = 0;
        coord.Y++;

        SetConsoleCursorPosition( hConsole, coord );
    }

    return;

}

void OutputConsoleText( const TCHAR* sz )
{
    tstring strTemp( sz );

    int iBufferWidth = GetConsoleBufferWidth();

    for ( unsigned int i = 1; i <= strTemp.length(); i++ )
    {
        TCHAR c = strTemp[i - 1];

        int iSpaceCnt = 0;

        if ( ( i % iBufferWidth ) == 0 )
        {
            if ( c != ' ' )
            {
                for ( int j = ( i - 1 ); j > -1; j-- )
                {
                    if ( strTemp[j] == ' ' )
                    {
                        strTemp.insert( j, iSpaceCnt, ' ' );
                        break;
                    }
                    else
                    {
                        iSpaceCnt++;
                    }
                }
            }
        }
    }

    // Output string to console
    tcout << strTemp << std::endl;
}