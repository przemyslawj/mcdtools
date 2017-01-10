/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAChunk.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamAnsi/MCSAChunk.h 4     11-02-16 16:35 Paetzold $
//
// $Modtime: 11-02-16 14:20 $
//
// $Log: /MC_Rack_II/MC_StreamAnsi/MCSAChunk.h $
// * 
// * 4     11-02-16 16:35 Paetzold
// * Bug fix when merging for continous data and event timestamps:
// * handling of timestamps for event data
// * 
// * 3     23.04.06 22:44 Paetzold
// * Update for Merge
// * 
// * 2     5-06-02 17:07 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSACHUNK_H_
#define _MCSACHUNK_H_


#include "MCSATimeStamp.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAChunk

class CMCSAEvent;
class CMCSAStream;
class CMCSAChunk
{
public:
	CMCSAChunk();
	~CMCSAChunk();

	CMCSAChunk* Clone();
	long WriteChunk(FILE* pFile, DWORDLONG addtime);

	long GetFromHi();
	long GetFromLow();
	long GetToHigh();
	long GetToLow();
	long GetSize();
	CMCSATimeStamp* GetTimeStampTo();
	CMCSATimeStamp* GetTimeStampFrom();
	long ReadData(short * pBuffer);
	CMCSAEvent* GetFirstEvent();
	CMCSAEvent* GetFirstEvent(char* pBuffer);

	bool ReadNextEvent(CMCSAEvent* evt);

// Implementation
	CMCSATimeStamp*	m_pTimeStampFrom;
	CMCSATimeStamp*	m_pTimeStampTo;
	DWORDLONG m_qwSize;
	DWORDLONG m_qwPos;
	FILE* m_pFile;
	int m_iPos;
	CMCSAStream* m_pStreamImp;
	
	char m_id[8];
	short* m_Buffer;
};

/////////////////////////////////////////////////////////////////////////////

#endif
