/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAStream.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAStream.h 18    20.05.10 14:20 Loeffler $
//
// $Modtime: 20.05.10 13:45 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAStream.h $
// * 
// * 18    20.05.10 14:20 Loeffler
// * - some functions made const
// * - GetRelativeChannelPosX added 
// * 
// * 17    11.05.10 15:13 Paetzold
// * After merge from DownSampling
// * 
// * 2     28.04.10 10:25 Loeffler
// * - GetSampleRate() added
// * - fix GetRawDataBufferSize for downsampled data
// * 
// * 1     16.04.10 14:58 Merz
// * 
// * 1     16.04.10 14:52 Merz
// * 
// * 16    22.01.09 14:44 Merz
// * changes for the burst stream
// * 
// * 15    1.12.08 11:07 Paetzold
// * Included checks for the actual buffer size and the calculated buffer
// * size
// * 
// * 14    14.11.08 9:58 Paetzold
// * Bug fix in view of triggered streams
// * 
// * 13    25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 12    14.01.07 23:11 Paetzold
// * 
// * 11    15.12.06 15:50 Loeffler
// * docu changes
// * 
// * 10    14.12.06 14:17 Loeffler
// * docu changes
// * 
// * 9     25.04.06 16:29 Paetzold
// * Merging of files
// * 
// * 8     23.04.06 22:44 Paetzold
// * Update for Merge
// * 
// * 7     7.02.06 8:42 Loeffler
// * new function for neuroshare
// * 
// * 6     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 5     26.09.02 10:10 Patzwahl
// * * DP: MCSAStream: changed the parameters of MoveToChunk, GetRawData,
// * GetRawDataBufferSize to	CMCSATimeStamp, to prevent rounding errors when
// * accessing data with an accuracy below 1 ms.	Fixed a bug in GetRawData
// * when accessing data beginning and ending in a singel chunk.
// * 
// * 4     6-06-02 10:43 Patzwahl
// * Reading MCS data files faster: 
// * GetRawData(...) and GetRawDataOfChannel(...) are Chunk based (and not
// * event). The necessary buffer size to hold the data has to be determined
// * before reading the data using GetRawDataBufferSize(...) and
// * GetRawDataBufferSizeOfChannel. Added HasContinuousData(), HasRawData(),
// * and MoveToChunk(...).
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the MCStream object
 */

#ifndef _MCSAStream_H_
#define _MCSAStream_H_

#include "MCSAStreamFile.h"

/////////////////////////////////////////////////////////////////////////////
// CMCSAStream

struct STRMHDR;
struct STRMFMT;
struct MCSHDR;
class CMCSAChannel;
class CMCSAEvent;
class CMIndex1;
class CMCSATimeStamp;
class CMCSAChunk;
class CMCSStreamFile;



