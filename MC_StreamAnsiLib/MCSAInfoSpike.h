/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAInfoSpike.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAInfoSpike.h 10    14.05.10 12:35 Loeffler $
//
// $Modtime: 14.05.10 9:40 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAInfoSpike.h $
// * 
// * 10    14.05.10 12:35 Loeffler
// * docu: functions deprecated
// * 
// * 9     11.05.10 15:13 Paetzold
// * After merge from DownSampling
// * 
// * 2     28.04.10 10:25 Loeffler
// * functions returning values in us added
// * 
// * 1     16.04.10 14:58 Merz
// * 
// * 1     16.04.10 14:52 Merz
// * 
// * 8     15.12.06 15:50 Loeffler
// * docu changes
// * 
// * 7     14.12.06 15:51 Jesinger
// * removed paths from #include statements
// * 
// * 6     14.12.06 14:17 Loeffler
// * docu changes
// * 
// * 5     15.08.06 11:22 Jesinger
// * changed include name "MCStream..." -> "MC_Stream..."
// * 
// * 4     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 3     10.02.03 10:13 Patzwahl
// * new info interface
// * 
// * 2     6-06-02 10:47 Patzwahl
// * added GetInputBufferID()
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the spike info object
 */

#ifndef _MCSAINFOSPIKE_H_
#define _MCSAINFOSPIKE_H_

#include <vector>
#include "MCStreamProperty.h"

using namespace std;

//! Retrieve Spike infos
/*! The SpikeInfo class provides information about a spike data stream.
 *	Information is organized in three levels:
 *	<ol>
 *	<li>general information
 *	<li>channel specific information
 *	<li>spike unit specific information
 *	</ol>
 *
 * Example:
 * \code

void CTestDLLDoc::ReadSpikeInfo()
{
// DP 01/2003
// this method describes the principle of reading spike info
// from an MC_Rack data file. In a real import method the code
// has to be optimized!!

	IMCSInfoSpike InfoSpike;

	InfoSpike.AttachDispatch(m_MCSStream.GetInfo());
	
	short iDetectMethod = InfoSpike.GetDetectMethod();
	short iSortMethod = InfoSpike.GetSortMethod();
	float fPreTrigger = InfoSpike.GetPreTrigger();
	float fPostTrigger = InfoSpike.GetPostTrigger();
	float fDeadTime = InfoSpike.GetDeadTime();

	for(long i = 0; i < m_MCSStream.GetChannelCount(); ++i)
	{
		IMCSChannel Channel;
		Channel.AttachDispatch(m_MCSStream.GetChannel(i));
		short iChHWID = Channel.GetHwid();
		short iChBufferIndex = Channel.GetId();
		Channel.ReleaseDispatch();

		short iChannelGroupID = InfoSpike.GetChannelGroupID(iChHWID);
		float fThresholdLevel = InfoSpike.GetThresholdLevel(iChHWID);
		short iThresholdSlope = InfoSpike.GetThresholdSlope(iChHWID);
		float fSlopeDeltaV = InfoSpike.GetSlopeDeltaV(iChHWID);
		float fSlopeMin = InfoSpike.GetSlopeMin(iChHWID);
		float fSlopeMax = InfoSpike.GetSlopeMax(iChHWID);

		short iUnitCount = InfoSpike.GetSpikeUnitCount();
		for( short j = 0; j < iUnitCount; ++j)
		{
			short iUnitID = InfoSpike.GetSpikeUnitID(j);
			float fSpikeUnitWndTime = InfoSpike.GetSpikeUnitWndTime(iChHWID, iUnitID);
			float fSpikeUnitWndMin = InfoSpike.GetSpikeUnitWndMin(iChHWID, iUnitID);
			float fSpikeUnitWndMax = InfoSpike.GetSpikeUnitWndMax(iChHWID, iUnitID);
		}
	}
	InfoSpike.ReleaseDispatch();
}

 * \endcode
 */

class CMCSAInfoSpike
{
public:
	CMCSAInfoSpike();
	virtual ~CMCSAInfoSpike();
	bool ReadSpikeFormatInfo(char** pInfo, WORD wHdrVersion);


	//! Get input buffer ID
	/*! Get buffer ID of the raw data buffer which is the input data stream of the spike sorter instrument.
	 * \return string of 8 characters, for example elec0001, filt0002.
	*/
	char* GetInputBufferID();

	//! Get spike detection method
	/*! Currently two spike detection methods are possible: threshold detection, and slope detection.
			Threshold detection is represented by 0, slope detection is represented by 1.
			\return <ul> 
							<li> 0 = threshold detection 
							<li> 1 = slope detection 
							</ul>
	*/
	short	GetDetectMethod();

	//! Get spike sorting method
	/*! Currently only a window based sorting method is possible.
			If the spike are not classified GetSortmethod returns 0, 
			if the spikes are sorted based on a window GetSortmethod returns 1.
			\return <ul>
							<li> 0 = spikes not classified
							<li> 1 = window based sorting
							</ul>
	*/
	short GetSortMethod();

