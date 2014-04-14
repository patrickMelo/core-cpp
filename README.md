Core C++
========

The Core C++ is a small C++ header used to start off new projects.

Features
--------

* Architecture and operating system detection macros:
  - ARCH_X86 defined for x86;
  - ARCH_X64 defined for x86_64;
  - ARCH_NAME defined with the compiler architecture name;
  - OS_LINUX defined for Linux systems;
  - OS_OSX defined for MacOS X systems;
  - OS_WINDOWS defined for Windows systems;
  - OS_NAME defined with the compiler operating system name;
  
* Fixed size integer type definitions:
  - int8, int16, int32, int64, uint8, uint16, uint32, uint64;
  
* Memory buffer macros:
  - NewBuffer( bufferSize );
  - CopyBuffer( int, out, size );
  - DeleteBuffer( buffer );
  
* Debugging macros:
  - Info( tag, message );
  - Warning( tag, message );
  - Error( tag, message );
  - Debug( tag, message );
  
* Endianess detection and conversion macros:
  - IsBigEndian();
  - Swap16( value );
  - Swap32( value );
  - Swap64( value );
  
* C-style string macros:
  - NewCString( stringSize );
  - DeleteCString( str );
  
* String conversion functions:
  - ToUpperCase( str );
  - ToLowerCase( str );
  - ToInt( string );
  - ToFloat( string );
  - ToBool( string );
  - FromInt( value )
  - FromFloat( value )
  - FromBool( value )