//! Retrieve MC_Rack data stream
/*! A stream represents all data belonging to a source, for example the
MC_Card, which provides raw data streams, or the spike sorter, which provides a
spike stream. Each stream consists of 1 to serveral channels (maximum is 128 channels).
Streams are managed by the MCStreamFile object. Please consult the code in the example project
MC_StreamTest to
learn how to create a stream object, access its channel and select a stream type for
the extraction of data.
*/
class CMCSAStream
{
public:
    //! Stream constructor
    /*!
     *you usually don't need to call this directly. Use CMCSAStreamFile::GetStream()
     */
	CMCSAStream(CMCSAStreamFile* pStreamFile);
	CMCSAStream* Clone(CMCSAStreamFile* pStreamFile);
	virtual ~CMCSAStream();

//! Get the ID of the stream
/*! The ID of the stream consists of four characters (short cut of the stream name)
and a four character number (0001, 0002, ...). <br>
The following names are defined (as of MCStream.dll V 3.2):
<table>
<tr>
<td>elec</td> <td>Electrode raw data</td>
</tr>
<tr>
<td>anlg</td> <td>Analog raw data</td>
</tr>
<tr>
<td>digi</td> <td>Digital raw data</td>
</tr>
<tr>
<td>spks</td> <td>Spikes</td>
</tr>
<tr>
<td>filt</td> <td>Filtered data</td>
</tr>
<tr>
<td>trig</td> <td>Triggered data (sweeps)</td>
</tr>
<tr>
<td>para</td> <td>Analyzer data (Parameters)</td>
</tr>
<tr>
<td>mean</td> <td>Averager data</td>
</tr>
<tr>
<td>sppa</td> <td>Spike analyzer data</td>
</tr>
</table>
This identifier is unique for a given mcd file
*/
	char* GetBufferID();

//! Get stream channel count
/*!
\return channel count
*/
	virtual long GetChannelCount() const;

//! Get stream header version
/*!
\return Header versione of the stream header
*/
	virtual long GetHeaderVersion();

//! Get data type
/*! 
\return zero terminated string with maximum of 8 characters:
<ul>
<li> params </li>
<li> average </li>
<li> trigger </li>
<li> filter </li>
<li> spikes </li>
<li> analog </li>
<li> digital </li>
<li> spkparam </li>
<li> bstparam </li>
</ul>
*/
	virtual char* GetDataType();

//! Get data stream name
/*! Get stream name, for example "Electrode Raw Data" or "Digital Raw Data".
\return zero terminated string (max. size 256 characters)
*/
	virtual char* GetName();

//! Method is deprecated
/*!
*/
	virtual char* GetComment();

//! Method is deprecated
/*!
*/
	virtual short GetID();

//! Get milli samples per second
/*! Devide the retrun value by 1000 to convert it to the common sample rate.
\return sample of the stream data (mulitplied by 1000)
*/
	virtual long GetMilliSamplesPerSecond() const;

//! Get sample rate in Hz
/*! returns 0 in case of error */
	virtual long GetSampleRate() const;

//! Get format version
/*! The format version is used for backward compartibility.
\return format version
*/
	virtual short GetFormatVersion();

//! Get unit sign
/*! Get the unit sign of the stream data. The return value of the
GetUnitSign() has to be casted to char (see demo code below).
\code
char cUnitSign = static_cast<char>(m_MCSStream.GetUnitSign());
\endcode
\return char, for example 'V' for volt
*/
	virtual short GetUnitSign();

//! Get number of AD bits
/*! Get number of bits of the analog digital (AD) converter. For MC_Card it is either 12 or 16
\return number of AD bits
*/
	virtual short GetADBits();

//! Get the AD zero value
/*! Get the AD value representing 0. For 12 bits the AD range
is 0 .. 4095, AD zero is 2048. For 16 bits the range is 0 .. 65535, AD zero is 32768
\return AD zero value
*/
	virtual WORD GetADZero();

//! Get units per AD step
/*! Get the unit value for a AD value step. Depending on the number
of AD bits, the input voltage range, and the amplifier gain GetUnitsPerAD()
returns the units per step. For example 0.833µV per step, when the
range was set to -4086mV to 4085mV, and the gain was 1200 (typical for a
MEA amplifier).
\return units per AD step
*/
	virtual double GetUnitsPerAD();

//! Method is deprecated
/*!
*/
	virtual short GetBytesPerChannel();

//! Get the number of samples of a data segment
/*! This method is only important for MC_Rack
\return number of samples per data segment
*/
	virtual short GetDefaultSamplesPerSegment();

//! Get the number of data segments
/*! This method is only important for MC_Rack
\return number of data segments
*/
	virtual short GetDefaultSegmentCount();

//! Get the channel object
/*! Eeach data stream consists of 1 to many channels.
Using GetChannelCount(), and GetChannel(), channel specific information
can be obtained (see example code below).
\code

for(long i = 0; i < m_MCSStream.GetChannelCount(); ++i)
{
	IMCSChannel Channel;
	Channel.AttachDispatch(m_MCSStream.GetChannel(i));
	CString csChName = Channel.GetName();
	short iChHWID = Channel.GetHwid();
	short iChBufferIndex = Channel.GetId();
	short iChGroupID = Channel.GetGroupID();
	Channel.ReleaseDispatch();
}
\endcode
*/
	virtual CMCSAChannel* GetChannel(short Index);

