// ********************************************************************************//
//
//  BEGIN ROGUE GAME
//
//*********************************************************************************//

//  SYSTEM INCLUDES
#include <conio.h>                       // Console I/O - supplies the getch() function

//  LOCAL INCLUDES
#include "ExtendedWin32Console.h"        // Simple Win32 console display engine

// MAP DIMENSIONS
#define MAP_WIDTH	40
#define MAP_HEIGHT	15

// TILE TYPES
#define TILE_ROCKFLOOR	0
#define TILE_WALL		1
#define TILE_CLOSEDDOOR	2
#define TILE_OPENDOOR	3
#define TILE_GRASS		4
#define TILE_TREE		5

//  DATA TYPES
struct TILE_TYPE
{
	char 	nCharacter;			// ASCII character for this tile type
	short	nColorCode;			// Color code for this tile type
	bool	bPassable;			// Set to true if you can walk on this tile
};

// FLOOR MAP
int nMapArray[MAP_HEIGHT][MAP_WIDTH] = { 
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 0, 0, 2, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 1 },
	{ 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2, 1 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 2, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 4, 4, 1, 1, 2, 1, 1, 4, 4, 4, 5, 0, 5 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 1, 0, 0, 0, 2, 0, 0, 0, 1, 4, 4, 1, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 5, 0, 5 },
	{ 4, 4, 1, 0, 0, 0, 1, 4, 4, 4, 1, 0, 0, 0, 1, 1, 1, 1, 4, 4, 4, 1, 0, 0, 1, 1, 1, 4, 4, 1, 0, 0, 0, 0, 1, 4, 4, 5, 0, 5 },
	{ 4, 4, 1, 1, 2, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 0, 0, 1, 4, 4, 4, 4, 1, 0, 0, 0, 0, 0, 5, 5, 5, 0, 5 },
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 1, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
	{ 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 4, 1, 0, 0, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5 },
	{ 4, 4, 4, 4, 4, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 4, 1, 1, 1, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4 },
	{ 4, 4, 4, 5, 4, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5, 0, 5, 0, 1, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4 },
	{ 4, 4, 4, 5, 4, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 5, 0, 0, 1, 4, 4, 4, 4, 4, 4, 1, 1, 0, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 5, 5, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 5, 0, 5, 0, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 1, 0, 0, 1, 4, 4, 4, 4, 1, 0, 0, 0, 0, 0, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4 },
	{ 4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }, 
};

// GLOBAL ARRAY USED TO DEFINE ALL TYPES OF TILES USED IN GAME
TILE_TYPE  sTileIndex[] = {
	{ '.', 7,  true },			// (0) TILE_ROCKFLOOR
	{ '#', 7,  false },			// (1) TILE_WALL
	{ '+', 9,  false },			// (2) TILE_CLOSEDDOOR
	{ '/', 11,  true },			// (3) TILE_OPENDOOR
	{ '.', 10, true },			// (4) TILE_GRASS
	{ 'T', 10, false }			// (5) TILE_TREE
};

// PLAYER'S CURRENT LOCATION
int nPlayerX;
int nPlayerY;

// FUNCTION PROTOTYPES
void DrawMap(void);
bool IsPassable(int x, int y);
void DrawTile(int x, int y);

void CloseDoorCommand(void);
void OpenDoorCommand(void);

// THE MAIN EVENT
void main(void)
{
	SetConsoleTitle("Roguelike Game");


	// Declare the player's position
	nPlayerX = 4;
	nPlayerY = 4;

	// Main game loop
	char nKey;
	while(true)
	{
		// draw floor map
		DrawMap();
		
		// draw player on screen
		console.SetColor(14);
		console.SetPosition(nPlayerX, nPlayerY);
		console << '@';

		// get user input
		nKey = getch();

		// process input
		int nDeltaX = 0;
		int nDeltaY = 0;
		switch(nKey)
		{
			// move up
			case 'w':
				nDeltaX = 0;
				nDeltaY = -1;
				break;

			// move left
			case 'a':
				nDeltaX = -1;
				nDeltaY = 0;
				break;

			// move right
			case 'd':
				nDeltaX = 1;
				nDeltaY = 0;
				break;

			// move down
			case 's':
				nDeltaX = 0;
				nDeltaY = 1;
				break;

			// open door
			case 'o':
				OpenDoorCommand();
				break;

			// close door
			case 'c':
				CloseDoorCommand();
				break;

			// escape key
			case 27:
				// Quit the program
				return;
		}

		// check if we can move in that direction
		if(IsPassable(nPlayerX + nDeltaX, nPlayerY + nDeltaY))
		{
			// if okay, move in the direction specified by the player
			nPlayerX += nDeltaX;
			nPlayerY += nDeltaY;
		}
	}
}

