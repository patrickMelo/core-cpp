/*
 * Core.hxx
 *
 * This file is part of the Core C++ source code.
 * Copyright 2014 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef CORE_H
#define CORE_H

// C

#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include <csignal>
#include <cinttypes>
#include <ctime>

// C++

#include <string>
#include <limits>
#include <algorithm>
#include <map>
#include <vector>
#include <new>

// Only Support C++11 Compilers

#if ( __cplusplus < 201103L )
	#error "Your compiler does not support the C++11 standard."
#endif

// Architectures

#if defined( i386 ) || defined( __i386 ) || defined( __i386__ )
	#define ARCH_X86
	#define ARCH_NAME "x86"
#elif defined( __amd64__ ) || defined( __amd64 ) || defined( __x86_64__ ) || defined( __x86_64 )
		#define ARCH_X64
		#define ARCH_NAME "x86_64"
	#else
		#error "Unsupported archtecture."
	#endif

// Operating Systems

#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		#define OS_LINUX
		#define OS_NAME "Linux"
	#elif defined( __APPLE__ ) || defined( __MACH__ )
			#define OS_OSX
			#define OS_NAME "OSX"
		#elif defined( _WIN32 ) || defined( _WIN64 ) || defined( __CYGWIN__ )
				#define OS_WINDOWS
				#define OS_NAME "Windows"
			#else
				#error "Unsupported operating system."
			#endif

#if defined( OS_LINUX ) || defined( OS_OSX )
	#define OS_UNIX
#endif

// Integer Types

typedef unsigned int	uint;
typedef uint8_t			uint8;
typedef uint16_t		uint16;
typedef uint32_t		uint32;
typedef uint64_t		uint64;

typedef int8_t	int8;
typedef int16_t	int16;
typedef int32_t	int32;
typedef int64_t	int64;

typedef unsigned long	ulong;
typedef unsigned short	ushort;

typedef std::map<std::string, int>	IntMap;
typedef std::vector<int>			IntList;

// Integer Union Types

union int64u {
	uint8	i8[ 8 ];
	uint16	i16[ 4 ];
	uint32	i32[ 2 ];
	uint64	i64;
};

union int32u {
	uint8	i8[ 4 ];
	uint16	i16[ 2 ];
	uint32	i32;
};

union int16u {
	uint8	i8[ 2 ];
	uint16	i16;
};

// String Types

typedef unsigned char			uchar;
typedef std::string				string;
typedef char*					cstring;
typedef std::vector<string>		StringList;
typedef std::map<string,string>	StringMap;

// Pointer Types

typedef uint8*	buffer;
typedef void*	pointer;

// General Constants

const uint		INVALID_INDEX	= std::numeric_limits<uint>::max();

const cstring	PROGRAM_NAME	= "Core C++";

const cstring	VERSION_STRING	= "0.1";
const uint		VERSION_MAJOR	= 0;
const uint		VERSION_MINOR	= 1;
const uint		VERSION_PATCH	= 0;

const cstring	COPYRIGHT_INFO	= "2014 Patrick L. Melo <patrick@patrickmelo.com.br>";

// Buffers

#define NewBuffer( bufferSize ) ( bufferSize > 0 ? new (std::nothrow) uint8[ bufferSize ] : NULL )
#define CopyBuffer( in, out, size ) memcpy( out, in, size )
#define DeleteBuffer( buffer ) if ( buffer ) { delete [] buffer; buffer = NULL; }

// Debug

#ifdef CORE_ENABLE_DEBUGGER
	#ifdef CORE_COLOR_MESSAGES
		#define Debug( tag, message, ...) printf( "\033[1;35m[%s] " message "\033[0m\n", tag, ##__VA_ARGS__ )
	#else
		#define Debug( tag, message, ...) printf( "[%s] " message "\n", tag, ##__VA_ARGS__ )
	#endif
#else
	#define Debug( tag, message, ... )
#endif

#ifdef CORE_COLOR_MESSAGES
	#define Info( tag, message, ... ) printf( "\033[1;32m[%s] " message "\033[0m\n" , tag, ##__VA_ARGS__ );
	#define Warning( tag, message, ... ) printf( "\033[1;33m[%s] " message "\033[0m\n" , tag, ##__VA_ARGS__ );
	#define Error( tag, message, ... ) printf( "\033[1;31m[%s] " message "\033[0m\n" , tag, ##__VA_ARGS__ );
#else
	#define Info( tag, message, ... ) printf( "[%s] " message "\n" , tag, ##__VA_ARGS__ );
	#define Warning( tag, message, ... ) printf( "[%s] Warning: " message "\n" , tag, ##__VA_ARGS__ );
	#define Error( tag, message, ... ) printf( "[%s] Error: " message "\n" , tag, ##__VA_ARGS__ );
#endif

// Endianness

const int16u	ENDIAN_WORD			= { { 0 } };
const cstring	ENDIAN_NAMES[ 2 ]	= { "Little Endian", "Big Endian" };

#define IsBigEndian() ( ENDIAN_WORD.i8[ 0 ] == 1 )

#define Swap16( value ) \
	value = ( ( ( value & 0x00FF ) << 8 ) | ( ( value & 0xFF00 ) >> 8 ) )

#define Swap32( value ) \
	value =	( ( ( value & 0x000000FF ) << 24 ) | \
			  ( ( value & 0x0000FF00 ) << 8 ) | \
			  ( ( value & 0x00FF0000 ) >> 8 ) | \
			  ( ( value & 0xFF000000 ) >> 24 ) )

#define Swap64( value ) \
	value = ( ( ( value & 0x00000000000000FF ) << 56 ) | \
			  ( ( value & 0x000000000000FF00 ) << 40 ) | \
			  ( ( value & 0x0000000000FF0000 ) << 24 ) | \
			  ( ( value & 0x00000000FF000000 ) << 8 ) | \
			  ( ( value & 0x000000FF00000000 ) >> 8 ) | \
			  ( ( value & 0x0000FF0000000000 ) >> 24 ) | \
			  ( ( value & 0x00FF000000000000 ) >> 40 ) | \
			  ( ( value & 0xFF00000000000000 ) >> 56 ) )

// Strings

#define NewCString( stringSize ) ( stringSize > 0 ? new (std::nothrow) char[ stringSize + 1 ] : NULL )
#define DeleteCString( str ) if ( str ) { delete [] str; str = NULL; }

#define ToUpperCase( str ) std::transform( str.begin(), str.end(), str.begin(), ::toupper )
#define ToLowerCase( str ) std::transform( str.begin(), str.end(), str.begin(), ::tolower )

#define ToInt( string ) std::atoll( string.c_str() )
#define ToFloat( string ) std::atof( string.c_str() )
#define ToBool( string ) ( ( string == "1" ) || ( string == "true" ) || ( string == "on" ) || ( string == "yes" ) )

static inline string FromInt( const int64 value )
{
	static char fromBuffer[ 30 ];

	#ifdef ARCH_X64
		sprintf( fromBuffer, "%ld", value );
	#else
		sprintf( fromBuffer, "%lld", value );
	#endif

	return fromBuffer;
}

static inline string FromFloat( const double value, const int precision = -1 )
{
	static char fromBuffer[ 30 ];

	switch ( precision )
	{
		case 1: sprintf( fromBuffer, "%.1f", value ); break;
		case 2: sprintf( fromBuffer, "%.2f", value ); break;
		case 3: sprintf( fromBuffer, "%.3f", value ); break;
		case 4: sprintf( fromBuffer, "%.4f", value ); break;
		case 5: sprintf( fromBuffer, "%.5f", value ); break;
		case 6: sprintf( fromBuffer, "%.6f", value ); break;
		case 7: sprintf( fromBuffer, "%.7f", value ); break;
		case 8: sprintf( fromBuffer, "%.8f", value ); break;
		default: sprintf( fromBuffer, "%f", value ); break;
	}

	return fromBuffer;
}

#define FromBool( value ) ( value ? "true" : "false" )

static inline string Implode( const StringList list, const string separator )
{
	string finalString = "";

	for ( StringList::const_iterator item = list.begin(); item != list.end(); ++item )
	{
		finalString += ( *item ) + separator;
	}

	return finalString.substr( 0, finalString.size() - separator.size() );
}

static inline void Explode( const string str, const string separator, StringList &list )
{
	list.clear();

	if ( str.empty() )
	{
		return;
	}

	int64 lastPosition = -1;
	int64 nextPosition = str.find( separator, 0 );

	while ( nextPosition != std::string::npos )
	{
		list.push_back( str.substr( lastPosition + 1, nextPosition - lastPosition - 1 ) );
		lastPosition = nextPosition;
		nextPosition = str.find( separator, lastPosition + 1);
	}

	if ( lastPosition < str.size() - 1 )
	{
		list.push_back( str.substr( lastPosition + 1 ) );
	}
}

static inline string EnsureSuffix( const string str, const string suffix )
{
	if ( str.size() < suffix.size() ) {
		return str + suffix;
	}

	return str.substr( str.size() - suffix.size() ) != suffix ? str + suffix : str;
}

static inline string RemoveSuffix( const string str, const string suffix )
{
	if ( str.size() < suffix.size() )
	{
		return str;
	}

	return str.substr( str.size() - suffix.size() ) == suffix ? str.substr( 0, str.size() - suffix.size() ) : str;
}

static inline string Trim( const string str )
{
	string trimmedString = str;
	uint64 leftPos = trimmedString.find_first_not_of( "\t\r\n " );

	if ( leftPos != std::string::npos )
	{
		trimmedString = trimmedString.erase( 0, leftPos );
	}

	uint64 rightPos = trimmedString.find_last_not_of( "\t\r\n " );

	if ( rightPos != std::string::npos )
	{
		trimmedString = trimmedString.erase( rightPos + 1 );
	}

	return trimmedString;
}

static inline string Replace( const string str, const string oldString, const string newString )
{
	string finalString = str;
	uint64 charIndex = finalString.find( oldString );
	uint oldStringLength = oldString.length();
	uint newStringLength = newString.length();

	while ( charIndex != std::string::npos )
	{
		finalString = finalString.substr( 0, charIndex ) + newString + finalString.substr( charIndex + oldStringLength );
		charIndex = finalString.find( oldString, charIndex + newStringLength );
	}

	return finalString;
}

static inline string AddSlashes( const string str )
{
	string escapedString = "";

	for ( int64 charIndex = 0; charIndex < str.size(); ++charIndex )
	{
		switch ( str[ charIndex ] )
		{
			case '"':
			case '\\':
			{
				escapedString += '\\';
				break;
			}
		}

		escapedString += str[ charIndex ];
	}

	return escapedString;
}

// Platform Specific Definitions

#ifdef OS_WINDOWS
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501 // Windows XP
	#endif

	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif

	extern "C" {
		#include <windows.h>
		#include <windowsx.h>
	}

	#define WINDOWS_TICK 10000000
	#define WINDOWS_UNIX_DIFFERENCE 11644473600LL

	#define ToUnixTime( time ) ( time / WINDOWS_TICK ) - WINDOWS_UNIX_DIFFERENCE

	static inline const cstring GetLastErrorMessage( void )
	{
		static char errorMessageBuffer[ 4097 ];
		FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), LANG_NEUTRAL, errorMessageBuffer, 4096, NULL );
		return errorMessageBuffer;
	}
#endif

#endif // CORE_H
