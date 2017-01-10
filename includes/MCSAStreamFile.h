/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAStreamFile.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAStreamFile.h 28    30.09.10 11:19 Merz $
//
// $Modtime: 22.09.10 13:35 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAStreamFile.h $
// * 
// * 28    30.09.10 11:19 Merz
// * changes for MEA21 Stimulator
// * 
// * 27    6.11.08 15:24 Paetzold
// * 
// * 26    4.11.08 15:06 Loeffler
// * use windows.h instead of typedefs.h if _WIN32 is defined
// * 
// * 25    5.09.08 14:54 Paetzold
// * 
// * 24    25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 23    22.05.07 8:30 Loeffler
// * raw timestamp functions added
// * 
// * 22    22.01.07 22:44 Paetzold
// * Cancel possibility when merging
// * 
// * 21    22.01.07 16:51 Paetzold
// * Callback routine for merging files
// * 
// * 20    19.12.06 14:19 Jesinger
// * 
// * 19    18.12.06 12:45 Loeffler
// * docu changes
// * 
// * 18    15.12.06 15:50 Loeffler
// * docu changes
// * 
// * 17    14.12.06 16:33 Jesinger
// * removed linux warnings
// * 
// * 16    14.12.06 15:51 Jesinger
// * removed paths from #include statements
// * 
// * 15    14.12.06 14:17 Loeffler
// * docu changes
// * 
// * 14    4.10.06 17:16 Paetzold
// * Bug fix when merging indexes
// * Keep attention to splitted sweeps when merging indexes
// * 
// * 13    15.08.06 11:22 Jesinger
// * changed include name "MCStream..." -> "MC_Stream..."
// * 
// * 12    9.05.06 23:47 Paetzold
// * Sorting by date
// * Test ident format
// * 
// * 11    23.04.06 22:44 Paetzold
// * Update for Merge
// * 
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the MCStream file object
 */
#ifndef _MCSAStreamFile_H_
#define _MCSAStreamFile_H_

#include <time.h>
#include <vector>
//using namespace std;
#include "MCSATimeStamp.h"
#include "MIndex1.h"

enum FileOpenResult {
	OK,
	FILE_OPEN_FAILED,
	WRONG_FILEFORMAT,
	forWRONG_HEADER,
	forNO_DATA
	};

typedef int (*mergecallback)(const char* text,int progress);

struct MCSHDR;
class CMCSAStream;
class CMCSAChunk;
class CMCLayout;
class CMMea21StimulatorProperty;