	//! Get spike pre trigger interval
	/*! 
		\deprecated this function should not be used any more, use GetPreTrigger_us() instead
		\return pre trigger interval in seconds
	*/
	float GetPreTrigger();

	//! Get spike pre trigger interval
	/*! 
		\return pre trigger interval in micro seconds
	*/
	int GetPreTrigger_us();

	//! Get spike post trigger interval
	/*! 
			\deprecated this function should not be used any more, use GetPostTrigger_us() instead
			\return post trigger interval in seconds
	*/
	float GetPostTrigger();

	//! Get spike post trigger interval
	/*! 
			\return post trigger interval in micro seconds
	*/
	int GetPostTrigger_us();

	//! Get dead time
	/*! The dead time defines the time interval after a detected spike, in which 
		no spike detection is performed.
		\deprecated this function should not be used any more, use GetDeadTime_us() instead
		\return dead time in seconds
	*/
	float GetDeadTime();

	//! Get dead time
	/*! The dead time defines the time interval after a detected spike, in which 
		no spike detection is performed.
		\return dead time in micro seconds
	*/
	int GetDeadTime_us();


//! Get channel group ID
/*! Channels could be arranged in groups (stereotodes, tetrodes, ...).
		Each grouped channel has an ID > 0; if a channel is not a member of
		a group GetChannelGroupID returns zero.
		\param iChHWID channel hardware ID
		\return group ID mif not zero
*/
	short GetChannelGroupID(short iChHWID);


//! Get threshold level
/*! Get threshold level in volts used for the channel with iChHWID. The returned value is
		valid only if spike detection was based on the threshold method, i.e. if GetDetectMethod == 0.
		\param iChHWID channel hardware ID
		\return threshold in volts
*/
	float GetThresholdLevel(short iChHWID);

//! Get slope for threshold detection
/*! Get slope used for the channel with iChHWID. A spike is detected only if the signal crosses the
		threshold with the correct slope. Positive slope: signal gets more positive; negative slope: 
		signal gets more negative. The returned value is valid only if spike detection was based on 
		the threshold method, i.e. if GetDetectMethod == 0.
		\param iChHWID channel hardware ID
		\return <ul> 
						<li> if slope == 0: positive slope </li>
						<li> if slope == 1: negative slope </li>
						</ul>
*/
	short GetThresholdSlope(short iChHWID);

//! Get voltage difference of slope detection method
/*! The slope detection methode is based on a range of signal slopes, given by the minimum 
		and maximum slope, combined with a minimum voltage difference. If the voltage difference
		is negative the signal has to get more negative, if the voltage difference is positive the
		signal has to get more positive.
		\param iChHWID channel hardware ID
		\return voltage difference in volts
*/
	float GetSlopeDeltaV(short iChHWID);

//! Get minimum slope of slope detection method
/*! The slope detection methode is based on a range of signal slopes, given by the minimum 
		and maximum slope, combined with a minimum voltage difference. 
		\param iChHWID channel hardware ID
		\return minimum slope in volts/seconds (or µV/µs)
*/
	float GetSlopeMin(short iChHWID);

//! Get maximum slope of slope detection method
/*! The slope detection methode is based on a range of signal slopes, given by the minimum 
		and maximum slope, combined with a minimum voltage difference. 
		\param iChHWID channel hardware ID
		\return maximum slope in volts/seconds (or µV/µs)
*/
	float GetSlopeMax(short iChHWID);


//! Get spike unit count
/*! Get the number of spike units defined for spike sorting.
		\return number of spike units
*/
	short GetSpikeUnitCount();

	
//! Get spike unit ID
/*! Get the number of spike units defined for spike sorting.
		\return number of spike units
*/
	short GetSpikeUnitID(short iIndex);

//! Get time point of the sorting window
/*! The sorting time window is defined by a time point (relative to the first data point 
		of the spike cut out), and a minimum and maximum voltage.
		\param iChHWID channel hardware ID
		\param iUnitID spike unit ID assocciated with the spike sorting window
		\return time point of the sort window in seconds
*/	
	float GetSpikeUnitWndTime(short iChHWID, short iUnitID);

//! Get minimum voltage of the sorting window
/*! The sorting time window is defined by a time point (relative to the first data point 
		of the spike cut out), and a minimum and maximum voltage.
		\param iChHWID channel hardware ID
		\param iUnitID spike unit ID assocciated with the spike sorting window
		\return minimum voltage in volts
*/	
	float GetSpikeUnitWndMin(short iChHWID, short iUnitID);

//! Get maximum voltage of the sorting window
/*! The sorting time window is defined by a time point (relative to the first data point 
		of the spike cut out), and a minimum and maximum voltage.
		\param iChHWID channel hardware ID
		\param iUnitID spike unit ID assocciated with the spike sorting window
		\return maximum voltage in volts
*/	
	float GetSpikeUnitWndMax(short iChHWID, short iUnitID);

private:
	CMSpikeProperty m_SpikeProperty;
	std::vector<WORD> m_arrUnitIDs;
};

/////////////////////////////////////////////////////////////////////////////
#endif
