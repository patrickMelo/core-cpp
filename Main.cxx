/*
 * Main.cxx
 *
 * This file is part of the Core C++ source code.
 * Copyright 2014 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Core.hxx"

// Auxiliary Functions

void SignalHandler( int signal )
{
	/****************************************/
	/* Put your signal handling stuff here. */
	/****************************************/

	/****************************************/
	/****************************************/
	/****************************************/
	exit( signal );
}

// Main

int main( int numberOfArguments, cstring* arguments )
{
	/* Attach the signal handler */

	signal( SIGABRT, SignalHandler );
	signal( SIGINT, SignalHandler );
	signal( SIGTERM, SignalHandler );

	/* Print the header. */

	Info( "*", "" );
	Info( "*", "%s - Version %s (%s %s %s)", PROGRAM_NAME, VERSION_STRING, OS_NAME, ARCH_NAME, ENDIAN_NAMES[ IsBigEndian() ] );
	Info( "*", "Copyright %s", COPYRIGHT_INFO );
	Info( "*", "" );

	/* Initialized the random number generator. */

	srand( time( NULL ) );

	/*******************************/
	/* Put your program code here. */
	/*******************************/

	int returnCode = 0;

	/*******************************/
	/*******************************/
	/*******************************/

	/* Print the footer. */

	Info( "*", "" );
	Info( "*", "Bye!" );
	Info( "*", "" );

	return returnCode;
}
