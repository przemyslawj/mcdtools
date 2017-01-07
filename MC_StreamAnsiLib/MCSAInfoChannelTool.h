/////////////////////////////////////////////////////////////////////////////
//
// MC_Rack
// Copyright (C) 2009 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoChannelTool.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoChannelTool.h 2     9.11.09 15:45 Merz $
//
// $Modtime: 5.11.09 15:44 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAInfoChannelTool.h $
// * 
// * 2     9.11.09 15:45 Merz
// * added an interface for the channel tool stream
// * 
// * 1     13.05.09 16:44 Merz
// * initial check in
// * 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSAINFOCHANNELTOOL_H_
#define _MCSAINFOCHANNELTOOL_H_
#include "MCStreamProperty.h"

#include <string>

class CMCSAInfoChannelTool
{
public:
	CMCSAInfoChannelTool();           // protected constructor used by dynamic creation

	CMChannelToolProperty m_ChannelToolProperty;

	std::string InputBufferName() const;
	std::string RefChannelName() const;
};
#endif
