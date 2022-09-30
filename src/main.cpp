/******************************************************************************
 * Copyright (c) 2022 Frank Ronneburg.  All rights reserved.
 *****************************************************************************/

/**
 * main.cpp ---
 *
 * Experiments with Audio and Video Data Collection
 */

#include "DataCollector.h"

#include <csignal>
#include <thread>
#include <syslog.h>

/*
 * BlockAllSignals
 *
 *    Sets up a signal mask for all threads spawned in this process (except the
 *    unblockable SIGKILL and SIGSTOP). NOTE this function has to be called
 *    before any threads are spawned so those threads can inherit the mask.
 *
 * @returns TRUE the signal mask was set up successfully.
 *
 */
static bool BlockAllSignals()
{
   sigset_t set;
   sigfillset(&set);
   if (0 != pthread_sigmask(SIG_BLOCK, &set, nullptr)) {
      return false;
   } else {
      return true;
   }
}

/*
 * WaitForShutdownSignal
 *
 *    Waits for a SIGINT signal from the system to initiate shutdown.
 *
 */

static void WaitForShutdownSignal()
{
   sigset_t set;
   sigfillset(&set);
   while (true) {
      int sig = 0;
      if (0 != sigwait(&set, &sig)) {
         syslog(LOG_ERR, "Received error from sigwait: %m");
         continue;
      } else if (sig != SIGINT) {
         syslog(LOG_INFO, "Received signal %d", sig);
         continue;
      } else {
         syslog(LOG_INFO, "Received shutdown signal %d", sig);
         break;
      }
   }
}

/*
 * main
 *
 *    Program entry point
 *
 */
int main()
{
   /* Start by initializing syslog. */
   openlog("data-collector", 0, 0);
   syslog(LOG_INFO, "Data Collector started: VERSION=%s", VERSION_STRING);

   /*
    * Our shutdown is going to be controlled by a SIGINT, and other that that
    * we want to ignore all signals coming in to any thread we create. So the
    * first thing to do is set up a signal mask that blocks all signals, which
    * we do here in the main thread so other threads will inherit the mask.
    */
   if (!BlockAllSignals()) {
      syslog(LOG_ERR, "Failed to block signals; bailing");
      return 0;
   } else {
      DataCollector dataCollector(0, 0);
      if (!dataCollector.Init()) {
         syslog(LOG_ERR, "Failed to initialize data collector");
      } else if (!dataCollector.Run()) {
         syslog(LOG_ERR, "Failed to start data collector");
      } else {
         WaitForShutdownSignal();
         dataCollector.Stop();
      }
   }

   return 0;
}
