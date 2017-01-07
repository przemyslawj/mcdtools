/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoTrigger.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoTrigger.h 11    3.12.10 12:59 Merz $
//
// $Modtime: 1.12.10 15:51 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAInfoTrigger.h $
// * 
// * 11    3.12.10 12:59 Merz
// * Trial Synchronization for Andreas Kreiter, manual trigger
// * 
// * 10    18.12.06 12:45 Loeffler
// * docu changes
// * 
// * 9     14.12.06 15:51 Jesinger
// * removed paths from #include statements
// * 
// * 8     15.08.06 11:22 Jesinger
// * changed include name "MCStream..." -> "MC_Stream..."
// * 
// * 7     24.06.03 9:50 Merz
// * added the function GetParameterUnit
// * 
// * 6     2.06.03 16:54 Merz
// * added the functions IsParameterTrigger and GetParameter for the
// * parameter trigger
// * 
// * 5     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 4     6-06-02 10:48 Patzwahl
// * changed GetInputBufferName() to GetInputBufferID()
// * 
// * 3     5-06-02 17:38 Patzwahl
/////////////////////////////////////////////////////////////////////////////
/*! \file
 \brief interface to the trigger info object
 */


#ifndef _MCSAINFOTRIGGER_H_
#define _MCSAINFOTRIGGER_H_

#include "MCStreamProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAInfoTrigger

//! Trigger info
class CMCSAInfoTrigger
{
public:
	CMCSAInfoTrigger();           // protected constructor used by dynamic creation
	virtual ~CMCSAInfoTrigger();

// Attributes
public:
	CMMEATriggerProperty m_TriggerProperty;

// Operations
public:

// Implementation
protected:
public:
	BOOL TrialSynchronization();
	char* GetParameterUnit();
	char* GetParameter();
    //! Is it a parameter trigger?
	BOOL IsParameterTrigger();

    //! Get trigger channel ID
	long GetChannel();
    //! Get dead time in ms
	long GetDeadTime();
    //! Get trigger threshold level
	long GetLevel();
    //! Get slope
    /*! \return
    <ul>
    <li>0: positive</li>
    <li>1: negative</li>
    </ul>
    */
	long GetSlope();
	long GetTriggeredStreamId();
	char* GetInputBufferID();
    //! Is it a digital trigger?
	BOOL IsDigitalTrigger();
	long GetDigitalTriggerValue();
	long GetDigitalTriggerMask();
    //! Get digital trigger type
    /*! \return 
    <ul>
    <li>0: '<'</li>
    <li>1: '='</li>
    <li>2: '>'</li>
    </ul>
    */
	long GetDigitalTriggerType();
};

/////////////////////////////////////////////////////////////////////////////
#endif