//! 
/*!
\mainpage

This documentation and the examples are published with MC_Rack V 3.5. 
For updates or questions please visit our homepage 
<a href="http://www.multichannelsystems.com">Multi Channel Systems</a>
or contact <a href="mailto:support@multichannelsystems.com">support@multichannelsystems.com</a>.

\section intro Introduction
The MCStream Automation Server is a Dynamic Link Library (DLL) named MCStream.dll, 
which contains code for reading Data Files that were recorded with Multi Channel System's 
data acquisition software MC_Rack. The code in the DLL can be called from any Windows 
program which can access objects of an OLE Automation Server. Such programs can be 
written, e.g. in Visual Basic, Visual C++, Borland C++, and many other programming languages. 

The MCStream OLE-Automation Server provides access to Automation Objects, representing MC_Rack 
data files, data streams in the data file, channels, events (data), and info in the data streams. 
These objects have attributes which can be read, and methods, which can be executed.
The stream object, for example, 
has an attribute named <code>NumberOfStreams</code>, which gives the number of streams stored in the 
data file. This object also has a method called <code>OpenFile()</code> to open an MC_Rack data file.

The MCStream OLE-Automation Server can read data from Version 1.70 and higher of MC_Rack,
so you don't have to bother learning the (complex) file format of the data files. 
The DLL contains a lot of code you would 
have to write yourself, if you wanted to access the data files directly. As the data 
format of MC_Rack will be adopted from time to time, we will provide new verions of the 
MCStream Automation Server which can read <b>new</b> and <b>old</b> data formats. There is also code 
in the DLL patching some header inconsistencies due to resolved MC_Rack bugs.

We provide an ANSI C++ compatible library for reading the data on Linux. It is part of the
MCStreamSupport files which are (optionally) installed with MC_Rack. On request we also provide 
this library for MSVC 8 on Windows.

\subsection objects The Object Hierarchy of the MCStream OLE-Automation Server

The MCStream OLE-Automation Server provides access to objects of six different classes: 
File, Stream, Channel, Chunk, Event, TimeStamp, Info.

The File object represents a data file written with MC_Rack. It contains zero or more 
Stream objects, which represent data streams within the file, e.g. raw data, spike data, 
trigger data, etc.

A data stream has zero or more Channel objects, which contain information about the 
channels in the stream, most notably the channel name. Usually, you don't need the 
channel object, because you can access the channel names via the stream object. Stream 
dependent configuration information can be get as an Info object.

A data stream stores zero or more (usually quite a lot of) Event objects, representing 
one event or data point. These events are
<ul>
<li>raw data measured at one point in time at all selected channels</li>
<li>a spike on one of the selected channels</li>
<li>a trigger event</li>
<li>an analyzer event combining the different extracted parameters (min, max) of all 
		selected channels at one time point</li>
<li>a spike analyzer event combining the extracted parameters of the spike analyzer</li>
</ul>

Internally, these events are stored in groups called Chunks. But usually, you don't 
need to know about Chunk objects.

Finally, every Event is associated with a TimeStamp object, which gives you the time 
(Year, Day, Month, Hour, Second, Millisecond, Microsecond, Nanosecond) this event 
was recorded. For convenience you can access the time of the event via the Event 
object directly.

Graphically, the object model looks like this:

<img src="MCStreamHierarchy.gif" align="middle" border=1 width=218 height=269>

The Event class has several subclasses, representing raw data, spikes, trigger events, 
prameters, .... The subclasses have additional methods and attributes. The method 
<code>GetFirstEvent()</code> of the stream object returns an object of the appropriate subclass. 
To determine which object the method GetFirstEvent() will return, look at the 
DataType attribute of the stream object. There are different info classes 
for the different DataTypes.

\subsection about About this documentation

In the current version of this documentation the following objects are described:

<ul>
<li> File: CMCSAStreamFile </li>
<li> Stream: CMCSAStream </li>
<li> Channel: CMCSAChannel </li>
<li> Event: CMCSAEvent 
	<ul>
	<li> Raw Data Event: </li>
	<li> Spike Event: CMCSAEvtSpike </li>
	<li> Trigger Event: CMCSAEvtTrigger</li>
	<li> Average Event: </li>
	<li> Parameter Event: </li>
	<li> Spike Parameter Event: CMCSAEvtSpikeParameter</li>
	</ul>
    </li>
<li> Info: 
	<ul>
	<li> Raw Data Info: </li>
	<li> Filter Info: </li>
	<li> Spike Info: CMCSAInfoSpike </li>
	<li> Trigger Info: CMCSAInfoTrigger</li>
	<li> Average Info: </li>
	<li> Parameter Info: </li>
	<li> Spike Parameter Info: CMCSAInfoSpikeParameter</li>
	</ul>
</li>
<li> TimeStamp: CMCSATimeStamp</li>
</ul>

\note the code for MCStream.dll is divided in two parts
<ol><li>ANSI C++ compatible code</li>
<li>OLE/COM wrapper</li>
</ol>
This documentation is based on the ANSI C++ files. You'll have to change the names of the classes if 
you use the COM interface:<br>
The ANSI C++ classes are named with an additional 'A' compared to the COM interfaces, e.g. the 
interface for a CMCSAStream is IMCSStream, for CMCSATimeStamp IMCSTimeStamp etc.
TimeStamps of the COM interface are returned as Dispatch not raw pointers<br>
(see also the example code)


<p>
</p>
<br>
<p>
</p>
\section start Getting started

\subsection example Example usage

The MSVC project MC_StreamTest in the MC_StreamSupport directory is provided to help you get started using
the MC_Stream.dll. This project was created via the MSVC (Microsoft <span>&copy;</span> Visual C++ 2005) project wizard creating an MFC dialog based application.
The example uses ATL CComPtr because it are easier to use than the Dispatch interface of MFC.

The projects allows to open an MC_Rack data file, shows the data stream which were recorded and for each
stream the recorded channels. It also shows some info about the stream and channel objects.

The function <code>QuickTestMCDFile()</code> shown here shows how to do all of this in one place. For more realistic
code see the file MC_StreamTestDlg.cpp in the example project.


\subsection examplefct Example function

The basic procedure to get to the data is:
<ol>
<li>open the mcd file</li>
<li>optionally read some file info, like the start time in the example</li>
<li>get the number of data streams</li>
<li>for each desired stream get the number and IDs of the recorded channels</li>
<li>for each channel read the raw data, either with timestamps from and to or looping over the events</li>
 <ul>
 <li>create the desired interface for the CComPtr, e.g.<br>
 <code>m_IStreamFile.CoCreateInstance(_bstr_t("MCSTREAM.MCSSTRM"));</code> <br>
MCSTREAM.MCSSTRM is the ProgID of the MCStream.dll
</li>
<li>use the pointer:<br>
<code>short res = m_IStreamFile->OpenFileEx("Example.mcd");</code> </li>
</ul>
</ol>


\code

void CMC_StreamTestDlg::QuickTestMCDFile(void)
{
    CString strFilter = "MC_Rack Data (*.mcd)|*.mcd|All Files (*.*)|*.*||";
    CFileDialog dlg(
        TRUE,
        NULL,
        NULL,
        OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR,
        strFilter,
        this);

    if (dlg.DoModal() == IDOK)
    {
        CComPtr<MCStream::IMCSStreamFile> IMcdFile;
        HRESULT hres = IMcdFile.CoCreateInstance(_bstr_t("MCSTREAM.MCSSTRM"));
        if (hres != S_OK)
        {
            MessageBox("Could not find registered MCStream.dll");
            return;
        }
        // open the mcd file
        short res = IMcdFile->OpenFileEx(_bstr_t(dlg.GetPathName()));
        if (res != 0)
        {
            CString s;
            s = "Error loading file: ";
            s += dlg.GetPathName();
            s += "\n";

            switch(res)
            {
            case 0: break;
            case 1: s += "File can not be opened.";
                break;
            case 2: s += "Wrong file format.";
                break;
            case 3: s += "Wrong file header.";
                break;
            case 4: s += "Empty data file.";
                break;
            default: ASSERT(0);
            }
            AfxMessageBox(s);
            return;
        }

        // demonstrates how to handle TimeStamp dispatch
        IDispatchPtr pStart = IMcdFile->GetStartTime();
        IDispatchPtr pStop = IMcdFile->GetStopTime();
        CComPtr<MCStream::IMCSTimeStamp> ItsStart;
        CComPtr<MCStream::IMCSTimeStamp> ItsStop;
        ItsStart = (MCStream::IMCSTimeStamp*) pStart.GetInterfacePtr();
        ItsStop = (MCStream::IMCSTimeStamp*) pStop.GetInterfacePtr();

        long yearStart = ItsStart->GetYear();
        long monthStart = ItsStart->GetMonth();
        long dayStart = ItsStart->GetDay();
        long hourSart = ItsStart->GetHour();
        long minStart = ItsStart->GetMinute();
        long secStart = ItsStart->GetSecond();

        TRACE("Start time of file: %d-%d-%d %d:%d:%d\n", yearStart, monthStart, dayStart, hourSart, minStart, secStart);

        long numStreams = IMcdFile->GetStreamCount();

        // do something with the data streams
        CString buffers;
        buffers.Format("%d buffers in file: ", numStreams);
        for (int i=0; i<numStreams; i++)
        {
            CComPtr<MCStream::IMCSStream> IStream = MakeSP<MCStream::IMCSStream>(IMcdFile->GetStream(i));

            buffers += IStream->GetBufferID().GetBSTR();
            buffers += " ";
        }
        buffers += "\n";
        TRACE(buffers);

        if (numStreams > 0)
        {
            // get some channel info for first buffer
            CComPtr<MCStream::IMCSStream> IStream = MakeSP<MCStream::IMCSStream>(IMcdFile->GetStream(0));

            long numChannels = IStream->GetChannelCount();
            CString channels;
            CString bufID = IStream->GetBufferID();
            channels.Format("%d channels in buffer %s: ", numChannels, bufID); 
            for (int i=0; i<numChannels; i++)
            {
                CComPtr<MCStream::IMCSChannel> IChannel = MakeSP<MCStream::IMCSChannel>(IStream->GetChannel(i));

                CString name = IChannel->GetDecoratedName();
                long hwID = IChannel->GetHWID();
                CString tmp;
                tmp.Format("ch: %s, HWID: %d, ", name, hwID);
                channels += tmp;
                if (i % 16 == 0)
                {
                    channels += "\n";
                    TRACE(channels);
                    channels = "";
                }
            }
            channels += "\n";
            TRACE(channels);
        }

        // now do something different for each different type of buffer
        for (int i=0; i<numStreams; i++)
        {
            CComPtr<MCStream::IMCSStream> IStream = MakeSP<MCStream::IMCSStream>(IMcdFile->GetStream(i));
            CString bufferID = IStream->GetBufferID();
            if (bufferID.Find("spks") != -1)
            {
                // see function ReadSpikeData()
            }
            else if (bufferID.Find("elec") != -1)
            {
                // read first 100 ms of raw data
                CComPtr<MCStream::IMCSTimeStamp> ItsStart = MakeSP<MCStream::IMCSTimeStamp>(IMcdFile->GetStartTime());

                ItsStart->SetNanosecondFromStart(0);
                ItsStart->SetMicrosecondFromStart(0);
                ItsStart->SetMillisecondFromStart(0);
                ItsStart->SetSecondFromStart(0);
                CComPtr<MCStream::IMCSTimeStamp> ItsEnd;

                // must create a new object
                IDispatchPtr pEnd;
                pEnd = ItsStart->Clone();
                ItsEnd = (MCStream::IMCSTimeStamp*)pEnd.GetInterfacePtr();
                ItsEnd->SetMillisecondFromStart(100);
                ItsEnd->SetMicrosecondFromStart(0);
                ItsEnd->SetNanosecondFromStart(0);
                ItsEnd->SetSecondFromStart(0);

                long eventCount = 0;
                IStream->EventCountFromTo(ItsStart, ItsEnd, &eventCount);
                TRACE("There are %d events in the first 100 ms\n", eventCount);

                long bufferSize = IStream->GetRawDataBufferSize(ItsStart, ItsEnd);
                short* pBuffer = new short[bufferSize];

                long rawDataCount = IStream->GetRawData(pBuffer, ItsStart, ItsEnd);
                if (bufferSize != rawDataCount)
                {
                    TRACE("error reading data\n");
                    delete[] pBuffer;
                    return;
                }

                TRACE("Data for first 100 ms\n");
                long numChannels = IStream->GetChannelCount();

                // for raw data the following can be asserted
                ASSERT(eventCount * numChannels == bufferSize);
                
                // example for channel 0
                int offset = 0;
                for (int i=0; i<100; i++)
                {
                    short d = pBuffer[(i*numChannels) + offset];
                    TRACE("%hd\n", d);
                    // the buffer contains the raw ADC data, these must be converted to real world units
                    // see function ReadContinuousRawData()
                }
                delete[] pBuffer;
            }
        }
        IMcdFile->CloseFile();
    }
}

\endcode

*/

