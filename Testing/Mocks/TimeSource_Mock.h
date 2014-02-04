/*!
 * @file
 * @brief Simple mock of a time source object, used for testing.
 *
 * Copyright (c) 2013 - General Electric - All rights reserved.
 */

#ifndef TIMESOURCE_MOCK_H_
#define TIMESOURCE_MOCK_H_

extern "C"
{
#include "I_TimeSource.h"
}

typedef struct
{
   I_TimeSource_t interface;
} TimeSource_Mock_t;

void TimeSource_Mock_Init(TimeSource_Mock_t *instance);

#endif
