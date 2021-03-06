/*******************************************************************************
*    E.S.O. - VLT project
*
*    "@(#) $Id$"
*
* who                when       what
* ----------------  ----------  ----------------------------------------------
* COMODO            -           Created.
* 
*/

#define _POSIX_SOURCE 1
#include "vltPort.h"

#include "wsf2ex3.h"
wsf2ex3WSF_RCSID("@(#) $Id: wsf2ex3ACTIVITY_MONITOR.C 593 2012-04-22 12:12:12Z landolfa $")

#include "wsf2ex3ACTIVITY_MONITOR.h"
#include "wsf2ex3CONFIG.h"
#include "wsf2ex3DATA.h"

#include "wsf2libCONTROL.h"
#include "wsf2libLOG.h"
#include "wsf2libFSM.h"

#include "evhTHREADS.h"

#include <unistd.h>


/** 
 * Constructor
 */
wsf2ex3ACTIVITY_MONITOR::wsf2ex3ACTIVITY_MONITOR(const std::string& procName, 
	wsf2libFSM* fsm, 
	evhTHREADS& threadsHandler, 
	wsf2libCONTROL& control,
	wsf2ex3CONFIG& config,
	wsf2ex3DATA& data) :
    wsf2libSCXML_ACTIVITY("MONITOR", procName, threadsHandler),
    mFsm(fsm),
    mControl(control),
    mConfig(config),
    mData(data)
{
    wsf2libLOG_TRACE();
}


/** 
 * Destructor
 */
wsf2ex3ACTIVITY_MONITOR::~wsf2ex3ACTIVITY_MONITOR()
{
    wsf2libLOG_TRACE();
}


/**
 * run
 */
void wsf2ex3ACTIVITY_MONITOR::run()
{
    /*
     * Here goes your thread code!
     */
     /*
     while (isRunning())
     	{
     	wsf2libLOG(LOG_INFO) << "Thread MONITOR!";
     	sleep(2);
     	}
     */
}

// __oOo__


