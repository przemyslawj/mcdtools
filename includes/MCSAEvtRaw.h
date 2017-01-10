/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvtRaw.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamAnsi/MCSAEvtRaw.h 5     11-02-16 16:34 Paetzold $
//
// $Modtime: 11-02-16 15:26 $
//
// $Log: /MC_Rack_II/MC_StreamAnsi/MCSAEvtRaw.h $
// * 
// * 5     11-02-16 16:34 Paetzold
// * Bug fix when merging for continous data and event timestamps:
// * new functions for changing timestamps in events
// * 
// * 4     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 3     5-06-02 17:16 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSAEVTRAW_H_
#define _MCSAEVTRAW_H_

#include "MCSAEvent.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAEvtRaw

class CMCSAEvtRaw : public CMCSAEvent
{
public:
	CMCSAEvtRaw();

// Operations
public:
	virtual bool Read();
	virtual bool ReadNext();

	virtual void ChangeTimestamp(DWORDLONG addtime);
	virtual bool HasEventTimeData();

	virtual long GetSize();
	CMCSAEvtRaw& operator=(const CMCSAEvtRaw& evt);

// Implementation
protected:
	virtual ~CMCSAEvtRaw();
public:
	short GetADData(short iChannel);
	BOOL GetADDataArray(short * buf);
};

/////////////////////////////////////////////////////////////////////////////
#endif