//! Interface for mcd files
/*! This is the entry point to all other MC_Stream interfaces
 */
class CMCSAStreamFile
{
public:
    //! constructor
    /*! if you use the COM interface, you would create an object for example like:
    \code
        CComPtr<MCStream::IMCSStreamFile> IMcdFile;
        HRESULT hres = IMcdFile.CoCreateInstance(_bstr_t("MCSTREAM.MCSSTRM"));
    \endcode
    */
	CMCSAStreamFile();
    //! destructor, closes the file if necessary, better call CloseFile() instead
	virtual ~CMCSAStreamFile();
	
//! Open MC_Rack data file (mcd file)
/*! Open a MC_Rack data file, and read the file header, which contains
info about the file, the recorded data streams and channels.<br>
\note If you use the COM interface, use <code>OpenFileEx()</code>
\param szFileName The complete path to the mcd file
\return File open error code
	<ul>
		<li> 0 = OK </li>
		<li> 1 = File can not be opened. </li>
		<li> 2 = Wrong file format. </li>
		<li> 3 = Wrong file header. </li>
		<li> 4 = Empty data file. </li>
	</ul>
*/	
	FileOpenResult OpenFile(LPCTSTR szFileName);

//! Close MC_Rack data file
/*! Closes the MC_Rack file, deletes the stream objects and the MCSHdr structure.
\return
	<ul>
		<li> 0 = OK </li>
	</ul>
*/	
	short CloseFile();

//! Get MC_Rack software version major part
/*!
\return software version (major part) of the recording software with which the mcd file was recorded.
This is a 4 byte value. The first two bytes indicate the major part of the version, the lower bytes the minor part<br>
Example
\code
int swMajor = m_IStreamFile->GetSoftwareVersionMajor();
int swMajor1 = swMajor >> 16;
int swMajor2 = swMajor & 0x0000FFFF;
\endcode
*/
	virtual long GetSoftwareVersionMajor();

//! Get MC_Rack software version minor part
/*!
 * \see GetSoftwareVersionMajor()
\return software version (minor part) of the recording software with which the mcd file was recorded.
*/
	virtual long GetSoftwareVersionMinor();

//! Get MC_Rack file header version
/*!
 * for internal use only
\return version of the mcd file header
*/
	virtual short GetHeaderVersion();


//! Get recording mode
/*! MC_Rack data can either be continuous or triggered (sweeps). For triggered data
the sweeps are of the same length (start on trigger and a fixed cut out interval)
\if deprecated
or it is variable (start and stop of the sweep is determied by a trigger signal).
\endif
\return mode:
	<ul>
	<li> 0 for continuous </li>
	<li> 1 for triggered start </li>
\if deprecated
	<li> 2 for triggered start/stop recordings. </li>
\endif
	</ul>
*/	
	virtual long GetRecordingMode();

//* Get data source type
/*! 
\return mode:
	<ul>
	<li> 0 for Plain layout </li>
	<li> 1 for MEA layout </li>
	<li> 2 for double Mea Layout </li>
	<li> 3 for unknown layout. </li>
	</ul>
*/	
	virtual short GetSourceType();

//! Get millisamples per second
/*!	To get the sample rate in Hz, divide the return value by 1000.
\return milli samples per second
*/
	virtual long GetMillisamplesPerSecond();

