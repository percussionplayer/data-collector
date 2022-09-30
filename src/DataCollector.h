/******************************************************************************
 * Copyright (c) 2022 Frank Ronneburg.  All rights reserved.
 *****************************************************************************/

/**
 * DataCollector.h ---
 *
 * The DataCollector is a simple audio and video data collection system.
 * FRANK TODO: more documentation?
 */

#pragma once

class DataCollector {
public:
   /* Standard member functions. Delete all unused ones. */
   DataCollector(void)                              = delete;
   ~DataCollector(void);
   DataCollector(const DataCollector&)              = delete;
   DataCollector& operator= (const DataCollector&)  = delete;
   DataCollector(const DataCollector&&)             = delete;
   DataCollector& operator= (const DataCollector&&) = delete;

   /*
    * Constructor
    *
    * @param variable FRANK TODO
    * @param otherVariable FRANK TODO
    */
   DataCollector(int variable, int otherVariable);

   /*
    * DataCollector::Init
    *
    *    Initializes the DataCollector.
    *
    * @param FRANK TODO: any parameters???
    * @returns TRUE if initialization succeeded
    */
   bool Init();

   /*
    * DataCollector::Run
    *
    *    Starts the DataCollector.
    *
    * @param FRANK TODO: any parameters???
    * @returns TRUE if the DataCollector successfully started.
    */
   bool Run();

   /*
    * DataCollector::Stop
    *
    *    Stops the DataCollector.
    *
    * @param FRANK TODO: any parameters???
    */
   void Stop();

private:
   int m_variable;      // FRANK TODO: make these real and document
   int m_otherVariable;
};
