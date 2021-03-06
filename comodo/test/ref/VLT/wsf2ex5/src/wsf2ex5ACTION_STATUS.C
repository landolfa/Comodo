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

#include "wsf2ex5.h"
wsf2ex5WSF_RCSID("@(#) $Id: wsf2ex5ACTION_STATUS.C 593 2012-04-22 12:12:12Z landolfa $")

#include "wsf2ex5ACTION_STATUS.h"
#include "wsf2ex5ACTION_MGR.h"
#include "wsf2ex5CONFIG.h"
#include "wsf2ex5DATA.h"
#include "wsf2ex5Actions.h"

#include "wsf2libCONTROL.h"
#include "wsf2libLOG.h"

/** 
 * Constructor
 * 
 * @param fsm pointer to the state machine.
 * @param dbRoot database root of the debug flag.
 */
wsf2ex5ACTION_STATUS::wsf2ex5ACTION_STATUS(wsf2ex5ACTION_MGR& actionMgr,
				       wsf2libCONTROL& control,
				       wsf2ex5CONFIG& config,
				       wsf2ex5DATA& data) :
    wsf2libACTION_STATUS(wsf2ex5ACTION_STR_STATUS, actionMgr, control),
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
wsf2ex5ACTION_STATUS::~wsf2ex5ACTION_STATUS()
{
    wsf2libLOG_TRACE();
}

	

// __oOo__

