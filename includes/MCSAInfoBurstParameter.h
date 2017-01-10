/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2008-2009 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoBurstParameter.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoBurstParameter.h 3     17.03.09 15:16 Merz $
//
// $Modtime: 6.03.09 13:08 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAInfoBurstParameter.h $
// * 
// * 3     17.03.09 15:16 Merz
// * changes for burst parameters
// * 
// * 2     26.01.09 13:10 Merz
// * check in for HL
// * 
// * 1     19.11.08 16:28 Merz
// * intial check in
// * 
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the Burst parameter info object
 */


#pragma once

#include "MCStreamProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAInfoBurstParameter command target

//! Info about the data created from the Burst parameter instrument
class CMCSAInfoBurstParameter
{
public:
	CMCSAInfoBurstParameter();

// Attributes
public:
	CMBurstAnalyzerProperty m_BurstAnalyzerProperty;

// Operations
public:


// Implementation
protected:
public:
	virtual ~CMCSAInfoBurstParameter();

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

