/////////////////////////////////////////////////////////////////////////////
//
// MC_Rack
// Copyright (C) 2000-2010 Multi Channel Systems, all rights reserved
//
// $Workfile: MCStream.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_Rack/IncANSI/MCStream.h 25    25.08.11 16:31 Jesinger $
//
// $Modtime: 25.08.11 16:29 $
//
// $Log: /MC_Rack_II/MC_Rack/IncANSI/MCStream.h $
// * 
// * 25    25.08.11 16:31 Jesinger
// * added double  m_dUnitsPerAD_MEA21 to struct STRMFMT
// * 
// * 24    19.10.10 10:19 Merz
// * set MCS hdr version to 11 for Mea2100
// * 
// * 23    23.09.10 13:20 Loeffler
// * macro commented out
// * 
// * 22    16.09.10 10:03 Merz
// * added m_HasStimulation to MCSHDR
// * 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _COMMON_MCASTREAM_H_
#define _COMMON_MCASTREAM_H_

#ifdef _WIN32
#include <windows.h>
#else
#include "typedefs.h"
#endif

#ifndef _MC_RACK
// From StdLib.h, neccessary?
#ifndef _MAX_PATH
#define _MAX_PATH   260 /* max. length of full pathname */
#define _STDLIB_ADDED 
#endif
#endif
#define _MCS_PATH 260

/* GCC under linux aligns doubles and DWORDLONGS to 4 byte bounderies
   and not to 8 byte bounderies like linux
   #pragma pack does not change this
   workaround: force gcc whith __attribute__ ((aligned(8)) to 8 bytes alignment
*/

#ifdef __GNUC__
#define GCC_ALIGN8  __attribute__ ((aligned (8)))
#else
#define GCC_ALIGN8
#endif

enum MeaSourceType {PlainLayout, MeaLayout, DoubleMeaLayout, DefinedLayout, unknownSourceType};
enum MeaSubType {UnknownSubType = -1, ElectrodeChannels, AnalogChannels, DigitalChannels};
#define ElectrodeType_Unknown 0
#define ElectrodeType_Recording 1
#define ElectrodeType_Stimulating 2
#define ElectrodeType_Reference 4
#define ElectrodeType_Bath 8

#define ASSERT_MAX_CHUNK_SIZE 500000

const char idMCSSTRM[8] = {'M','C','S','S','T','R','M',' '};
const char idLISThdr[8] = {'L','I','S','T','h','d','r',' '};
const WORD wNumberOfImages = 4;

struct IMAGEDATA
{
	int			m_bSelectedElec1;
	int			m_bSelectedElec2;
	int			m_ixLayoutPosElec1;
	int			m_iyLayoutPosElec1;
	int			m_ixLayoutPosElec2;
	int			m_iyLayoutPosElec2;
	double		m_fxImagePosElec1   GCC_ALIGN8;
	double		m_fyImagePosElec1   GCC_ALIGN8;
	double		m_fxImagePosElec2   GCC_ALIGN8;
	double		m_fyImagePosElec2   GCC_ALIGN8;
	char		m_szImageFilePathName[_MCS_PATH];
};

//ATTENTION, if you change the Header or one of the stream format
//infos you also must change the
//HeaderVersion and adapt the MCStream.dll
//Append new variables at the end of the structs
//and take care of the changes in the MCStream.dll read code.
const char idMCSHDR[8]  = {'M','C','S','H','D','R',' ',' '};
const WORD wCurrentMCSHDRHeaderVersion = 11;
struct MCSHDR
{
	WORD		m_wHeaderVersion;				// Header Version
	DWORD		m_dwMSSoftwareVersion;			// Software Version High Bytes
	DWORD		m_dwLSSoftwareVersion;			// Software Version Low Bytes
	char		m_szFile[_MCS_PATH];			// File Name
	char		m_szComment[513];				// Comment
	DWORDLONG	m_qwTimeStamp   GCC_ALIGN8;					// time of pressing start button
												// This value is set a new when recording from replayer 
												// For split file it stays on value of first file
	DWORD		m_dwStreamCount;				// Number of Streams
	DWORD		m_dwMilliSamplesPerSecond;		// hardware sampling Rate, sampling frequency * 1000

	// from Version 1.35 (changed 23.2.1999 (HL))

	// this is a CMTimeWindowProperty
	int			m_iWindowChoice;// 0 = continuous; 1 = triggered start; 2 = triggered start/stop
	float		m_fTime1;				// Time 1 in ms, distance or peritriggertime 1
	float		m_fTime2;				// Time 2 in ms, extent or peritriggertime 2
	WORD		m_wID1;					// Trigger ID 1;
	WORD		m_wID2;					// Trigger ID 2;

