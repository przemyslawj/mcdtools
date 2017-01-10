/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoEvoked.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoEvoked.h 7     14.12.06 15:51 Jesinger $
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSAINFOEVOKED_H_
#define _MCSAINFOEVOKED_H_
#include <vector>
#include "MCStreamProperty.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CMCSAInfoEvoked

class CMCSAInfoAverage
{
public:
	CMCSAInfoAverage();           // protected constructor used by dynamic creation

// Attributes
public:

	CMEvokedProperty m_EvokedProperty;

// Operations
public:


// Implementation
//protected:
	virtual ~CMCSAInfoAverage();

	char* GetTriggerBufferID();
	float GetTimeWindowStartTime();
	float GetTimeWindowWindowExtend();
	short GetMaxTimeWindowCount();
};

/////////////////////////////////////////////////////////////////////////////
#endif
