# Magic Maze: Quest 0

Directory Structure
====================
```
  Magic Maze (Solution File)  
     |  
     +-- Game (binaries)  
     |  
     +-- Source (Source code) (Project file)  
     |  
     +-- Config (XML Configuration Files)  
     |  
     +-- Documentation (Project Specifications)  
     |  
     +-- Obj (compile time intermediaries objects)  
```


Magic Maze Project Overview
====================
 
The purpose of this assignment is to give you experience working with tools that 
facilitate flexible game architecture. In this assignment you will:
 
 *    construct an extensible, flexible, SUD-style/text-based game space using an
      inheritance hierarchy of objects that exhibit polymorphic behavior and rely
      extensively on templated storage containers;

 *    construct a library of object assets using the ObjectFactory pattern; and,
 
 *    utilize the TinyXML library to load, parse, and configure a game state from XML.


Implementation
===============================================
1.  Some portions of the Project was reorganized.
    For example, the Visual Studio Project file (.vxproj) moved to Source subdirectory.

2.  [XmlLite](https://msdn.microsoft.com/en-us/library/ms752872(v=vs.85).aspx) was used in lieu of TinyXML, mostly due to lack of Windows Unicode support.

    The XmlLite runtime file, Xmllite.dll, is integrated into the following operating systems and products:

        Windows Server 2008 or later
        Windows Vista or later
        Windows XP with Service Pack 3 or later
        Windows Server 2003 with Service Pack 2 or later
        Microsoft Internet Explorer 7 and later.

2.  CRoomFactory serves as the class factory for all CRoom objects.

3.  Implementation of a CGame class for the management of the CRoomMap instance and other application-level
    functions, such as:
    * Execute
    * IsGameFinished
    * LoadConfigFile

4.  XML parsing, in general ...

    There was deliberate effort made to decouple the core game classes from the details of XML parsing.
    To this end:
    * CXmlParser & CXmlGameDataHandler serve as the parsing engine;
    * PUZZLE_DATA, ROOM_DATA, NEIGHBOR_DATA serve as the intermediary raw data structures; and,
    * CGame invokes the instantiation of the parsing engine and the subsequent dispatching of
      the raw data structures to CRoomMap::Initialize member function.