	virtual char* GetComment();

//! Get Year component of recording start time
/*!
\return Year component of recording start time
*/
	virtual short GetYear();

//! Get Month component of recording start time
/*!
\return Month component of recording start time
*/
	virtual short GetMonth();

//! Get Day component of recording start time
/*!
\return Day component of recording start time
*/
	virtual short GetDay();

//! Get Hour component of recording start time
/*!
\return Hour component of recording start time
*/
	virtual short GetHour();

//! Get Minute component of recording start time
/*!
\return Minute component of recording start time
*/
	virtual short GetMinute();

//! Get Second component of recording start time
/*!
\return Second component of recording start time
*/
	virtual short GetSecond();

//! Get Millisecond component of recording start time
/*!
\return Millisecond component of recording start time
*/
	virtual short GetMillisecond();

//! Get Microsecond component of recording start time
/*!
\return Microsecond component of recording start time
*/
	virtual short GetMicrosecond();

//! Get Nanosecond component of recording start time
/*!
\return Nanosecond component of recording start time
*/
	virtual short GetNanosecond();

//! Get number of data streams of the currenly opened data file.
/*!	Data stream are electrode raw data, filtered data, digital data,
spikes, and so on.
\return number of data streams
*/
	virtual long GetStreamCount();

//! Get a pointer to a stream object
/*!
\param Index to the array of streams (0 up to <code>GetStreamCount() - 1</code>)
\return pointer to stream object
*/
	virtual CMCSAStream* GetStream(long Index);

//! Get the number of sweeps
/*! If the number of sweeps is larger than 0, the data is stored as sweeps
(and not continuous) in the file. The return value is the actual number of sweeps.
\code

long lSweepCount = m_MCSFile.GetSweepCount();
if(lSweepCount > 0)
{
	long lSweepLength = m_MCSFile.GetSweepLength();
	
	for(long sc = 0; sc < lStreamCount; ++sc)
	{
		// create stream object
		m_MCSStream.AttachDispatch(m_MCSFile.GetStream(sc));
		CString csBufferID = m_MCSStream.GetBufferID();

		if((csBufferID.Find("elec") != -1) ||
			(csBufferID.Find("filt") != -1) ||
			(csBufferID.Find("anlg") != -1) ||
			(csBufferID.Find("digi") != -1))
		{
			for(long sweep = 0; sweep < lSweepCount; ++sweep)
			{
				IMCSTimeStamp SweepStart;
				LPDISPATCH lpd = m_MCSFile.GetSweepStartTimeAt(i);
				SweepStart.AttachDispatch(lpd);
				int iSeconds = SweepStart.GetSecondFromStart();
				int iMilliS = SweepStart.GetMillisecondFromStart();
				int iMicroS = SweepStart.GetMicrosecondFromStart();
				int iNanoS = SweepStart.GetNanosecondFromStart();
				SweepStart.ReleaseDispatch();
				__int64 i64RecordingTime =	static_cast<__int64>(iSeconds) * 1000000 +
																		static_cast<__int64>(iMilliS) * 1000 +
																		static_cast<__int64>(iMicroS);

				long lSweepSize = m_MCSStream.GetSweepRawDataBufferSize(lSweep);
				short* pMCDBuffer = new short [lSweepSize];
				if(lSweepSize != m_MCSStream.GetSweepRawData(pMCDBuffer, lSweep))
				{
					AfxMessageBox("Error reading Sweep");
					return false;
				}
			}
		}
		m_MCSStream.ReleaseDispatch();
	}		
}
\endcode
\return number of recorded sweeps
*/
	virtual int GetSweepCount();

//! Get sweep length
/*!
\return sweep length in milli seconds
*/
	virtual long GetSweepLength();

//! Get duration of the pre trigger
/*!
\return pre trigger interval in ms
*/
	virtual long GetPreTriggerTime();

//! This method is deprecated
/*! use the method GetSweepLength instead.
*/
	virtual long GetPostTriggerTime();

//! Get the sweep start time
/*!
\see example code
\param lSweep Index to sweep
\return TimeStamp object of sweep start time
*/
	virtual CMCSATimeStamp* GetSweepStartTimeAt(long lSweep);

//! Get the sweep end time
/*!
\param lSweep Index to sweep.
\return Time stamp object
*/
	virtual CMCSATimeStamp* GetSweepEndTimeAt(long lSweep);

