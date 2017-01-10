/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvtParam.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAEvtParam.h 5     25.01.08 9:18 Paetzold $
//
// $Modtime: 22.01.08 15:10 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAEvtParam.h $
// * 
// * 5     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 4     2.02.05 11:41 Merz
// * added function for the slope
// * 
// * 3     5-06-02 17:14 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSAEVTPARAM_H_
#define _MCSAEVTPARAM_H_

#include "MCSAEvent.h"
#include "MCSAInfoParam.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAEvtParam command target

class CMCSAEvtParam : public CMCSAEvent
{
public:
	CMCSAEvtParam();
	virtual ~CMCSAEvtParam();

	BOOL GetDataArray(short iChannel, float * buf);	// float FAR* buf
	float GetMin(short iChannel);
	float GetMax(short iChannel);
	float GetTmin(short iChannel);
	float GetTmax(short iChannel);
	float GetHeight(short iChannel);
	float GetWidth(short iChannel);
	float GetAmplitude(short iChannel);
	float GetArea(short iChannel);
	float GetNumber(short iChannel);
	float GetRate(short iChannel);
	float GetSlope(short iChannel);

	virtual bool Read();
	virtual bool ReadNext();
	virtual long GetSize();

	BOOL GetCArray(int iChannel, vector<float>* a);

	CMCSAEvtParam& operator=(const CMCSAEvtParam& evt);

	CMCSAInfoParam* m_pInfo;
	char*			m_pEvtData;
};

/////////////////////////////////////////////////////////////////////////////
#endif
