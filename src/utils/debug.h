#ifndef _GFX_DEBUG_
#define _GFX_DEBUG_

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#ifdef VALIDATE_SHADERS
#define VALIDATE_SHADERS_TEST 1
#define DEBUG_TEST 1
#else
#define VALIDATE_SHADERS_TEST 0
#endif

#endif