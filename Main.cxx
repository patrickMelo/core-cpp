/*
 * Main.cxx
 *
 * This file is part of the Core C++ source code.
 * Copyright 2014-2016 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Core.hxx"

// Auxiliary Functions

void SignalHandler( int signalCode )
{
	/****************************************/
	/* Put your signal handling stuff here. */
	/****************************************/

	/****************************************/
	/****************************************/
	/****************************************/

	if ( signalCode != SIGINT )
		exit( signalCode );
}

// Main

int main( int numberOfArguments, cstring* arguments )
{
	/* Attach the signal handler. */

	struct sigaction signalAction;

	signalAction.sa_handler = SignalHandler;
	sigemptyset( &signalAction.sa_mask );
	signalAction.sa_flags = 0;

	sigaction( SIGHUP, &signalAction, NULL );
	sigaction( SIGINT, &signalAction, NULL );
	sigaction( SIGQUIT, &signalAction, NULL );
	sigaction( SIGILL, &signalAction, NULL );
	sigaction( SIGABRT, &signalAction, NULL );
	sigaction( SIGFPE, &signalAction, NULL );
	sigaction( SIGSEGV, &signalAction, NULL );
	sigaction( SIGTERM, &signalAction, NULL );

	/* Print the header. */

	Info( "*", "" );
	Info( "*", "%s - Version %s (%s %s %s)", PROGRAM_NAME, VERSION_STRING, OS_NAME, ARCH_NAME, ENDIAN_NAMES[ IsBigEndian() ] );
	Info( "*", "Copyright %s", COPYRIGHT_INFO );
	Info( "*", "" );

	Debug( "*", "" );
	Debug( "*", "--- DEVELOPMENT VERSION ---" );
	Debug( "*", "" );

	/* Initialize the random number generator and disable the output buffering. */

	srand( time( NULL ) );
	setbuf( stdout, NULL );

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
