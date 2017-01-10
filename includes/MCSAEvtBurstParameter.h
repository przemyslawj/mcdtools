/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2008-2009 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvtBurstParameter.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAEvtBurstParameter.h 4     1.06.10 11:55 Paetzold $
//
// $Modtime: 1.06.10 11:47 $
//
/////////////////////////////////////////////////////////////////////////////
/*! \file
 \brief interface to the Burst parameter event object
 */


#pragma once

#include "MCSAEvent.h"
#include "MCSAInfoBurstParameter.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAEvtBurstParameter command target

//! Burst parameter event
class CMCSAEvtBurstParameter : public CMCSAEvent
{
public:
	CMCSAEvtBurstParameter();
	virtual ~CMCSAEvtBurstParameter();

	virtual bool Read();
	virtual bool ReadNext();

	CMCSAEvtBurstParameter& operator=(const CMCSAEvtBurstParameter& evt);

    //! Channel of the event
	short GetChannel();
	//! HWID of the event
	short GetHWID();
    //! Unit ID (0: not sorted)
	short GetUnitId();
	//! Timestamp of the burst
	DWORDLONG GetTimestampOfBurst();
    //! Value of the parameter
    /*!
     \param ParameterID Index of the parameter. Get the number of parameters from CMCSAInfoBurstParameter
     \return Parameter value
    */
	float Parameter(unsigned long ParameterID);

private:
	long		GetSize();
	DWORDLONG*  m_pqwTick;
	DWORDLONG*	m_pqwTimeStampOfBurst;
	WORD*		m_pwChannel;
	WORD*		m_pwHWID;
	WORD*		m_pwUnitID;
	DWORDLONG*	m_pqwDurationOfBurst;
	int*		m_piNumberOfSpikes;
	float*		m_pfSpikeFrequency;


};