//********************************************************************************//
//
// IsPassable Function
// this function goes through the coordinates specified in the map array and returns
// TRUE if the coordinate is passable, FALSE if the player cannot occupy that coordinate.
//
//*********************************************************************************//
bool IsPassable(int x, int y)
{
	// makes sure coordinates are valid
	if(x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return false;

	// stores value of specified tile
	int nTileValue = nMapArray[y][x];

	// returns value if passable
	return sTileIndex[nTileValue].bPassable;
}

//********************************************************************************//
//
// DrawMap Function
// this function draw the floor map on the screen
//
//*********************************************************************************//
void DrawMap(void)
{
	for(int y = 0; y < MAP_HEIGHT; y++)
	{
		for(int x = 0; x < MAP_WIDTH; x++)
		{
			DrawTile(x, y);
		}
	}

	// draw notifications to the player
	console.SetPosition(2, 22);
	console << "\n\n  Directions: \n";
	console << "  Navigate using 'WASD' keys \n";
	console << "  Press 'o' to open doors \n";
	console << "  Press 'c' to close doors";
}

//*********************************************************************************//
//
//  DrawTile Function
//	this function draws a map tile for all coordinates given
//
//*********************************************************************************//
void DrawTile(int x, int y)
{
	// sets position of tiles
	console.SetPosition(x, y);

	// specifies tile type
	int nType = nMapArray[y][x];

	// sets tile color
	console.SetColor(sTileIndex[nType].nColorCode);

	// draws tiles to the screen
	console << sTileIndex[nType].nCharacter;
}

//********************************************************************************//
//
// OpenDoorCommand Function
// user command function converts closed doors to open ones specified by the player
//
//*********************************************************************************//
void OpenDoorCommand(void)
{
	// draw notifications to the player
	console.SetPosition(2, 22);
	console << "Which direction? (w, a, s, d)";

	// give cue as to where to look
	char nKey = getch();
	int nDeltaX = 0;
	int nDeltaY = 0;
	
	// clear screen and notification text
	console.Clear();

	// figure out which key player pressed
	switch(nKey)
	{
		// SOUTH
		case 's':
			nDeltaX = 0;
			nDeltaY = 1;
			break;

		// WEST
		case 'a':
			nDeltaX = -1;
			nDeltaY = 0;
			break;

		// EAST
		case 'd':
			nDeltaX = 1;
			nDeltaY = 0;
			break;

		// NORTH
		case 'w':
			nDeltaX = 0;
			nDeltaY = -1;
			break;

		// in case of invalid direcion
		default:
			// no direction specified, abort
			console.Clear();
			return;		
	}

	// make sure theres a door present in the direction stated by the user
	if(nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] == TILE_CLOSEDDOOR)
	{
		// if the door is opened, change its state to closed
		nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] = TILE_OPENDOOR;
	}
}

//*********************************************************************************//
//
// CloseDoorCommand Function
// user command function that converts an open door to a closed one
// at a tile specified by the user
//
//*********************************************************************************//
void CloseDoorCommand(void)
{
	// draw a notification to the user
	console.SetPosition(2, 22);
	console << "Which direction? (w, a, s, d)";

	// let the user decide where to look
	char nKey = getch();
	int nDeltaX = 0;
	int nDeltaY = 0;

	// clear the screen to get rid of the notification text
	console.Clear();

	// compute which tile the user specified
	switch(nKey)
	{
		// SOUTH
		case 's':
			nDeltaX = 0;
			nDeltaY = 1;
			break;

		// WEST
		case 'a':
			nDeltaX = -1;
			nDeltaY = 0;
			break;

		// EAST
		case 'd':
			nDeltaX = 1;
			nDeltaY = 0;
			break;

		// NORTH
		case 'w':
			nDeltaX = 0;
			nDeltaY = -1;
			break;

		// not a valid direction
		default:
			// no direction specified, so abort
			return;		
	}

	// make sure theres a door present in the direction stated by the user
	if(nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] == TILE_OPENDOOR)
	{
		// if there's a closed door, change its state to closed
		nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] = TILE_CLOSEDDOOR;
	}
}

// ********************************************************************************//
//
//  END ROGUE GAME
//
//*********************************************************************************//