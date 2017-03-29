/*!
 * @file
 * @brief Implementation of time source test double.
 */

#include "TimeSource_TestDouble.h"

TimeSourceTickCount_t GetTicks(I_TimeSource_t *instance)
{
   TimeSource_TestDouble_t *self = (TimeSource_TestDouble_t *)instance;
   return self->ticks;
}

static const I_TimeSource_Api_t timeSourceApi =
   {
      GetTicks
   };

void TimeSource_TestDouble_Init(TimeSource_TestDouble_t *instance)
{
   instance->interface.api = &timeSourceApi;

   instance->ticks = 0;
}

void TimeSource_TestDouble_SetTicks(TimeSource_TestDouble_t *instance, const TimeSourceTickCount_t ticks)
{
   instance->ticks = ticks;
}

void TimeSource_TestDouble_TickOnce(TimeSource_TestDouble_t *instance)
{
   instance->ticks += 1;
}

void TimeSource_TestDouble_TickMany(TimeSource_TestDouble_t *instance, const TimeSourceTickCount_t ticks)
{
   instance->ticks += ticks;
}
