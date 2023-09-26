#ifndef LOG_H
#define LOG_H

#include <stdlib.h>
#include <stdio.h>

// This macro is created by the compiler in the project settings.
// It is defined only when the program is compiled in debug mode
// That way we can define stuff only in debug mode or release mode.
#ifdef SUDOKU_DEBUG

	/**
	 * Simple logging macro
	 */
	#define LOG(msg, ...) printf("%s:%d %s: "msg"\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

	/**
	 * Terminates the program if x is false, and prints msg.
	 */
	#define ASSERT(x, msg, ...) if (!x) { LOG(msg, ##__VA_ARGS__); exit(-1); }

#else

	/**
	 * Simple logging macro (disabled in release mode)
	 */
	#define LOG(msg, ...)

	 /**
	  * Terminates the program if x is false, and prints msg (disabled in release mode)
	  */
	#define ASSERT(x, msg, ...)

#endif

#endif