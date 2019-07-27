#ifndef _GFX_LOG_
#define _GFX_LOG_

#include "debug.h"

#include <stdarg.h>
#include <stdio.h>

#define PrintD(fmt, ...)                                       \
    do                                                         \
    {                                                          \
        if (DEBUG_TEST)                                        \
            fprintf(stderr, "%s:%d:%s(): " fmt "\n", __FILE__, \
                    __LINE__, __func__, __VA_ARGS__);          \
    } while (0)

#endif