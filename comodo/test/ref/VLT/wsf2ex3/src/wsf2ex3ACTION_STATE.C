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
wsf2ex3WSF_RCSID("@(#) $Id: wsf2ex3ACTION_STATE.C 593 2012-04-22 12:12:12Z landolfa $")

#include "wsf2ex3ACTION_STATE.h"
#include "wsf2ex3ACTION_MGR.h"
#include "wsf2ex3CONFIG.h"
#include "wsf2ex3DATA.h"
#include "wsf2ex3Actions.h"

#include "wsf2libCONTROL.h"
#include "wsf2libLOG.h"

/** 
 * Constructor
 * 
 * @param fsm pointer to the state machine.
 * @param dbRoot database root of the debug flag.
 */
wsf2ex3ACTION_STATE::wsf2ex3ACTION_STATE(wsf2ex3ACTION_MGR& actionMgr,
				       wsf2libCONTROL& control,
				       wsf2ex3CONFIG& config,
				       wsf2ex3DATA& data) :
    wsf2libACTION_STATE(wsf2ex3ACTION_STR_STATE, actionMgr, control),
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
wsf2ex3ACTION_STATE::~wsf2ex3ACTION_STATE()
{
    wsf2libLOG_TRACE();
}

	

// __oOo__

