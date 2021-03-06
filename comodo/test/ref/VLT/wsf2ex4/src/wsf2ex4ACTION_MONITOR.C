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

#include "wsf2ex4.h"
wsf2ex4WSF_RCSID("@(#) $Id: wsf2ex4ACTION_MONITOR.C 593 2012-04-22 12:12:12Z landolfa $")

#include "wsf2ex4ACTION_MONITOR.h"
#include "wsf2ex4ACTION_MGR.h"
#include "wsf2ex4CONFIG.h"
#include "wsf2ex4DATA.h"
#include "wsf2ex4Actions.h"
#include "wsf2ex4Errors.h"

#include "wsf2libCONTROL.h"
#include "wsf2libLOG.h"
#include "wsf2libASSERT.h"


/** 
 * Constructor
 * 
 * @param fsm pointer to the state machine.
 * @param dbRoot database root of the debug flag.
 */
wsf2ex4ACTION_MONITOR::wsf2ex4ACTION_MONITOR(wsf2ex4ACTION_MGR& actionMgr,
				       wsf2libCONTROL& control,
				       wsf2ex4CONFIG& config,
				       wsf2ex4DATA& data) :
    wsf2libACTION(wsf2ex4ACTION_STR_MONITOR),
    mActionMgr(actionMgr), 
    mControl(control), 
    mConfig(config), 
    mData(data)
{
    wsf2libLOG_TRACE();
}


/** 
 * Destructor
 */
wsf2ex4ACTION_MONITOR::~wsf2ex4ACTION_MONITOR()
{
    wsf2libLOG_TRACE();
}


/**
 * Init
 */
ccsCOMPL_STAT wsf2ex4ACTION_MONITOR::Init()
{
    wsf2libLOG_TRACE();
    wsf2libLOG_ACTION(GetName());
    ErrReset();

    return SUCCESS;
}

/**
 * Execute
 */
ccsCOMPL_STAT wsf2ex4ACTION_MONITOR::Execute()
{
    wsf2libLOG_TRACE();
    wsf2libLOG_ACTION(GetName());
    ErrReset();

    return SUCCESS;
}

/**
 * Complete. 
 */
ccsCOMPL_STAT wsf2ex4ACTION_MONITOR::Complete()
{
    wsf2libLOG_TRACE();
    wsf2libLOG_ACTION(GetName());
    ErrReset();

    return SUCCESS;
}

/**
 * Abort. 
 */
ccsCOMPL_STAT wsf2ex4ACTION_MONITOR::Abort()
{
    wsf2libLOG_TRACE();
    wsf2libLOG_ACTION(GetName());
    ErrReset();

    return SUCCESS;
}

/**
 * Reject 
 */
ccsCOMPL_STAT wsf2ex4ACTION_MONITOR::Reject()
{
    wsf2libLOG_TRACE();
    wsf2libLOG_ACTION(GetName());
    ErrReset();

    return SUCCESS;
}

/**
 * Supersede 
 */
ccsCOMPL_STAT wsf2ex4ACTION_MONITOR::Supersede()
{
    wsf2libLOG_TRACE();
    wsf2libLOG_ACTION(GetName());
    ErrReset();

    return SUCCESS;
}
	

// __oOo__

