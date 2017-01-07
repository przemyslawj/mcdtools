/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvtTrigger.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAEvtTrigger.h 7     3.12.10 12:59 Merz $
//
// $Modtime: 30.11.10 13:41 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAEvtTrigger.h $
// * 
// * 7     3.12.10 12:59 Merz
// * Trial Synchronization for Andreas Kreiter, manual trigger
// * 
// * 6     17.11.09 9:14 Paetzold
// * ManualTriggerCount
// * 
// * 5     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 4     18.12.06 12:45 Loeffler
// * docu changes
// * 
// * 3     5-06-02 17:23 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////
/*! \file
 \brief interface to the trigger event object
 */

#ifndef _MCSAEVTTRIGGER_H_
#define _MCSAEVTTRIGGER_H_

#include "MCSAEvent.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAEvtTrigger

//! Trigger event
/*! The trigge event is only a timestamp when the triggerwas detected. The interface
 * uses the base class functions
 */
class CMCSAEvtTrigger : public CMCSAEvent
{
public:
	CMCSAEvtTrigger();
	virtual ~CMCSAEvtTrigger();
	short GetADData();
	int GetManualTriggerCount();
	int GetTrialNumber();
	int GetStimulusNumber();

	virtual bool Read();
	virtual bool ReadNext();
	virtual long GetSize();
	CMCSAEvtTrigger& operator=(const CMCSAEvtTrigger& evt);

private:
	WORD m_wValue;
	int m_iManualTriggerCount;
	int m_iTrialNumber;
	int m_iStimulusNumber;

	void ReadMem();
};

/////////////////////////////////////////////////////////////////////////////
#endif
