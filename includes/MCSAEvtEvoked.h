/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvtEvoked.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAEvtEvoked.h 7     14.11.08 11:35 Loeffler $
//
/////////////////////////////////////////////////////////////////////////////
/*! \file
 \brief interface to the averager event object
 */


#ifndef _MCSAEVTEVOKED_H_
#define _MCSAEVTEVOKED_H_

#include "MCSAEvent.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAEvtEvoked command target

//! Averager event
class CMCSAEvtAverage : public CMCSAEvent
{
public:
	CMCSAEvtAverage();           

    //! Get number of data samples
	long GetCount();
    //! Get number of time windows used for the average
	long GetTimeWindowCount();
    //! Get raw ADC data
	short GetADData(int iIndex);
    //! Get the whole array of data
    /*!
    \param buf must be an array of short with length of GetCount() 
    */
	BOOL GetADDataArray(short * buf);
    //! Channel of the event
	short GetChannel();
	short GetHWID();

// Operations
public:
	virtual bool Read();
	virtual bool ReadNext();
	virtual long GetSize();
	CMCSAEvtAverage& operator=(const CMCSAEvtAverage& evt);

// Implementation
protected:
	virtual ~CMCSAEvtAverage();

private:
	void SetMemberPointers();

	DWORDLONG*  m_pqwTick;
	WORD*		m_pwChannel;
	short* m_pHWID;
	short m_HWID;
	WORD*		m_pwNumOfWindows;
	DWORD*		m_pdwSPS;
	WORD*		m_pwData;
};

/////////////////////////////////////////////////////////////////////////////
#endif
