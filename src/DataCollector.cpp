/******************************************************************************
 * Copyright (c) 2022 Frank Ronneburg.  All rights reserved.
 *****************************************************************************/

/**
 * DataCollector.cpp ---
 *
 * Implementation of the DataCollector class.
 */

#include "DataCollector.h"

#include <stdio.h>  // FRANK TODO: review whether this is needed

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
   printf("~DataCollector\n");
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
   printf("DataCollector::Init\n");
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
   // FRANK TODO: this will start the background thread
   printf("DataCollector::Run\n");
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
   // FRANK TODO: stop the background thread
   printf("DataCollector::Stop\n");
}
