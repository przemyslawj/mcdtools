/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAEvtSpike.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAEvtSpike.h 11    11.05.10 15:13 Paetzold $
//
// $Modtime: 11.05.10 10:59 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAEvtSpike.h $
// * 
// * 11    11.05.10 15:13 Paetzold
// * After merge from DownSampling
// * 
// * 2     10.05.10 10:00 Loeffler
// * make PreTick int instead of WORD
// * 
// * 1     16.04.10 14:58 Merz
// * 
// * 1     16.04.10 14:52 Merz
// * 
// * 10    14.11.08 11:35 Loeffler
// * HWID added
// * 
// * 9     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 8     14.01.07 23:10 Paetzold
// * 
// * 7     15.12.06 15:50 Loeffler
// * docu changes
// * 
// * 6     14.12.06 14:17 Loeffler
// * docu changes
// * 
// * 5     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 4     10.02.03 10:16 Patzwahl
// * introduced wUnitID, and compartibility code
// * 
// * 3     5-06-02 17:18 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the spike event object
 */

#ifndef _MCSAEVTSPIKE_H_
#define _MCSAEVTSPIKE_H_

#include "MCSAEvent.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAEvtSpike command target

//! Retrieve a spike 
/*! A spike Event consists of a channel ID, a unit ID, the spike signal, and
		a time stamp.
		
\code

void CTestDLLDoc::ReadSpikes()
{
// DP 01/2003
// this method describes the principle of reading spike data
// from an MC_Rack data file. In a real import method the code
// has to be optimized for speed!!

  // determine values for conversion of AD-values to voltages
  int iADBits = m_MCSStream.GetADBits();
  int iADZero = m_MCSStream.GetADZero();
  char cUnitSign = static_cast<char>(m_MCSStream.GetUnitSign());
  float fUnitsPerAD = static_cast<float>(m_MCSStream.GetUnitsPerAD());

	IMCSEvtSpike EventSpike; 
  EventSpike.AttachDispatch(m_MCSStream.GetFirstEvent());
  int iContinue = 1;
      
  // loop over all events
  while (iContinue == 1)
	{
		int iChannel = EventSpike.GetChannel();
		CString csChannelName = m_MCSStream.GetChannelName(iChannel);
		int iUnitID = EventSpike.GetUnitID(); //if 0 spike is not classified

    int iSeconds = EventSpike.GetSecondFromStart();
    int iMilliS = EventSpike.GetMillisecondFromStart();
    int iMicroS = EventSpike.GetMicrosecondFromStart();
    int iNanoS = EventSpike.GetNanosecondFromStart();

		float fSpikeTimeStamp = iSeconds +
														static_cast<float>(iMilliS) / 1000 +
														static_cast<float>(iMicroS) / 1000000 +
														static_cast<float>(iNanoS) / 1000000000;


  	int iPreTick = EventSpike.GetPreEvent();
		int iSpikeDataArraySize = EventSpike.GetCount();
		short* SpikeDataBuffer = new short[iSpikeDataArraySize];
		EventSpike.GetADDataArray(SpikeDataBuffer);

    // compute voltage from iADData
		float* Spike = new float[iSpikeDataArraySize];
		for(int i = 0; i < iSpikeDataArraySize; ++i)
		{
			*(Spike + i) = (*(SpikeDataBuffer + i) - iADZero) * fUnitsPerAD;
		}
    delete [] Spike;
		                              
    // move to next event
		delete [] SpikeDataBuffer;
    iContinue = EventSpike.Next();
  }
  EventSpike.ReleaseDispatch();
}
\endcode
*/
class CMCSAEvtSpike : public CMCSAEvent
{

public:
	CMCSAEvtSpike();           

//! Get spike sample count
/*! The number of samples of the whole spike cut out.
 * \return number of data samples (2 bytes) of the spike
*/
	long GetCount();

//! Get sample count of pre trigger interval
/*! The spike cut out is composed of a pre and post trigger interval.
 * \return number of data samples (2 bytes) of the pre trigger interval
*/
	long GetPreEvent();

//! Get channel ID
/*! Each spike is marked with a channel ID. To retrieve more information
		you may access the <a class="qindex" href="classIMCSInfoSpike.html">IMCSInfoSpike</a> 
		class using the channel hardware ID (ChHWID). 
		The folloing code shows the mapping of the channel ID to chHWID
		(currently MAX_CHANNELS is 128).
\code

for(int iChID = 0; iChID < MAX_CHANNELS; ++iChID)
{
	for(long i = 0; i < m_MCSStream.GetChannelCount(); ++i)
	{
		IMCSChannel Channel;
		Channel.AttachDispatch(m_MCSStream.GetChannel(i));
		if(iChID == Channel.GetId())
		{
			CString csChannelName = Channel.GetName();
			long lChHWID = Channel.GetHwid();
		}
		Channel.ReleaseDispatch();
	}
}
\endcode

 * \return channel ID
*/	
	short GetChannel();


//! Get spike unit ID
/*! If spikes were sorted using MC_Rack (see GetDetectMethod() of
		<a class="qindex" href="classCMCSAInfoSpike.html">CMCSAInfoSpike</a>), 
		each spike is labeled with a unit ID. If a spike was not classified
		the UnitID is 0. If spikes were not sorted, all spikes are labeld 0.
 * \return	<ul>
						<li> 0 if spike was not classified / or not sorted </li>
						<li> UnitID > 0, spike was classified,and is member of spike unit with the ID.</li>
						</ul>
*/
	short GetUnitID();

	short GetHWID();

//! Get spike data
/*! Transferes the spike data (AD values) to a buffer (*bud). Make sure that the buffer 
		has the correct size. You may convert the AD values to voltage (see code fragments below).
\code

// determine values for conversion of AD-values to voltages
int iADZero = m_MCSStream.GetADZero();
float fUnitsPerAD = static_cast<float>(m_MCSStream.GetUnitsPerAD());

// Get spike data 
int iSpikeDataArraySize = EventSpike.GetCount();
short* SpikeDataBuffer = new short[iSpikeDataArraySize];
EventSpike.GetADDataArray(SpikeDataBuffer);

// compute voltage from iADData
float* Spike = new float[iSpikeDataArraySize];
for(int i = 0; i < iSpikeDataArraySize; ++i)
{
	*(Spike + i) = (*(SpikeDataBuffer + i) - iADZero) * fUnitsPerAD;
}

\endcode
 * \return TRUE if successful.
*/
	BOOL GetADDataArray(short * buf);

//! Get single data point
/*! Get single data point (AD value) at index iIndex of the spike data.
\param iIndex index into the spike data array (starts with zero)
\return AD value at index
*/
	short GetADData(int iIndex);

	virtual bool Read();
	virtual bool ReadNext();
	virtual long GetSize();
	CMCSAEvtSpike& operator=(const CMCSAEvtSpike& evt);

public:
	virtual ~CMCSAEvtSpike();

private:
	void SetMemberPointers();
	void CalcOffsetNext();

	DWORDLONG*  m_pqwTick;
	WORD*		m_pwChannel;
	int*		m_piSize;
	int*		m_pPreTick;
	WORD*		m_pwUnitID;
	WORD		m_wUnitID;
	short* m_pHWID;
	short m_HWID;
	WORD*		m_pwData;
};

/////////////////////////////////////////////////////////////////////////////
#endif