    //! Get the sweep start time as a DWORDLONG (time in ns)
    virtual DWORDLONG GetSweepRawStartTimeAt(long sweepIndex);


//! This method is deprecated
	virtual long GetStartTriggerStreamID();

//! This method is deprecated
	virtual long GetStopTriggerStreamID();

//! Get time stamp of start pressed
/*! Time stamp when sart button was pressed. For continuous
data it is very close to the time of the fist data sample, but
for triggered data both values may differ enormously.
\see GetStartTime().
\return Time stamp when start button was pressed
*/
	virtual CMCSATimeStamp* GetTimeStampStartPressed();

//! Get start time
/*! The start time is the time point of the first data sample.
\return Time stamp of the first data sample.
*/
	virtual CMCSATimeStamp* GetStartTime();

//! Get stop time
/*! the stop time is the time stamp of the last data sample.
\return Time stamp of the last data sample.
*/
	virtual CMCSATimeStamp* GetStopTime();

	virtual BOOL GetWithIndex();
	virtual long GetSegmentTime();
	virtual FILE*		GetFilePointer();
	virtual DWORDLONG	GetFirstChunkPosition();
	virtual short SetStartTriggerStreamID(long pStreamID);
	virtual short SetStopTriggerStreamID(long pStreamID);
	virtual long GetStreamIndexForStreamID(char* ciD);
	virtual void GetImageData(long, long*, long*, long*, long*, long*, long*, double*, double*, double*, double*);
	virtual char* GetImageFilePathName(long);
	CMIndex1* GetIndex();
	void SetTempDir(char* pcTempDir);
	MCSHDR* GetMCSHDR();
	
