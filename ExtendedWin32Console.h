//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//	CExtendedWin32Console.h - Declaration for extended Win32-Console functionality.				//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//	This header defines the data structures and functionality required to create a console I/O	//
//	library similar in feature to the ubiquitous cout and cin objects. It is by no means 		//
//	compatible with those objects however and serves only as fullfilling a requirement for		//
//	the tutorials.																				//
//																								//
//	Coded by: Craig Stickel																		//
//	(C) April 9, 2007																			//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////// BEGIN HEADER /////////////////////////////////////////////

#pragma once

// System #includes ///////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN
#include <windows.h>			// Win32 commands
#include <stdlib.h>				// Borrows some number converting routines

// Symbolic Constants /////////////////////////////////////////////////////////////////////////

// Dimensions
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 35;

// System Configurations
const DWORD CONSOLE_MODE = ENABLE_PROCESSED_OUTPUT;

// CExtendedWin32Console Class Declaration ////////////////////////////////////////////////////
class CExtendedWin32Console
{
	public:
		// Constructors and Destructors ///////////////////////////////////////////////////////

		// Default constructor
		CExtendedWin32Console()
		{
			// Retrieve console handles for input and output
			this->hConsoleInput		= (HWND)GetStdHandle( STD_INPUT_HANDLE );
			this->hConsoleOutput	= (HWND)GetStdHandle( STD_OUTPUT_HANDLE );

			// Configure console modes
			SetConsoleMode( this->hConsoleInput, NULL );
			SetConsoleMode( this->hConsoleOutput, CONSOLE_MODE );	

			// Set console screen size
			SMALL_RECT smRect;
			smRect.Left = 0;
			smRect.Top = 0;
			smRect.Right = SCREEN_WIDTH - 1;
			smRect.Bottom = SCREEN_HEIGHT - 1;
			SetConsoleWindowInfo( this->hConsoleOutput, TRUE, &smRect );

			// Hide the cursor
			CONSOLE_CURSOR_INFO info;
			info.bVisible	= false;
			info.dwSize		= 100;
			SetConsoleCursorInfo( this->hConsoleOutput, &info );
		}

		~CExtendedWin32Console()
		{
		}
		
		// Public Methods /////////////////////////////////////////////////////////////////////

		// Clears the screen
		void Clear( void )
		{
			// Change the screen mode to allow wrapping
			SetConsoleMode( this->hConsoleOutput, ENABLE_WRAP_AT_EOL_OUTPUT );

			// Read the current attribute
			CONSOLE_SCREEN_BUFFER_INFO info;
			GetConsoleScreenBufferInfo( this->hConsoleOutput, &info );
			
			// Clear the screen
			COORD dwCoord		= { 0, 0 };	
			DWORD dwWritten;

			FillConsoleOutputCharacter( this->hConsoleOutput, ' ', SCREEN_WIDTH * SCREEN_HEIGHT,
				dwCoord, &dwWritten );

			FillConsoleOutputAttribute( this->hConsoleOutput, info.wAttributes, 
				SCREEN_WIDTH * SCREEN_HEIGHT, dwCoord, &dwWritten );

			// Move cursor back to start of the screen (coordinates 0,0)
			SetConsoleCursorPosition( this->hConsoleOutput, dwCoord );

			// Change back to the normal console mode
			SetConsoleMode( this->hConsoleOutput, CONSOLE_MODE );
		}

		// Draws a character to the console
		CExtendedWin32Console &operator <<( char nCharacter )
		{
			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, &nCharacter, 1, &dwWritten, NULL );

