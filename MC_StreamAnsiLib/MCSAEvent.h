/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvent.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamAnsi/MCSAEvent.h 8     11-02-16 16:34 Paetzold $
//
// $Modtime: 11-02-16 15:26 $
//
// $Log: /MC_Rack_II/MC_StreamAnsi/MCSAEvent.h $
// * 
// * 8     11-02-16 16:34 Paetzold
// * Bug fix when merging for continous data and event timestamps:
// * new functions for changing timestamps in events
// * 
// * 7     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 6     22.05.07 8:30 Loeffler
// * raw timestamp functions added
// * 
// * 5     15.12.06 15:50 Loeffler
// * docu changes
// * 
// * 4     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 3     5-06-02 17:09 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the base event object
 */

#ifndef _MCSAEVENT_H_
#define _MCSAEVENT_H_

#include "MCSATimeStamp.h"

class CMCSAChunk;
class CMCSAStream;


//! Retrieve Event Infos
/*! Base class of the different event types (spike, average, param, ...).
		It provides the time stamp interface, and the iteration from event to event.
		The example below shows how to iterate over spike events and extract the time
		point of the spike.
\code

IMCSEvtSpike EventSpike; 
EventSpike.AttachDispatch(m_MCSStream.GetFirstEvent());
int iContinue = 1;
while (iContinue == 1)
{
	int iSeconds = EventSpike.GetSecondFromStart();
	int iMilliS = EventSpike.GetMillisecondFromStart();
	int iMicroS = EventSpike.GetMicrosecondFromStart();
	int iNanoS = EventSpike.GetNanosecondFromStart();

	float fSpikeTimeStamp = iSeconds +
				static_cast<float>(iMilliS) / 1000 +
				static_cast<float>(iMicroS) / 1000000 +
				static_cast<float>(iNanoS) / 1000000000;

	iContinue = EventSpike.Next();
}
EventSpike.ReleaseDispatch();
}
\endcode
*/
class CMCSAEvent
{
public:
	CMCSAEvent();
	virtual ~CMCSAEvent();

//! Get Event time: Year part
/*!
\return Year part of the event time stamp
*/
	short GetYear();

//! Get Event time: Month part
/*!
\return Month part of the event time stamp
*/
	short GetMonth();

//! Get Event time: Day part
/*!
\return Day part of the event time stamp
*/
	short GetDay();

//! Get Event time: Hour part
/*!
\return Hour part of the event time stamp
*/
	short GetHour();

//! Get Event time: Minute part
/*!
\return Minute part of the event time stamp
*/
	short GetMinute();

//! Get Event time: Second part
/*!
\return Second part of the event time stamp
*/
	short GetSecond();

//! Get Event time: Millisecond part
/*!
\return Millisecond part of the event time stamp
*/
	short GetMillisecond();

//! Get Event time: Microsecond part
/*!
\return Microsecond part of the event time stamp
*/
	short GetMicrosecond();

//! Get Event time: Nanosecond part
/*!
\return Nanosecond part of the event time stamp
*/
	short GetNanosecond();

//! Get Event time relativ to the start of the recoding: Second part
/*!
\return Second part of the event time stamp
*/
	long GetSecondFromStart();

//! Get Event time relativ to the start of the recoding: Millisecond part
/*!
\return Millisecond part of the event time stamp
*/
	short GetMillisecondFromStart();

//! Get Event time relativ to the start of the recoding: Microsecond part
/*!
\return Microsecond part of the event time stamp
*/
	short GetMicrosecondFromStart();

//! Get Event time relativ to the start of the recoding: Nanosecond part
/*!
\return Nanosecond part of the event time stamp
*/
	short GetNanosecondFromStart();

//! Get Event time stamp
/*!
\return Time stamp of the event
*/
	CMCSATimeStamp* Get_TimeStamp();

    DWORDLONG GetRawTimeStamp();

//! Move to the next event
/*!
\return
			<ul>
			<li> 0 if there is no next event
			<li> >0 if successful
			</ul>
*/
	bool Next();

// Implementation

	SYSTEMTIME Get_SysTime() const;
	void Set_SysTime( SYSTEMTIME st );

	BOOL Get_DeepCopy() const;
	void Set_DeepCopy( BOOL b );

	CMCSAChunk* Get_Chunk() const;
	void Set_Chunk( CMCSAChunk* pChunk );

	CMCSAStream* Get_StreamImp() const;
	void Set_StreamImp( CMCSAStream* pStreamImp );

	long Get_ChunkSize() const;
	void Set_ChunkSize( long lChunkSize );
	long Get_Offset() const;
	void Set_Offset( long lOffset );
	long Get_OffsetNext() const;
	void Set_OffsetNext( long lOffsetNext );
	char* Get_pData() const;
	void Set_pData( char* pData );
	
	virtual bool Read();
	virtual bool ReadNext();
	
	virtual void ChangeTimestamp(DWORDLONG addtime);
	virtual bool HasEventTimeData();
	/**
	 * GetSize() returns the size of the Event in bytes
	 * @return size in bytes
	 **/
	virtual long GetSize() {return 0;};

	BOOL m_bDeepCopy;	//if FALSE m_pData from this Object is referenced after copy, so dont
						//delete m_pData by destroying yourself (handle with care!)
	CMCSAChunk*		m_pChunk;

	CMCSAStream*		m_pStreamImp;

	char*			m_pData;
	long			m_lChunkSize;
	long			m_lOffset;
	long			m_lOffsetNext;
	
	CMCSATimeStamp	m_TimeStamp;


protected:
	SYSTEMTIME	m_st;
};

/////////////////////////////////////////////////////////////////////////////

#endif	// _MCSAEVENT_H_
