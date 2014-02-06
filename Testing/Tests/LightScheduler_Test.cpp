extern "C"
{
#include <string.h>
#include "LightScheduler.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "DigitalOutputGroup_Mock.h"
#include "TimeSource_TestDouble.h"
#include "uassert_test.h"

TEST_GROUP(LightScheduler)
{
   LightScheduler_t scheduler;

   DigitalOutputGroup_Mock_t fakeDigitalOutputGroup;
   TimeSource_TestDouble_t fakeTimeSource;

   void setup()
   {
      DigitalOutputGroup_Mock_Init(&fakeDigitalOutputGroup);
      TimeSource_TestDouble_Init(&fakeTimeSource);

      memset(&scheduler, 0xFF, sizeof(scheduler));
   }

   void GivenThatTheLightSchedulerHasBeenInitialized()
   {
      LightScheduler_Init(&scheduler, (I_DigitalOutputGroup_t *)&fakeDigitalOutputGroup, (I_TimeSource_t *)&fakeTimeSource);
   }

   void WithLightScheduledToBeTurnedOn(uint8_t lightId, TimeSourceTickCount_t time)
   {
      LightScheduler_AddSchedule(&scheduler, lightId, true, time);
   }

   void WithLightScheduledToBeTurnedOff(uint8_t lightId, TimeSourceTickCount_t time)
   {
      LightScheduler_AddSchedule(&scheduler, lightId, false, time);
   }

   void WithScheduledTurnOnRemoved(uint8_t lightId, TimeSourceTickCount_t time)
   {
      LightScheduler_RemoveSchedule(&scheduler, lightId, true, time);
   }

   void WithScheduledTurnOffRemoved(uint8_t lightId, TimeSourceTickCount_t time)
   {
      LightScheduler_RemoveSchedule(&scheduler, lightId, false, time);
   }

   void WithTimeOf(TimeSourceTickCount_t time)
   {
      TimeSource_TestDouble_SetTicks(&fakeTimeSource, time);
   }

   void LightShouldBeTurnedOn(uint8_t lightId)
   {
      mock().expectOneCall("Write")
         .onObject(&fakeDigitalOutputGroup)
         .withParameter("channel", lightId)
         .withParameter("state", true);
   }

   void LightShouldBeTurnedOff(uint8_t lightId)
   {
      mock().expectOneCall("Write")
         .onObject(&fakeDigitalOutputGroup)
         .withParameter("channel", lightId)
         .withParameter("state", false);
   }

   void NoLightsShouldBeChanged()
   {
   }

   void WhenTheSchedulerIsRun()
   {
      LightScheduler_Run(&scheduler);
   }
};

TEST(LightScheduler, InitNullChecks)
{
   CHECK_ASSERTION_FAILED(LightScheduler_Init(NULL, (I_DigitalOutputGroup_t * )&fakeDigitalOutputGroup, (I_TimeSource_t * )&fakeTimeSource));
   CHECK_ASSERTION_FAILED(LightScheduler_Init(&scheduler, NULL, (I_TimeSource_t * )&fakeTimeSource));
   CHECK_ASSERTION_FAILED(LightScheduler_Init(&scheduler, (I_DigitalOutputGroup_t * )&fakeDigitalOutputGroup, NULL));
}

TEST(LightScheduler, AddScheduleNullChecks)
{
   CHECK_ASSERTION_FAILED(LightScheduler_AddSchedule(NULL, 1, true, 100));
}

TEST(LightScheduler, RemoveScheduleNullChecks)
{
   CHECK_ASSERTION_FAILED(LightScheduler_RemoveSchedule(NULL, 1, true, 100));
}

TEST(LightScheduler, RunNullChecks)
{
   CHECK_ASSERTION_FAILED(LightScheduler_Run(NULL));
}

TEST(LightScheduler, OneSchedule_TurnOnAtTheRightTime)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(1, 150);
   WithTimeOf(150);
   LightShouldBeTurnedOn(1);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, OneSchedule_TurnOnAtTheRightTime_DifferentLight)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(14, 150);
   WithTimeOf(150);
   LightShouldBeTurnedOn(14);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, OneSchedule_TurnOffAtTheRightTime)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOff(1, 150);
   WithTimeOf(150);
   LightShouldBeTurnedOff(1);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, OneSchedule_NotExecutedAtTheWrongTime)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(1, 150);
   WithTimeOf(130);
   NoLightsShouldBeChanged();
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, MultipleSchedules_SameTimeDifferentLights)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(1, 150);
   WithLightScheduledToBeTurnedOff(2, 150);
   WithTimeOf(150);
   LightShouldBeTurnedOn(1);
   LightShouldBeTurnedOff(2);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, MultipleSchedules_DifferentTimesSameLight)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOff(13, 150);
   WithLightScheduledToBeTurnedOn(13, 300);

   WithTimeOf(150);
   LightShouldBeTurnedOff(13);
   WhenTheSchedulerIsRun();

   WithTimeOf(300);
   LightShouldBeTurnedOn(13);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, MultipleSchedules_DifferentTimesDifferentLights)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOff(4, 150);
   WithLightScheduledToBeTurnedOn(13, 300);

   WithTimeOf(150);
   LightShouldBeTurnedOff(4);
   WhenTheSchedulerIsRun();

   WithTimeOf(300);
   LightShouldBeTurnedOn(13);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, OneSchedule_RemoveSchedule)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(13, 300);
   WithScheduledTurnOnRemoved(13, 300);

   WithTimeOf(300);
   NoLightsShouldBeChanged();
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, MultipleSchedules_RemoveSchedule)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(13, 300);
   WithLightScheduledToBeTurnedOff(34, 20);
   WithScheduledTurnOffRemoved(34, 20);

   WithTimeOf(20);
   NoLightsShouldBeChanged();
   WhenTheSchedulerIsRun();

   WithTimeOf(300);
   LightShouldBeTurnedOn(13);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, AssertOnRemoveInvalidSchedule)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(13, 300);
   CHECK_ASSERTION_FAILED(WithScheduledTurnOffRemoved(34, 20));
}

TEST(LightScheduler, SchedulesRemovedAfterRunning)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   WithLightScheduledToBeTurnedOn(1, 150);
   WithTimeOf(150);
   LightShouldBeTurnedOn(1);
   WhenTheSchedulerIsRun();
   NoLightsShouldBeChanged();
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, CanAddAndRemoveSchedulesWithoutRunningOutOfSchedules)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   for(uint8_t i = 0; i < MAX_SCHEDULES * 2; i++)
   {
      WithLightScheduledToBeTurnedOff(i, 20);
      WithScheduledTurnOffRemoved(i, 20);
   }

   WithLightScheduledToBeTurnedOn(1, 150);
   WithTimeOf(150);
   LightShouldBeTurnedOn(1);
   WhenTheSchedulerIsRun();
}

TEST(LightScheduler, AssertWhenScheduleIsAddedAndThereAreNoMoreSlots)
{
   GivenThatTheLightSchedulerHasBeenInitialized();

   for(uint8_t i = 0; i < MAX_SCHEDULES; i++)
   {
      WithLightScheduledToBeTurnedOff(i, 20);
   }

   CHECK_ASSERTION_FAILED(WithLightScheduledToBeTurnedOff(15, 20));
}
