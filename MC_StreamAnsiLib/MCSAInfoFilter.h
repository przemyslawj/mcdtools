/////////////////////////////////////////////////////////////////////////////
//
// MC_Rack
// Copyright (C) 1998-2010 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoFilter.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoFilter.h 6     11.05.10 15:13 Paetzold $
//
// $Modtime: 11.05.10 10:59 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAInfoFilter.h $
// * 
// * 6     11.05.10 15:13 Paetzold
// * After merge from DownSampling
// * 
// * 2     28.04.10 10:26 Loeffler
// * some missing functions added
// * 
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSAINFOFILTER_H_
#define _MCSAINFOFILTER_H_
#include "MCStreamProperty.h"

#include <string>

class CMCSAInfoFilter
{
public:
	CMCSAInfoFilter();           // protected constructor used by dynamic creation

	CMFilterProperty m_FilterProperty;

	//! get name of filter
	std::string GetFilterName() const;

	//! get center frequency in Hz of bandstop resonator
	double GetCenterFrequency() const;
	
	//! get Q factor of bandstop resonator
	double GetQFactor() const;
	
	//! returns true if downsampling was checked
	/*! this is only possible if the filter type is low pass
	 */
	bool IsDownsamplingEnabled() const;

	//! get downsampling frequency
	int GetDownsamplingFrequency() const;

	//! get cutoff frequency in Hz of either low or high pass
	int GetCutoff() const;

	//! get cutoff frequency in Hz of either low or high pass
	int GetLowerCutoff() const;

	//! not used as of V 4.0
	int GetUpperCutoff() const;

	//! returns name of the filter pass type (low pass, high pass, band stop etc.)
	std::string GetPassTypeAsString() const;

	/*!
	 * 0: Undefined
	 * 1: Low pass
	 * 2: High pass
	 */
	int GetPassType() const;

	/*! These are the indices of EnFilterTypes
	 * 0: Bessel 2nd order
	 * 1: Bessel 4th order
	 * 2: Butterworth 2nd order
	 * 3: Chebyshev 2nd order 0.5 dB
	 * 4: Chebyshev 2nd order 1.0 dB
	 * 5: Chebyshev 2nd order 2.0 dB
	 * 6: Chebyshev 2nd order 3.0 dB
	 * 7: Bandstop Resonator
	 * 8: Savitzky-Golay
	 */
	int GetFilterType() const;

	//! Get filter name string, input a filter type from GetFilterType()
	string GetFilterName(int FilterType) const;

	// info for Savitzky-Golay filter
	//! get order of Savitzky-Golay filter
	int GetSGOrder() const;

	//! get total number of averaging samples of the Savitzky-Golay filter
	int GetSGNumSamples() const;

	//! get number of averaging samples to the left side of the Savitzky-Golay filter
	int GetSGNumDataPointsLeft() const;

	//! returns true if filter is a Savitzky-Golay filter
	bool IsSavitzkyGolayFilter() const;

	//! returns true if filter is a IIR filter
	/*! as of V 4.0 these are all filters except the Savitzky-Golay filter
	 */
	bool IsIIRFilter() const;
};

#endif
