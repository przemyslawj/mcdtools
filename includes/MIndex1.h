/////////////////////////////////////////////////////////////////////////////
//
// MC_Rack
// Copyright (C) 2000 Multi Channel Systems, all rights reserved
//
// $Workfile: MIndex1.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamIncANSI/MIndex1.h 6     5.10.06 15:21 Paetzold $
//
// $Modtime: 1.10.06 9:39 $
//
// $Log: /MC_Rack_II/MC_StreamIncANSI/MIndex1.h $
// * 
// * 6     5.10.06 15:21 Paetzold
// * Bugfix in merging index
// * 
// * 5     23.04.06 22:49 Paetzold
// * update for Merge
// * 
// * 4     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 3     3.04.03 16:12 Patzwahl
// * removed comments
// * 
// * 2     5-06-02 16:40 Patzwahl
// * added HasIndexes() and HasSweeps() methods
// * 
// * 1     14-08-00 15:54 Patzwahl
// * initial check in
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MINDEX1_H_
#define _MINDEX1_H_

#include "MCStream.h"

#ifndef _MC_RACK
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;
#endif

/////////////////////////////////////////////////////////////////////////////

class CMBufferStateMap;
class CMIndex1Item;
class CMRingBuffer;
struct INDEX1HDR;

#ifdef _MC_RACK
typedef CArray<DWORDLONG, DWORDLONG&> CMATimesArray;
typedef CArray<CMIndex1Item, CMIndex1Item&> CMAIndexArray;
#else
typedef vector<DWORDLONG> CMATimesArray;
typedef vector<CMIndex1Item> CMAIndexArray;
#endif


class CMIndex1Item
{

public:
	CMIndex1Item();
	CMIndex1Item(DWORDLONG qwTickFrom,DWORDLONG qwPos);


	INDEX1 m_Index1;
private:
};


/*
 *  index of the written segments
 *
 *  the class handles the index headers and the index entries:
 *  initializing, reading and writing
 *
 *  the index items are stored in an array and also written after stop
 *
 *  this class is to be used by the OLE object as well
 */

class CMIndex1
{
//	DECLARE_SERIAL(CMIndex1)
public:
	CMIndex1Item* GetAt(DWORD dwIndex);
	CMIndex1();
	CMIndex1(CMIndex1& index);
	CMIndex1& operator=(CMIndex1& index);
	~CMIndex1();
	void Destroy();
	void AddIndex(CMIndex1& index,DWORDLONG addtime,DWORDLONG filepos);

	void Add(DWORDLONG qwFrom,DWORDLONG qwPos);
	bool HasSweeps();
	bool HasIndexes();

	void WriteHeaders(FILE* pFile,char* pcFileName,DWORD dwStreamCount);
	BOOL ReadHeaders(FILE* pFile);
	void WriteItems(FILE* pFile);
	BOOL ReadItems(FILE* pFile);
	BOOL CheckIndex(FILE* pFile);

	CMATimesArray* m_parrSweepStartTimes;
	CMATimesArray* m_parrSweepEndTimes;

	CMAIndexArray m_arrIndex; //array of index itams
	INDEX1MCSHDR m_IdxHdr;

private:


	DWORDLONG m_qwIndexOffset;

};

#endif	// _MINDEX1_H_
