/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2006-2009 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoSpikeParameter.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoSpikeParameter.h 7     17.03.09 15:16 Merz $
//
// $Modtime: 6.03.09 12:45 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAInfoSpikeParameter.h $
// * 
// * 7     17.03.09 15:16 Merz
// * changes for burst parameters
// * 
// * 6     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 5     18.12.06 12:45 Loeffler
// * docu changes
// * 
// * 4     15.12.06 15:50 Loeffler
// * docu changes
// * 
// * 3     14.12.06 15:51 Jesinger
// * removed paths from #include statements
// * 
// * 2     15.08.06 11:22 Jesinger
// * changed include name "MCStream..." -> "MC_Stream..."
// * 
// * 1     19.07.06 13:36 Merz
// * initial check in
// * 
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the spike parameter info object
 */


#ifndef _MCSAINFOSPIKEPARAMETER_H_
#define _MCSAINFOSPIKEPARAMETER_H_

#include "MCStreamProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAInfoSpikeParameter command target

//! Info about the data created from the spike parameter instrument
class CMCSAInfoSpikeParameter
{
public:
	CMCSAInfoSpikeParameter();

// Attributes
public:
	CMSpikeAnalyzerProperty m_SpikeAnalyzerProperty;

// Operations
public:


// Implementation
protected:
public:
	virtual ~CMCSAInfoSpikeParameter();

    //! Name of the input buffer which was used to analyze
	char* InputBufferName();
    //! Number of generated parameters
	int ParameterCount();
    //! Was parameter with ID ParameterId selected for recording?
	BOOL ParameterSelected(unsigned long ParameterId);
    //! Name of the parameter
	char* ParameterName(unsigned long ParameterId);
    //! Multiplication factor to calculate voltage value
	double ParameterFactor(unsigned long ParameterId);
    //! Exponent to calculate voltage value
	int ParameterExponent(unsigned long ParameterId);
    //! Unit string, e.g 'ms' or 's' or 'Hz'
	std::string ParameterUnit(unsigned long ParameterId);
    //! Number of units used for sorting
	int UnitCount();
    //! Unit selected for sorting?
	BOOL UnitSelected(unsigned long UnitId);
    //! Spike sort method used
    /*!
    * \return 
        <ul> 
        <li>0: no sorting</li>
        <li>1: sort window</li>
        </ul>
    */
	int UnitSortMethod();
};

/////////////////////////////////////////////////////////////////////////////
#endif
