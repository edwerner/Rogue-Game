Rogue Game
==========

Console application created in C++ using C text interfaces `conio.h` and `ExtendedWin32Console.h` for color output and text positioning.

![](RogueGame/media/roguelike_game_001.jpg)

Compile:
---------
    g++ -c main.cpp
    g++ main.o -o main

Run:
-----
    ./main

Directions
----------

Press `WASD` keys to move the character around the level. To open doors, position the character next to the door and press the `o` key. You must confirm which direction the door is relative to your character by pressing the `WASD` keys. To close the door, do the same using the `c` key to initiate. Green `.` characters are grass, `#` characters are walls, green `T` characters are trees, locked doors are `+` characters and open doors are `/` characters. Trees and walls are impenetrable.
