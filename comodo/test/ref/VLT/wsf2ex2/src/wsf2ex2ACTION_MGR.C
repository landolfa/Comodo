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

#include "wsf2ex2.h"
wsf2ex2WSF_RCSID("@(#) $Id: wsf2ex2ACTION_MGR.C 593 2012-04-22 12:12:12Z landolfa $")

#include "wsf2ex2ACTION_MGR.h"
#include "wsf2ex2CONFIG.h"
#include "wsf2ex2DATA.h"
#include "wsf2ex2Actions.h"
#include "wsf2ex2Defines.h"
#include "wsf2ex2Errors.h"

#include "wsf2libACTION.h"
#include "wsf2libLOG.h"
#include "wsf2libASSERT.h"
#include "wsf2libDB_ADDR.h"
#include "wsf2libCMDH_MGR.h"
#include "wsf2libCMDH_INTERNAL.h"
#include "wsf2libFSM.h"

#include "evhTHREADS.h"

#include "wsf2ex2ACTION_EXIT.h"
#include "wsf2ex2ACTION_STATE.h"
#include "wsf2ex2ACTION_VERBOSE.h"
#include "wsf2ex2ACTION_STANDBY.h"
#include "wsf2ex2ACTION_OFF.h"
#include "wsf2ex2ACTION_ONLINE.h"
#include "wsf2ex2ACTION_STATUS.h"
#include "wsf2ex2ACTION_TRACE.h"
#include "wsf2ex2ACTION_SELFTST.h"
#include "wsf2ex2ACTION_STOP.h"
#include "wsf2ex2ACTION_SETUP.h"
#include "wsf2ex2ACTION_VERSION.h"
#include "wsf2ex2ACTION_SIMULAT.h"
#include "wsf2ex2ACTION_INIT.h"
#include "wsf2ex2ACTION_DEBUG.h"




/** 
 * Constructor
 * Creates the shared data objects, the standard actions
 * and the custom actions.
 *
 * @param fsm pointer to the state machine.
 * @param dbRoot database root.
 */
wsf2ex2ACTION_MGR::wsf2ex2ACTION_MGR(const dbSYMADDRESS& dbRoot,
				     vltINT32 argCount, 
				     char* arg[],
				     wsf2libCMDH_MGR* eventMgr)
    : wsf2libACTION_MGR(dbRoot, wsf2libDB_ADDR(dbRoot, wsf2ex2DB_CONTROL_POINT), argCount, arg, eventMgr),
      mConfig(NULL),
      mData(NULL)
{
    wsf2libLOG_TRACE();

    mConfig = new wsf2ex2CONFIG(wsf2libDB_ADDR(dbRoot, wsf2ex2DB_CONFIG_POINT), argCount, arg);
    if (mConfig == NULL)
	{
        ErrAdd(wsf2ex2MOD, wsf2ex2ERR_NULL_POINTER, __FILE_LINE__, "wsf2ex2CONFIG");
        ObjStatus(FAILURE);	
	return;	
	}	
    if (mConfig->ErrStatus() == FAILURE || mConfig->ObjStatus() == FAILURE)
	{
        ErrAdd(wsf2ex2MOD, wsf2ex2ERR_CREATE, __FILE_LINE__, "wsf2ex2CONFIG");
        ObjStatus(FAILURE);	
	return;
	}
	
    mData = new wsf2ex2DATA(wsf2libDB_ADDR(dbRoot, wsf2ex2DB_DATA_POINT), *mConfig);
    if (mData == NULL)
	{
        ErrAdd(wsf2ex2MOD, wsf2ex2ERR_NULL_POINTER, __FILE_LINE__, "wsf2ex2DATA");
        ObjStatus(FAILURE);	
	return;	
	}	
    if (mData->ErrStatus() == FAILURE || mData->ObjStatus() == FAILURE)
	{
        ErrAdd(wsf2ex2MOD, wsf2ex2ERR_CREATE, __FILE_LINE__, "wsf2ex2DATA");
        ObjStatus(FAILURE);	
	return;
	}
}