	virtual CMCSAChannel* GetChannelHWID(short Index);
//! Get name of the channel
/*!
\return Name of the channel
*/
	virtual char* GetChannelName(short Index);
	
//! Get Info object of the stream
/*! Most streams have a info object, which provides information
about the data stream. See example below how to access the info object.
\code

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
\endcode
\return stream info object
*/
	virtual void* GetInfo();

//!	Has data stream continuous data
/*!
\return
	 <ul>
	 <li> true if data is continuous </li>
	 <li> false if the data is triggered </li>
	 </ul>
*/
	virtual bool HasContinuousData();

//!	Has data stream raw data
/*! MC_Rack raw data pools the data types 'analog', 'filter', and 'digital'.
\return
	 <ul>
	 <li> true if stream contain raw data ('analog', 'filter', and 'digital') </li>
	 <li> false if stream contain other data </li>
	 </ul>
*/
	virtual bool HasRawData();

//! Get raw data
/*! GetRawData(short* pData, long lFrom, long lTo) swiftly reads raw data streams
This method is for continuous raw data (type = analog, electrode, digital, filtered)
For triggered raw data use the GetSweep... methods, for all other data
use the event based reading routines.
\code

void CTestDLLDoc::ReadRawData(__int64 i64From, __int64 i64To) // in µs
{
// DP 02/2003
// this method describes the principle of reading raw data
// from an MC_Rack data file. In a real import method the code
// has to be optimized for speed!!

	if(m_MCSStream.HasRawData() && m_MCSStream.HasContinuousData())
	{
		// set time stamps
		long lFromSec=(long)(i64From / 1000000);
		short sFromMSec=(short)((i64From - (DWORDLONG)lFromSec * 1000000) / 1000);
		short sFromUSec=(short)((i64From - (DWORDLONG)lFromSec * 1000000 - (DWORDLONG)sFromMSec * 1000));
		short sFromNSec = 0;

		long lToSec=(long)(i64To / 1000000);
		short sToMSec=(short)((i64To - (DWORDLONG)lToSec * 1000000) / 1000);
		short sToUSec=(short)((i64To - (DWORDLONG)lToSec * 1000000 - (DWORDLONG)sToMSec * 1000));
		short sToNSec = 0;

		IMCSTimeStamp tsFrom,tsTo;
		tsTo.AttachDispatch(m_MCSFile.GetStartTime());
		tsFrom.AttachDispatch(tsTo.Clone());
		tsFrom.SetSecondFromStart(lFromSec);
		tsFrom.SetMillisecondFromStart(sFromMSec);
		tsFrom.SetMicrosecondFromStart(sFromUSec);
		tsFrom.SetNanosecondFromStart(sFromNSec);
		tsTo.ReleaseDispatch();
		tsTo.AttachDispatch(tsFrom.Clone());
		tsTo.SetSecondFromStart(lToSec);
		tsTo.SetMillisecondFromStart(sToMSec);
		tsTo.SetMicrosecondFromStart(sToUSec);
		tsTo.SetNanosecondFromStart(sToNSec);

		long lBufferSize = m_MCSStream.GetRawDataBufferSize(tsFrom, tsTo);
		short* pBuffer = new short[lBufferSize];
		
		if(lBufferSize != m_MCSStream.GetRawData(pBuffer, tsFrom, tsTo))
		{
			ASSERT(0);
		}
		delete [] pBuffer;
	}
}

\endcode
\param pData pointer to data array of shorts (size must be determined before calling GetData.
\param tsFrom: TimeStamp start reading in ns relative to start recording.
\param tsTo: TimeStamp end reading in ns relative to start recording.
\return number of Data values read from the file, 0 if data is not a raw data stream
*/
	virtual long GetRawData(short* pData, long DataSize, CMCSATimeStamp* tsFrom, CMCSATimeStamp* tsTo);

//! Get raw data of a single channel
/*! GetRawDataOfChannel(short* pData, long lIndex) swiftly reads raw data of channel lIndex
This method is for continuous raw data (type = analog, electrode, digital, filtered)
For triggered raw data use the GetSweep... methods, for all other data
use the event based reading routines.
\param pData pointer to data array of shorts (size must be determined before calling GetData.
\param lIndex: index to channel (starts with zero!)
\return number of Data values read from the file, 0 if data is not a raw data stream (analog, electrode, digital, filtered) or triggered
*/
	virtual long GetRawDataOfChannel(short* pData, long lIndex);

//! Get raw data of a single channel
/*! GetRawDataOfChannelStartCount(short* pData, long lIndex, long lStart, long lCount) swiftly 
reads raw data of channel lIndex, starting at lStart sample lCount values. This method is for continuous raw 
data (type = analog, electrode, digital, filtered)
For triggered raw data use the GetSweep... methods, for all other data
use the event based reading routines.
\param pData pointer to data array of shorts (size must be determined and memory provided before calling GetData).
\param lIndex: index to channel (starts with zero!)
\param lStart index of sample to start from
\param lCount number of samples to get
\return number of Data values read from the file, 0 if data is not a raw data stream (analog, electrode, digital, filtered) or triggered
*/
	virtual long GetRawDataOfChannelStartCount(short* pData, long lIndex, long lStart, long lCount);

//! Get buffer size
/*! GetRawDataBufferSize(long lFrom, long lTo) called to determine the required buffer size
This method is for continuous raw data (type = analog, electrode, digital, filtered).
For triggered raw data use the GetSweep... methods, for all other data
use the event based reading routines.
\param tsFrom: start reading in ns relative to start recording.
\param tsTo: end reading in ns relative to start recording.
\return size of buffer (shorts). Retuns 0 if the stream has no raw data or is triggered.
*/
	virtual long GetRawDataBufferSize(CMCSATimeStamp* tsFrom, CMCSATimeStamp* tsTo);

//! Get buffer size needed for a single channel
/*! GetRawDataBufferSizeOfChannel() called to determine for a single channel the required buffer size
This method is for continuous raw data (type = analog, electrode, digital, filtered).
For triggered raw data use the GetSweep... methods, for all other data
use the event based reading routines.
\return size of buffer (shorts). Retuns 0 if the stream has no raw data or is triggered.
*/
	virtual long GetRawDataBufferSizeOfChannel();


//! Get buffer size neede for a sweep
/*! GetSweepRawDataBufferSize() called to determine the required buffer size for a single sweep of triggered data
This method is for triggered raw data (type = analog, electrode, digital, filtered)
For continuous raw data use the GetData... methods, for all other data
use the event based reading routines.
\return size of buffer (shorts). Retuns 0 if the stream has no raw data or is continuous.
*/
	virtual long GetSweepRawDataBufferSize(long lSweepIndex);

//! Get sweep data
/*! This method is for triggered raw data (type = analog, electrode, digital, filtered)
For continuous raw data use the GetData... methods, for all other data
use the event based reading routines.
\param pData pointer to data array of shorts (size must be determined beforehand).
\param lSweepIndex defines which sweep is accessed
\return true if the next triggered data block was read; false if not.
*/
	virtual long GetSweepRawData(short* pData, long DataSize, long lSweepIndex);
	virtual long GetSweepRawData(short* pData, long DataSize, long lSweepIndex,long lStart,long lCount);
//! Get sweep data of a single channel
/*! This method is for triggered raw data (type = analog, electrode, digital, filtered)
For continuous raw data use the GetData... methods, for all other data
use the event based reading routines.
\param pData pointer to data array of shorts (size must be determined beforehand).
\param lSweepIndex defines which sweep is accessed
\param lIndex channel index
\return true if the next triggered data block was read; false if not.
*/
	virtual long GetSweepRawDataOfChannel(short* pData, long sweepsize, long lSweepIndex, long lIndex);
	virtual long GetSweepRawDataOfChannel(short* pData, long sweepsize, long lSweepIndex, long lIndex,long lStart,long lCount);

//! Get first data chunk
/*! Get the first data chunk of the current stream. See the example code below
how to read in the data chunks of a stream. 
\code

void CTestDLLDoc::ReadRawDataChunks()
{
// DP 02/2003
// this method describes the principle of reading raw data chunks
// from an MC_Rack data file by reading the file chunks (segments
// of maximal 100ms data). In a real import method the code
// has to be optimized for speed!!

	int iStreamHdrVersion = m_MCSStream.GetHeaderVersion();

  // determine values for conversion of AD-values to voltages
  int iADBits = m_MCSStream.GetADBits();
  int iADZero = m_MCSStream.GetADZero();
  char cUnitSign = static_cast<char>(m_MCSStream.GetUnitSign());
  float fUnitsPerAD = static_cast<float>(m_MCSStream.GetUnitsPerAD());

	long lChannelCount = m_MCSStream.GetChannelCount();
	for(int i = 0; i < lChannelCount; ++i)
	{
		CString csChannelName = m_MCSStream.GetChannelName(i);
	}

	LPDISPATCH lpdChunk;

	IMCSChunk* pChunk = new IMCSChunk;
	lpdChunk = m_MCSStream.GetFirstChunk();

	if(lpdChunk)
	{
		pChunk->AttachDispatch(lpdChunk);
	}
	
	while(lpdChunk)
	{
		IMCSTimeStamp ChunkFrom;
		LPDISPATCH lpd = pChunk->GetTimeStampFrom();
		ChunkFrom.AttachDispatch(lpd);
		int iSeconds = ChunkFrom.GetSecondFromStart();
		int iMilliS = ChunkFrom.GetMillisecondFromStart();
		int iMicroS = ChunkFrom.GetMicrosecondFromStart();
		int iNanoS = ChunkFrom.GetNanosecondFromStart();
		ChunkFrom.ReleaseDispatch();

		float fChunkFrom = iSeconds +
														static_cast<float>(iMilliS) / 1000 +
														static_cast<float>(iMicroS) / 1000000 +
														static_cast<float>(iNanoS) / 1000000000;

		IMCSTimeStamp ChunkTo;
		lpd = pChunk->GetTimeStampTo();
		ChunkTo.AttachDispatch(lpd);
		iSeconds = ChunkTo.GetSecondFromStart();
		iMilliS = ChunkTo.GetMillisecondFromStart();
		iMicroS = ChunkTo.GetMicrosecondFromStart();
		iNanoS = ChunkTo.GetNanosecondFromStart();
		ChunkTo.ReleaseDispatch();

		float fChunkTo = iSeconds +
														static_cast<float>(iMilliS) / 1000 +
														static_cast<float>(iMicroS) / 1000000 +
														static_cast<float>(iNanoS) / 1000000000;

		long lBufferSize = pChunk->GetSize();
		short* pBuffer = new short[lBufferSize];
		if(lBufferSize != pChunk->ReadData(pBuffer))
		{
			ASSERT(0);
		}

		float* pMicroVolts = new float[lBufferSize];

		for(i = 0; i < lBufferSize; ++i)
		{
			*(pMicroVolts + i) = (*(pBuffer + i) - iADZero) * fUnitsPerAD;
		}
		
		delete pBuffer;
		delete pMicroVolts;
		lpdChunk = m_MCSStream.GetNextChunk(lpdChunk);
	}

	pChunk->ReleaseDispatch();
	delete pChunk;
}
\endcode
\return pointer to a chunk object
*/
	virtual CMCSAChunk* GetFirstChunk();

//! Get next chunk object
/*! See example code for the GetFistChunk() method.
\return pointer to the next chunk object
*/
	virtual CMCSAChunk* GetNextChunk(CMCSAChunk* pCurrentChunk);

//! Get chunk object which is next to a time stamp
/*! Moves in the file to the data chunk next to the time stamp.
\param ts time stamp
\return pointer to the chunk object next to time stamp
*/
	virtual CMCSAChunk* GetChunkNextTo(CMCSATimeStamp* ts);


//! Get first event of data stream
/*! See example code below for how to use the stream events to
access data. For raw data use the GetRaw..., or GetSweep... methods.
\code

void CTestDLLDoc::ReadSpikes()
{
// DP 01/2003
// this method describes the principle of reading spike data
// from an MC_Rack data file. In a real import method the code
// has to be optimized for speed!!

  // determine values for conversion of AD-values to voltages
  int iADZero = m_MCSStream.GetADZero();
  char cUnitSign = static_cast<char>(m_MCSStream.GetUnitSign());
  float fUnitsPerAD = static_cast<float>(m_MCSStream.GetUnitsPerAD());

	IMCSEvtSpike EventSpike; 
  EventSpike.AttachDispatch(m_MCSStream.GetFirstEvent());
  int iContinue = 1;
      
  // loop over all events
  while (iContinue == 1)
	{
		int iUnitID = EventSpike.GetUnitID(); //if 0 spike is not classified

    int iSeconds = EventSpike.GetSecondFromStart();
    int iMilliS = EventSpike.GetMillisecondFromStart();
    int iMicroS = EventSpike.GetMicrosecondFromStart();
    int iNanoS = EventSpike.GetNanosecondFromStart();

		float fSpikeTimeStamp = iSeconds +
														static_cast<float>(iMilliS) / 1000 +
														static_cast<float>(iMicroS) / 1000000 +
														static_cast<float>(iNanoS) / 1000000000;


		int iChannel = EventSpike.GetChannel();
		CString csChannelName = m_MCSStream.GetChannelName(iChannel);

  	int iPreTick = EventSpike.GetPreEvent();
		int iSpikeDataArraySize = EventSpike.GetCount();
		short* SpikeDataBuffer = new short[iSpikeDataArraySize];
		EventSpike.GetADDataArray(SpikeDataBuffer);

    // compute Voltage from iADData
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
\return Event object
*/
	virtual CMCSAEvent* GetFirstEvent();

//! Move to next Event
/*!
\return Event object
*/
	virtual CMCSAEvent* GetNextEvent(CMCSAEvent* pCurrentEvent);

//! Move to Event next ot the stime stamp
/*!
\param ts Time stamp
\return Event object next to time stamp
*/
	virtual CMCSAEvent* GetEventNextTo( CMCSATimeStamp* ts);

//! Get count of events within time stamp From to To
/*! EventCountFromTo() returns the number of events per channel within
the interval difined by time stamps From to To. The counts are written to the
arrEventCount, which has to be of size 128 (because the maximum number of channels is 128).
\param dispFrom pointer to a time stamp representing the interval start time
\param dispTo pointer to a time stamp representing the interval end times
\param arrEventCount array (size = 128) to store the event counts. In the case of 
*/
	virtual void EventCountFromTo(CMCSATimeStamp* dispFrom, CMCSATimeStamp* dispTo, long * arrEventCount);

