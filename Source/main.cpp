/**
 * @file       main.cpp
 * @brief      CRoomMap class implementation
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
 * <b> Objective:</b> The purpose of this homework is to explore the use of the Object
 *                    Factory design pattern in combination with XML parsing for configuration.
 *
 */

#include "Common.h"

#include <iostream>

#include "Console.h"
#include "RoomMap.h"
#include "Room.h"

#include "Game.h"


constexpr const TCHAR g_szXmlConfigFile[] = _T("..\\Config\\Puzzle.xml");


//GUI Helper Functions
void splashScreen();

//Engine Functions
void displayGameDone(const CRoom*, int);

int main()
{
    CGame theGame(11);

    if ( theGame.LoadConfigFile( g_szXmlConfigFile ) )
    {
        //Initialize Game State
        CRoom* pRoom = theGame.FindNextRoom( nullptr );

        //Splash Screen
        ClearConsole();
        splashScreen();

        //Until Game Termination Condition Do:
        while ( !theGame.IsGameFinished( pRoom ) )
        {
            //Wipe the GUI clean
            ClearConsole();

            //Perform the game mechanic
            pRoom = theGame.Execute( pRoom );

            if ( pRoom == nullptr )
            {
                tcout << _T( "Runtime fault encountered!!!  Game Terminated." ) << std::endl;
                break;
            }
        }

        //Display End Game State
        displayGameDone( pRoom, theGame.GetHealth() );
    }

    return 0;

}


void splashScreen()
{
    tcout << _T("ROOM PUZZLE") << std::endl;
    tcout << std::endl;
    tcout << _T("Mark L. Short (2017)") << std::endl;
    tcout << _T("CPSC 4377/5377, Advanced Game Programming, Homework 0") << std::endl;
    tcout << _T("UALR, Computer Science Dept.") << std::endl;
    tcout << std::endl;
    tcout << _T("INSTRUCTIONS: Find the finish!") << std::endl;
    tcout << std::endl;
    PauseConsole();
}

void displayGameDone( const CRoom* room, int health)
{
    ClearConsole();

    if (health <= 0)
    {
            tcout << std::endl;
            tcout << _T("Health Reached Zero!") << std::endl;
            tcout << _T("GAME OVER...") << std::endl;
            tcout << std::endl;
    }
    else
    {
        switch( room->GetConditionType() )
        {
        case CND_WIN:
            tcout << std::endl;
            tcout << _T("YOU WIN") << std::endl;
            tcout << std::endl;
            break;
        case CND_LOSE:
            tcout << std::endl;
            tcout << _T("GAME OVER...") << std::endl;
            tcout << std::endl;
            break;
        case CND_QUIT:
            tcout << std::endl;
            tcout << _T("GOOD BYE") << std::endl;
            tcout << std::endl;
            break;
        }
    }

    PauseConsole();
}