/** 
 * Destructor
 * Delete all the actions and the shared data objects.
 */
wsf2ex2ACTION_MGR::~wsf2ex2ACTION_MGR()
{
    wsf2libLOG_TRACE();
    /*
     * No ASSERTPTR on mConfig and mData here since an error could have
     * stopped their instantiation: mData could still be NULL if mConfig instation
     * failed.
     */

    /*
     * Delete all SCXML actions and activities
     * Delete WSF actions
     *
     * NOTE: this has to be done here to avoid deleting DATA and CONFIG
     *       before the ACTIONs and ACTIVITIEs. ACTIONs may still need
     *       to access DATA and CONFIG in the destructor.
     */
    SCXMLDelAllActions();
    SCXMLDelAllActivities();
    DelAllActions();
    
    /*
     * Only now delete DATA and CONFIG
     */
    delete mData;
    delete mConfig;        
}


/** 
 * Create standard actions for standard commands.
 *
 * @param fsm Pointer to the state machine.
 * @param dbRoot database root.
 */
ccsCOMPL_STAT wsf2ex2ACTION_MGR::CreateActions()
{
    wsf2libLOG_TRACE();

    wsf2libACTION* action = NULL;


    action = new wsf2ex2ACTION_DEBUG(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_EXIT(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_INIT(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_OFF(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_ONLINE(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_SELFTST(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_SETUP(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_SIMULAT(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_STANDBY(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_STATE(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_STATUS(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_STOP(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_TRACE(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_VERBOSE(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);

    action = new wsf2ex2ACTION_VERSION(*this, *GetControl(), *mConfig, *mData);
    if (action == NULL) return FAILURE;
    if (action->ErrStatus() == FAILURE) return FAILURE;
    AddAction(action);


    return SUCCESS;
}

/** 
 * Create activities
 *
 */
ccsCOMPL_STAT wsf2ex2ACTION_MGR::CreateActivities(const char* procName, wsf2libFSM* fsm, evhTHREADS& threadsHandler)
{
    wsf2libLOG_TRACE();
    wsf2libASSERTPTR(procName);
    wsf2libASSERTPTR(fsm);	
	

    return SUCCESS;
}

/** 
 * Init all actions.
 */
ccsCOMPL_STAT wsf2ex2ACTION_MGR::Init()
{
    wsf2libLOG_TRACE();
    wsf2libASSERTPTR(mConfig);
    wsf2libASSERTPTR(mData);    
    ErrReset();

 
    /*
     * Initialize shared data.
     */
    if (InitControl() == FAILURE)
	{
	ErrAdd(wsf2ex2MOD, wsf2ex2ERR_INIT, __FILE_LINE__, "CONTROL");
	return FAILURE;
	}

    if (mConfig->Init() == FAILURE)
	{
	ErrAdd(wsf2ex2MOD, wsf2ex2ERR_INIT, __FILE_LINE__, "CONFIG");
	return FAILURE;
	}

    if (mData->Init() == FAILURE)
	{
	ErrAdd(wsf2ex2MOD, wsf2ex2ERR_INIT, __FILE_LINE__, "DATA");
	return FAILURE;
	}

    /*
     * Initialize all events
     */
    if (InitAllEvents() == FAILURE)
	{
	ErrAdd(wsf2ex2MOD, wsf2ex2ERR_INIT, __FILE_LINE__, "EVENTS");
	return FAILURE;	
	}

    /*
     * Initialize actions and local data.
     */
    if (InitAllActions() == FAILURE)
	{
	ErrAdd(wsf2ex2MOD, wsf2ex2ERR_INIT, __FILE_LINE__, "ACTIONS");
	return FAILURE;
	};
    
    return SUCCESS;
}

wsf2ex2CONFIG& wsf2ex2ACTION_MGR::GetConfig()
{
    wsf2libLOG_TRACE();
    return *mConfig;    
}

wsf2ex2DATA& wsf2ex2ACTION_MGR::GetData()
{
    wsf2libLOG_TRACE();
    return *mData;    
}


// __oOo__