	DWORDLONG	m_qwChunkStart;
	BOOL m_bForce128msChunks;
	BOOL m_bAllowForce128ms;

	long CopyMerge(CMCSAStreamFile** listFiles,int n,char* cOutfile,mergecallback callback = NULL);
	static long Sort(CMCSAStreamFile** listFiles,int n);
	static long CheckIdentFormat(CMCSAStreamFile** listFiles,int n);
	static long CheckIdentFormat(CMCSAStreamFile* file1, CMCSAStreamFile* file2);
	static void GetLastMergeError(char* errstr, long len);

	short GetElectrodeChannels();
	short GetAnalogChannels();
	short GetDigitalChannels(); 
	short GetTotalChannels();
	long GetDriverVersionMajor(); 
	long GetDriverVersionMinor();
	short GetElectrodeChannels2();
	short GetAnalogChannels2();
	short GetElectrodeChannelOffset1(); 
	short GetElectrodeChannelOffset2();
	short GetAnalogChannelOffset1();
	short GetAnalogChannelOffset2();
	long GetVoltageRange(void);

	CMCLayout* GetLayout(){return m_Layout;};
	CMMea21StimulatorProperty* GetMea21StimulatorProperty() {return m_MMea21StimulatorProperty;};

	int MCRack_DataSourceType();
	char* GetDataSourceName();
	char* GetSerialNumber();
	int GetBusType();
	int GetVendorId();
	int GetProductId();

private:
	bool m_bChunkLonger128ms;
	void Destroy();
	virtual BOOL		ReadHdr();
	int WriteHdr(FILE* pFile);
	
