/******************************************************************************
 * Copyright (c) 2022 Frank Ronneburg.  All rights reserved.
 *****************************************************************************/

/**
 * DataCollector.cpp ---
 *
 * Implementation of the DataCollector class.
 */

#include "DataCollector.h"

#include <atomic>
#include <syslog.h>

/*
 * DataCollector::DataCollector
 *
 *    See header file.
 *
 */
DataCollector::DataCollector(int variable, int otherVariable)
   : m_variable(variable)  // FRANK TODO
   , m_otherVariable(otherVariable) // FRANK TODO
{
   // FRANK TODO: what construction do we need???
}

/*
 * DataCollector::~DataCollector
 *
 *    See header file.
 *
 */
DataCollector::~DataCollector()
{
   // FRANK TODO: clean everything up
   // NOTE: it's possible to be destructed without having called Stop. Must handle that.
   syslog(LOG_INFO, "~DataCollector\n");
}

/*
 * DataCollector::Init
 *
 *    See header file.
 *
 */
bool DataCollector::Init(void)
{
   // FRANK TODO: do some stuff
   syslog(LOG_INFO, "DataCollector::Init\n");
   return true;
}

/*
 * DataCollector::Run
 *
 *    See header file.
 *
 */
bool DataCollector::Run(void)
{
   // FRANK TODO: initialize GStreamer, set up the caller-provided callback interface
   std::atomic<bool> ready = ATOMIC_FLAG_INIT;
   m_watchdogThread = std::make_shared<std::thread>(
      [this, &ready] { RunGStreamer(ready); } 
   );
   syslog(LOG_INFO, "DataCollector::Run waiting for watchdog");
   while (!ready) {
      std::this_thread::yield();
   }
   syslog(LOG_INFO, "DataCollector::Run ready flag is set");
   return true;
}

/*
 * DataCollector::Stop
 *
 *    See header file.
 *
 */
void DataCollector::Stop(void)
{
   syslog(LOG_INFO, "DataCollector::Stop signaling GStreamer shutdown");

   // FRANK TODO: kill the GStreamer mainloop
   m_variable = 1;
   m_watchdogThread->join();

   // FRANK TODO: clean up any resources allocated in "Run"
   syslog(LOG_INFO, "DataCollector::Stop completed GStreamer shutdown");
}

/*
 * DataCollector::RunGStreamer
 *
 *    Background thread to start GStreamer mainloop and wait for it to exit.
 *
 * @param  ready        [in] flag that is set once gstreamer is started.
 */
void DataCollector::RunGStreamer(std::atomic<bool> &ready)
{
   syslog(LOG_INFO, "RunGStreamer watchdog thread starting");

   // FRANK TODO: populate a GStreamer user_data, start the mainloop, run it. THEN:
   std::this_thread::sleep_for(std::chrono::seconds(5));
   ready = true;

   // FRANK TODO: wait for the mainloop to exit. For now, just wait until m_variable is non-zero
   while (m_variable == 0) {
      syslog(LOG_INFO, "GStreamer is running: %d", m_otherVariable++);
      std::this_thread::sleep_for(std::chrono::seconds(5));
   }

   // FRANK TODO: clean up anything set up in this function (clean up mainloop, etc)
   syslog(LOG_INFO, "RunGStreamer exiting watchdog thread");
}