	// default of these in registry
	MeaSourceType	m_iSourceType;			// MEA-Layout or other
	WORD		m_wElectrodeChannels1;
	WORD		m_wElectrodeChannelOffset1;
	WORD		m_wAnalogChannels1;
	WORD		m_wAnalogChannelOffset1;
	WORD		m_wDigitalChannels;
	WORD		m_wDigitalChannelOffset;
	WORD		m_wTotalChannels;

	// further important info
	DWORDLONG	m_qwEndTime        GCC_ALIGN8;			// the time of the last written segment
	DWORDLONG	m_qwSweepCount     GCC_ALIGN8;			// number of written sweeps

	// from Version 1.44 (variable sampling rate and VC 6.0)
	BOOL		m_bWithIndex;			// do we have an index at the end?

	DWORD		m_dwSegmentTime;

	// from Version 1.60
	DWORDLONG	m_qwStartTime    GCC_ALIGN8;			// data start time
										// This is start time for triggered data and
										// first written chunk time for continous data.
										// This value is copyied from replayer to recorder
	DWORD		m_dwMSDriverVersion;	// Driver Version High Bytes
	DWORD		m_dwLSDriverVersion;	// Driver Version Low Bytes

	//(DP)BufferID from Version 2.0
	char		m_szBufferID1[9];			// new BufferID from Start Trigger (instead of m_wID1)
	char		m_szBufferID2[9];			// new BufferID from Stop Trigger (instead of m_wID2)

	// from version 3.0
/*
	long		m_bSelectedElec1;
	long		m_bSelectedElec2;
	long		m_ixLayoutPosElec1;
	long		m_iyLayoutPosElec1;
	long		m_ixLayoutPosElec2;
	long		m_iyLayoutPosElec2;
	double		m_fxImagePosElec1    GCC_ALIGN8;
	double		m_fyImagePosElec1    GCC_ALIGN8;
	double		m_fxImagePosElec2    GCC_ALIGN8;
	double		m_fyImagePosElec2    GCC_ALIGN8;
	char		m_szImageFilePathName[_MCS_PATH];
*/
	// from Version 3.2
	IMAGEDATA	m_arrImageData[wNumberOfImages];

	WORD		m_wElectrodeChannels2;
	WORD		m_wElectrodeChannelOffset2;
	WORD		m_wAnalogChannels2;
	WORD		m_wAnalogChannelOffset2;

	int			m_lADVoltage;

	int			m_MCRack_DataSourceType; // 0=MC_Card 1=USB_MEA 2=Simulation
	char		m_DataSourceName[80];
	char		m_SerialNumber[20];
	int			m_BusType;
	int			m_VendorId;
	int			m_ProductId;

	bool		m_HasStimulation;
};

// Layout info
const char idLAYOUTHDR[8]  = {'L','A','Y','O','U','T',' ',' '};

// Layout info
const char idMEA21STIMULATORHDR[8]  = {'S','T','I','M','2','1',' ',' '};


// common part of stream header
const char idSTRMHDR[8]  = {'S','T','R','M','H','D','R',' '};
const WORD wCurrentSTRMHDRHeaderVersion = 0;
struct STRMHDR
{
	WORD	m_wHeaderVersion;			// Header Version
	char    m_szType[9];				// type name of data
	char    m_szName[257];				// name of stream
	char    m_szComment[513];			// comment
	WORD	m_wID;										// ID of stream
	DWORD	m_dwMilliSamplesPerSecond;	// software Sampling Rate
	DWORD	m_dwChannelCount;			// Number of channels
	char	m_szBufferID[9];			// new BufferID (for example trig0001)
};
// following the common part of stream header there is a 
// list of m_dwChannelCount channel headers

// common part of channel header
const WORD wCurrentCHNNLHDRHeaderVersion = 2;
struct CHNNLHDR
{
	WORD	m_wHeaderVersion;			// Header Version
	DWORD	m_dwID;						// channel ID, position in buffer
	DWORD	m_dwHWID;					// channel hardware ID, derived from HW channel ID
	char	m_szName[257];				// name of channel
	char	m_szComment[513];			// comment
	DWORD	m_dwRefCount;				// number of referenced channels
	WORD	m_wGroupID;					// ID of the channel group (tetrode ...) 0 = no group
	char	m_szDecoratedName[257];     // 
	int		m_lGain;					// 
	int     m_ElectrodeType;			// reference | recording | stimulation | bath
	int     m_posX;
	int		m_posY;
	int     m_posZ;
	int		m_ExtendX;
	int		m_ExtendY;
	int		m_Diameter;
	int		m_Dx;						// Display position x
	int     m_Dy;						// Display position y
	int     m_Dxextend;					// Display size width
	int		m_Dyextend;					// Display size height
	int		m_LowF;						// Low Amplifier Frequency
	int		m_HighF;					// High Amplifier Frequency
};
// following the common part of channel header there is a 
// list of m_dwRefCount reference headers

