/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoParam.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoParam.h 7     25.01.08 9:18 Paetzold $
//
// $Modtime: 22.01.08 15:32 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAInfoParam.h $
// * 
// * 7     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 6     14.12.06 15:51 Jesinger
// * removed paths from #include statements
// * 
// * 5     15.08.06 11:22 Jesinger
// * changed include name "MCStream..." -> "MC_Stream..."
// * 
// * 4     2.02.05 11:40 Merz
// * added function for the slope
// * 
// * 3     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 2     5-06-02 17:31 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSAINFOPARAM_H_
#define _MCSAINFOPARAM_H_

#include "MCStreamProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAInfoParam command target

class CMCSAInfoParam
{
public:
	CMCSAInfoParam();           // protected constructor used by dynamic creation

// Attributes
public:
	//AnalyzerParams m_ParamTable[AN_NCHOICES]; //combined info from m_AnalyzerProperty and Buffer for Display
	AnalyzerParams m_ParamTable[AN_NCHOICES]; //combined info from m_AnalyzerProperty and Buffer for Display

	int  m_PositionTable[AN_NCHOICES];	//condensed info from m_AnalyzerProperty for Display

	CMIAnalyzerProperty m_AnalyzerProperty;

	CMTimeWindowProperty m_TimeWindowProperty;

	WORD m_wChannelSize;

// Operations
public:


// Implementation
protected:
public:
	virtual ~CMCSAInfoParam();

	char*  InputBufferName();

	int MinPos();
	int MaxPos();
	int TMinPos();
	int TMaxPos();
	int HeightPos();
	int WidthPos();
	int AmplitudePos();
	int AreaPos();
	int NumberPos();
	int RatePos();
	int NumTimeWindows();
	float TimeWindowTime1();
	float TimeWindowTime2();
	int TimeWindowChoice();
	int TimeWindowStartTriggerID();
	int TimeWindowStopTriggerID();
	int SlopePos();

};

/////////////////////////////////////////////////////////////////////////////
#endif