			// Return this instance to expediate concurrent function calls
			return *this;
		}

		// Draws a string to the console
		CExtendedWin32Console &operator <<( const char * p_szString )
		{
			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, p_szString, strlen( p_szString ), &dwWritten, NULL );
	
			// Return this instance to expediate concurrent function calls
			return *this;
		}

		// Draws an integer to the console
		CExtendedWin32Console &operator <<( signed int nInt )
		{
			// Convert the integer into a string
			char szBuffer[ 12 ];
			itoa( nInt, szBuffer, 10 );

			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, szBuffer, strlen( szBuffer ), &dwWritten, NULL );

			return *this;
		}

		CExtendedWin32Console &operator <<( signed long nInt )
		{
			// Convert the integer into a string
			char szBuffer[ 12 ];
			itoa( nInt, szBuffer, 10 );

			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, szBuffer, strlen( szBuffer ), &dwWritten, NULL );
		}

		CExtendedWin32Console &operator <<( signed short nInt )
		{
			// Convert the integer into a string
			char szBuffer[ 12 ];
			itoa( nInt, szBuffer, 10 );

			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, szBuffer, strlen( szBuffer ), &dwWritten, NULL );
		}

		CExtendedWin32Console &operator <<( unsigned int nInt )
		{
			// Convert the integer into a string
			char szBuffer[ 12 ];
			itoa( nInt, szBuffer, 10 );

			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, szBuffer, strlen( szBuffer ), &dwWritten, NULL );
		}

		CExtendedWin32Console &operator <<( unsigned long nInt )
		{
			// Convert the integer into a string
			char szBuffer[ 12 ];
			itoa( nInt, szBuffer, 10 );

			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, szBuffer, strlen( szBuffer ), &dwWritten, NULL );
		}

		CExtendedWin32Console &operator <<( unsigned short nInt )
		{
			// Convert the integer into a string
			char szBuffer[ 12 ];
			itoa( nInt, szBuffer, 10 );

			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, szBuffer, strlen( szBuffer ), &dwWritten, NULL );
		}

		// Draws a double to the console
		CExtendedWin32Console &operator <<( double dDouble )
		{
			// Convert the double to a string
			int nDec;
			int nSign;
			char *p_szBuffer = _fcvt( dDouble, 7, &nDec, &nSign );

			// Create a copy of the string
			int nLen = strlen( p_szBuffer );
			char *p_szString = new char[ nLen + 3 ];	// +1 for negative sign (if needed), +1 for
														// decimal point, +1 for null character

			// Add the negative if not present
			if( nSign )
			{
				p_szString[0] = '-';
				nSign = 1;				// Just in case for the next command (nSign is not guaranteed to 
										// be 1 if a negative symbol is needed)
			}

			// Copy up until the decimal point
			strncpy( p_szString + nSign, p_szBuffer, nDec );

			// Insert decimal point
			p_szString[ nDec + nSign ] = '.';

			// Copy remaining portion
			strcpy( p_szString + nSign + nDec + 1, p_szBuffer + nDec );

			// Remove any trailing zeros
			int nDrawLen;
			for( nDrawLen = nLen; nDrawLen > 0; nDrawLen-- )
			{
				if( p_szString[nDrawLen] == '0' )
					nDrawLen--;
				else
					break;
			}

			// Because of the way the method works, nDrawLen is actually one less than it should be
			nDrawLen++;

			DWORD dwWritten;
			WriteConsole( this->hConsoleOutput, p_szString, nDrawLen, &dwWritten, NULL );
			
			// Deallocate memory
			delete [] p_szString;

			// Return this instance to expediate concurrent function calls
			return *this;
		}

		// Changes the color attributes of the console output
		void SetColor( int nColor )
		{
			SetConsoleTextAttribute( this->hConsoleOutput, nColor );
		}

		// Changes the current position of console output
		void SetPosition( int nPosX, int nPosY )
		{
			COORD dwCoord = { nPosX, nPosY };
			SetConsoleCursorPosition( this->hConsoleOutput, dwCoord );
		}

	private:
		// Private Properties /////////////////////////////////////////////////////////////////

		// Input handle for the console
		HWND hConsoleInput;

		// Output handle for the console
		HWND hConsoleOutput;
	
} console;

//////////////////////////////////////// END OF HEADER ///////////////////////////////////////////