	/*
	 ** ReadIndexFile() access previously generated index file to obtain
	 ** @param CMIndex1 reference to CMIndex1
	 ** @return bool: true if IndexFile was read successfully, false if not.
	 */
	bool ReadIndexFile(CMIndex1& Index);

	/*
	 ** GenerateIndex() extracting index by reading the whole mcd file
	 ** @param CMIndex1 reference to CMIndex1
	 ** @return bool: true if Index was extracted successfully, false if not.
	 */
	bool GenerateIndex(CMIndex1& Index);

	/*
	 ** ReconstuctRecordingMode() determines recording mode for files Version < 1.34
	 ** @return long RecordingMode //0=continous, 1=StartOnTrigger, 2=StartAndStopOnTrigger
	 ** up to now only 0 and 1 are returned; startAndSpotOn Trigger has still to be implemented
	 */
	long ReconstructRecordingMode();

	/*
	 ** ReconstuctSweepLength() determines sweep length for files Version < 1.34
	 ** @return long SweepLength
	 */
	long ReconstructSweepLength();

	/*
	 ** ReconstuctStartTime() determines the Start time (first written chunk)
	 ** @return DWORDLONG StartTime
	 */
	DWORDLONG ReconstructStartTime();

	void DestroyChunks();
	CMCSAChunk* GetFirstChunk();
	CMCSAChunk* GetNextChunk(CMCSAChunk* pCurrentChunk);
	CMCSAChunk* ReadChunkFrom(FILE* pFile);

	long AppendFirstFile(CMCSAStreamFile* file);
	long Append(CMCSAStreamFile* file);
	long CloseMerge();

	mergecallback m_callback;
	char* m_callbacklasttext;
	int m_callbacklastprogress;
	clock_t m_callbacklastcall;
	int HandleCallback(const char* text,int progress);

	char  m_chID[8];	

	CMCSATimeStamp m_TimeStampStartPressed;
	CMCSATimeStamp m_StartTime;
	CMCSATimeStamp m_StopTime;

	MCSHDR*			m_pMCSHdr;
	CMIndex1		m_Index;

	FILE*			m_pFile;
	DWORDLONG		m_qwListHdrSize;
	CMCSAStream**	m_pStreams;
	DWORDLONG		m_qwFirstChunkPosition;
	DWORDLONG		m_qwStreamSize;
	DWORDLONG		m_qwIndexWritePos;
	DWORDLONG       m_qwIndexReadPos;
	long			m_lStartTriggerStreamID;
	long			m_lStopTriggerStreamID;
	char			m_szFileName[_MCS_PATH];
	char*			m_pcTempDir;

	vector<CMCSAChunk*> m_arrChunks;
	int				m_iPosition;

	CMCLayout* m_Layout;

	CMMea21StimulatorProperty* m_MMea21StimulatorProperty;

	// Merge error
	static char m_merge_error_string[255];
};

#endif

/////////////////////////////////////////////////////////////////////////////