	//! Get x channel position in a range from 0 (left) to 100 (right)
	/*! \param Index the channel index
	 * \attention this might not be the same as the relative position from the layout if not
	 * all channels of the MEA are in the stream
	 */
	int GetRelativeChannelPosX(short Index) const;

	//! Get y channel position in a range from 0 (top) to 100 (bottom)
	/*! \param Index the channel index
	 * \attention this might not be the same as the relative position from the layout if not
	 * all channels of the MEA are in the stream
	 */
	int GetRelativeChannelPosY(short Index) const;

	virtual long GetStreamFormatPrivate(char **pData);
	enum {readOK, readSkipped, readError};
	virtual int	ReadHdr(FILE* pFile);
	int WriteHdr(FILE* pFile);
	MCSHDR* GetMCSHDR();
	void DestroyChunks();
	STRMFMT* Get_pStrmFmt() const;

private:

	/*
	 **
	 ** MoveToChunk(CMCSATimeStamp* ts) 
	 ** Set the time point by the time stamp SetTimeStamp() method; 
	 ** @param The routine moves within the file to the chunk which includes 
	 ** the wanted (ns relative to start recording). 
	 ** @return bool true if chunk exists, false if not
	 */
	bool MoveToChunk(CMCSATimeStamp* ts);

	void GetMaxChannelPos(int& x, int& y) const;

	CMCSAChunk* ReadChunkFrom(FILE* pFile);
	CMCSAChunk* m_pCurrentChunk;
	DWORDLONG		m_qwStrmHdrSize;
	DWORDLONG		m_qwStrmFmtSize;
	char*			m_chStrmFmtPrivate;
	STRMHDR*		m_pStrmHdr;

	CMCSAChannel**	m_pChannels;

	char			m_chChunkID[9];
	char			m_chTypeID[4];

	STRMFMT*		m_pStrmFmt;

	CMCSAStreamFile* m_pStreamFile;

	vector<CMCSAChunk*> m_arrChunks;
	int				m_iPosition;

};


#endif // _MCSAStream_H_

/////////////////////////////////////////////////////////////////////////////
