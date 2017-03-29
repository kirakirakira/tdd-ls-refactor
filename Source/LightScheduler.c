/*!
 * @file
 * @brief Light scheduler implementation.
 */

#include "LightScheduler.h"
#include "uassert.h"

void LightScheduler_Init(LightScheduler_t *instance, I_DigitalOutputGroup_t *lights, I_TimeSource_t *timeSource)
{
   uint8_t i;

   uassert(instance);
   uassert(lights);
   uassert(timeSource);

   instance->light = lights;
   instance->ts = timeSource;
   instance->schCnt = 0;

   for(i = 0; i < MAX_SCHEDULES; i++)
   {
      instance->sch[i].use = false;
      instance->sch[i].st = false;
      instance->sch[i].t = 0;
      instance->sch[i].id = 0;
   }
}

void LightScheduler_AddSchedule(LightScheduler_t *instance, uint8_t lightId, bool lightState, TimeSourceTickCount_t time)
{
   uint8_t i;

   uassert(instance);

   instance->schCnt++;

   for(i = 0; i < MAX_SCHEDULES; i++)
   {
      if(!instance->sch[i].use)
         break;
   }

   uassert(i < MAX_SCHEDULES);

   instance->sch[i].st = lightState;
   instance->sch[i].t = time;
   instance->sch[i].id = lightId;
   instance->sch[i].use = true;
}

void LightScheduler_RemoveSchedule(LightScheduler_t *instance, uint8_t lightId, bool lightState, TimeSourceTickCount_t time)
{
   uint8_t i;

   uassert(instance);

   for(i = 0; i < MAX_SCHEDULES; i++)
   {
      if(instance->sch[i].use)
      {
         if(instance->sch[i].id == lightId)
         {
            if(instance->sch[i].st == lightState)
            {
               if(instance->sch[i].t == time)
               {
                  instance->sch[i].use = false;
                  instance->sch[i].st = false;
                  instance->sch[i].t = 0;
                  instance->sch[i].id = 0;

                  return;
               }
            }
         }
      }
   }

   uassert(false);
}

void LightScheduler_Run(LightScheduler_t *instance)
{
   uint8_t i;

   uassert(instance);

   for(i = 0; i < MAX_SCHEDULES; i++)
   {
      if(instance->sch[i].use)
      {
         if(instance->sch[i].t == TimeSource_GetTicks(instance->ts))
         {
            DigitalOutputGroup_Write(instance->light, instance->sch[i].id, instance->sch[i].st);

            instance->sch[i].use = false;
            instance->sch[i].st = false;
            instance->sch[i].t = 0;
            instance->sch[i].id = 0;
         }
      }
   }
}
