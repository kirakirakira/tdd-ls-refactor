/*!
 * @file
 * @brief Time source that allows manual control of the time.
 */

#ifndef TIMESOURCE_TESTDOUBLE_H
#define TIMESOURCE_TESTDOUBLE_H

#include "I_TimeSource.h"

typedef struct
{
   I_TimeSource_t interface;
   TimeSourceTickCount_t ticks;
} TimeSource_TestDouble_t;

void TimeSource_TestDouble_Init(TimeSource_TestDouble_t *instance);
void TimeSource_TestDouble_SetTicks(TimeSource_TestDouble_t *instance, const TimeSourceTickCount_t ticks);
void TimeSource_TestDouble_TickOnce(TimeSource_TestDouble_t *instance);
void TimeSource_TestDouble_TickMany(TimeSource_TestDouble_t *instance, const TimeSourceTickCount_t ticks);

#endif
