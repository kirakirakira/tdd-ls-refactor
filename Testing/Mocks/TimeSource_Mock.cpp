/*!
 * @file
 * @brief Implementation of TimeSource_Mock.
 *
 * Copyright (c) 2013 - General Electric - All rights reserved.
 */

#include <stdbool.h>
#include <stddef.h>
#include "CppUTestExt/MockSupport.h"
#include "TimeSource_Mock.h"
#include "I_TimeSource.h"

static TimeSourceTickCount_t GetTicks(I_TimeSource_t *timeSource)
{
   return mock().actualCall("GetTicks")
      .onObject((void *)timeSource)
      .returnValue().getIntValue();
}

static const I_TimeSource_Api_t tsApi =
   { GetTicks };

void TimeSource_Mock_Init(TimeSource_Mock_t *instance)
{
   instance->interface.api = &tsApi;
}
