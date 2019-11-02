/**
 * @file       Definitions.h
 * @brief      Project enum definitions header file
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

#if !defined(__DEFINITIONS_H__)
#define __DEFINITIONS_H__

//Declaration of condition enumeration
typedef enum _CONDITION_TYPE
{
    CND_INVALID = -1,
    CND_WIN = 0,
    CND_LOSE,
    CND_NONE,
    CND_QUIT
} CONDITION_TYPE;

typedef enum _ROOM_TYPE
{
    RM_INVALID = -1,
    RM_NORMAL = 0,
    RM_MAGIC
} ROOM_TYPE;

constexpr bool IsValid( CONDITION_TYPE cnd ) noexcept
{ return cnd != CND_INVALID; };

constexpr bool IsValid ( ROOM_TYPE type ) noexcept
{ return type != RM_INVALID; };

#endif