// reference header
struct REFHDR
{
	//DPBufferID: REFHDR  not used, and not usable since MCSHDR 5 due to changed buffer id
	WORD	m_wBuffer;					// ID of referenced buffer
	DWORD	m_dwChannel;				// ID of referenced channel in referenced buffer
};

// common part of stream format
const char idSTRMFMT[8]  = {'S','T','R','M','F','M','T',' '};
//const WORD wCurrentSTRMFMTHeaderVersion = 0;  // size: 24
const WORD wCurrentSTRMFMTHeaderVersion = 1;
struct STRMFMT
{
	WORD	m_wHeaderVersion;			// Header Version

	char	m_cUnitSign;				// Unit Sign, e.g. V, A etc.
	WORD	m_wBits;					// number of bits AD to encode data
	WORD	m_wZeroAD;					// zero line of AD
	double  m_dUnitsPerAD   GCC_ALIGN8;	// Units per AD step (on MEA21 depending on selected 16 bit Range)

	WORD	m_wBytesPerChannel;			// number of bytes per channel
	WORD	m_wDefaultSamplesPerSegment;// suggested segment size
	WORD	m_wDefaultSegmentCount;		// suggested buffer size

	// new filed starting with wCurrentSTRMFMTHeaderVersion = 1
	double  m_dUnitsPerAD_MEA21     GCC_ALIGN8;		// Units per AD step (on MEA21 the "real" value, needed for feedback)
};

// index
const char idINDEX1POS[8]  = {'I','D','X','1','P','O','S',' '};

const char idINDEX1MCSHDR[8]  = {'I','D','X','1','M','C','S',' '};
const WORD wCurrentINDEX1MCSHDRHeaderVersion = 1;
struct INDEX1MCSHDR
{
	WORD		m_wHeaderVersion;		// Header Version
	char		m_szFile[257];			// File Name
	DWORD		m_dwStreamCount;		// Number of Streams, for consistency checks
	DWORD		m_wIndexSize;			// number of index items
	DWORDLONG	m_qwTimeStampFirst   GCC_ALIGN8;		// timestamp of first index entry, for consistency checks
	DWORDLONG	m_qwTimeStampLast    GCC_ALIGN8;		// timestamp of last index entry, for consistency checks
	DWORD		m_wSweepSize;			// number of sweep start/end entries
	DWORDLONG	m_qwSweepStartFirst   GCC_ALIGN8;	// timestamp of first entry of sweep start times, for consistency checks
	DWORDLONG	m_qwSweepEndLast      GCC_ALIGN8;		// timestamp of last entry of sweep end times, for consistency checks
};

const char idINDEX1[8]  = {'I','D','X','I','D','X',' ',' '};
struct INDEX1
{
	DWORDLONG	m_qwTimeStampFrom    GCC_ALIGN8;		// time stamp of indexed chunk
	DWORDLONG	m_qwFileOffset       GCC_ALIGN8;		// offset of indexed chunk
};

const char idINDEX1SWEEPS[8]  = {'I','D','X','S','W','E','E','P'};

#define INDEXDISTANCE   250000			// An Index is written every INDEXDISTANCE bytes


#ifndef _MC_RACK
#ifdef _STDLIB_ADDED
#undef _MAX_PATH
#undef _STDLIB_ADDED
#endif
#endif

#ifdef linux
#include <ctype.h>
#define _FILE_OFFSET_BITS 64
#define _fseeki64 fseeko
#define _ftelli64 ftello
#elif __APPLE__
#include <ctype.h>
#define _FILE_OFFSET_BITS 64
#define _fseeki64 fseeko
#define _ftelli64 ftello
#endif

#ifdef linux
#define UNUSED_ALWAYS(x)
#elif __APPLE__
#define UNUSED_ALWAYS(x)
//#else
//#define UNUSED_ALWAYS(x) x
#endif

#endif	// _COMMON_MCASTREAM_H_
