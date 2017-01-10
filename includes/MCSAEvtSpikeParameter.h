/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2006 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvtSpikeParameter.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAEvtSpikeParameter.h 5     17.03.09 15:16 Merz $
//
// $Modtime: 7.03.09 15:50 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAEvtSpikeParameter.h $
// * 
// * 5     17.03.09 15:16 Merz
// * changes for burst parameters
// * 
// * 4     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 3     18.12.06 12:45 Loeffler
// * docu changes
// * 
// * 2     14.12.06 16:33 Jesinger
// * removed linux warnings
// * 
// * 1     19.07.06 13:36 Merz
// * initial check in
// * 
/////////////////////////////////////////////////////////////////////////////
/*! \file
 \brief interface to the spike parameter event object
 */


#ifndef _MCSAEVTSPIKEPARAMETER_H_
#define _MCSAEVTSPIKEPARAMETER_H_

#include "MCSAEvent.h"
#include "MCSAInfoSpikeParameter.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAEvtSpikeParameter command target

//! Spike parameter event
class CMCSAEvtSpikeParameter : public CMCSAEvent
{
public:
	CMCSAEvtSpikeParameter();
	virtual ~CMCSAEvtSpikeParameter();

	virtual bool Read();
	virtual bool ReadNext();

	CMCSAEvtSpikeParameter& operator=(const CMCSAEvtSpikeParameter& evt);

    //! Channel of the event
	short GetChannel();
	//! HWID of the event
	short GetHWID();
    //! Unit ID (0: not sorted)
	short GetUnitId();
    //! Value of the parameter
    /*!
     \param ParameterID Index of the parameter. Get the number of parameters from CMCSAInfoSpikeParameter
     \return Parameter value
    */
	float Parameter(unsigned long ParameterID);

private:
	long		GetSize();
	DWORDLONG*  m_pqwTick;
	WORD*		m_pwChannel;
	WORD*		m_pwHWID;
	WORD*		m_pwUnitID;
	DWORDLONG*	m_pqwISI;
	float*		m_pfRate;
	DWORDLONG*	m_pqwSpikeTimeStamp;

};

/////////////////////////////////////////////////////////////////////////////
#endif
