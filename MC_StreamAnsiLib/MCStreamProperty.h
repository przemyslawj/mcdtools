/////////////////////////////////////////////////////////////////////////////
//
// MC_Rack
// Copyright (C) 2000-2010 Multi Channel Systems, all rights reserved
//
// $Workfile: MCStreamProperty.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_Rack/IncANSI/MCStreamProperty.h 56    3.12.10 12:54 Merz $
//
// $Modtime: 1.12.10 15:42 $
//
// $Log: /MC_Rack_II/MC_Rack/IncANSI/MCStreamProperty.h $
// * 
// * 56    3.12.10 12:54 Merz
// * Trial Synchronization for Andreas Kreiter, 20Hz for Enzo Wanke
// * 
// * 55    30.09.10 11:16 Merz
// * changes for MEA21 Stimulator
// * 
// * 54    16.09.10 10:06 Merz
// * changes for the MEA21 Stimulator
// * 
// * 53    6.08.10 16:17 Merz
// * changes for MEA21 Stimulator
// * 
// * 52    6.08.10 14:23 Merz
// * 
// * 51    18.06.10 15:26 Merz
// * added the functions GetLowerCutoffAsFloat and GetUpperCutoffAsFloat
// * 
// * 50    1.06.10 13:35 Paetzold
// * Added header files for new Linux c++ compilers
// * 
// * 49    1.06.10 11:54 Paetzold
// * moved static variable to cpp file to remove warning
// * 
// * 48    11.05.10 15:13 Paetzold
// * After merge from DownSampling
// * 
// * 47    10.05.10 15:05 Paetzold
// * Realtime Feedback Property
// * 
// * 46    4.03.10 11:09 Merz
// * changes for downsampling
// * 
// * 45    21.10.09 11:51 Merz
// * removed the coefficient arrays from the serialization of the filter
// * property and from the read format info function of the filter buffer
// * 
// * 44    12.10.09 11:12 Merz
// * added new filter types
// * 
// * 43    29.05.09 10:37 Merz
// * added the reference channel name to CMChannelToolProperty
// * 
// * 42    27.05.09 10:23 Merz
// * renamed variable
// * 
// * 41    26.05.09 15:17 Merz
// * removed warning
// * 
// * 40    13.05.09 16:30 Merz
// * changes for the new ChannelTool instrument
// * 
// * 39    5.03.09 15:28 Merz
// * 
// * 43    13.02.09 14:19 Merz
// * 
// * 42    13.02.09 11:44 Merz
// * 
// * 41    11.02.09 14:53 Merz
// * 
// * 40    10.02.09 16:56 Merz
// * 
// * 39    10.02.09 15:39 Merz
// * 
// * 38    22.01.09 14:39 Loeffler
// * Savitzky-Golay filter added
// * 
// * 37    28.11.08 14:29 Merz
// * 
// * 36    25.11.08 10:14 Merz
// * changes for the burst analyzer
// * 
// * 35    25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 34    19.03.07 23:32 Paetzold
// * Bugfix: return of a pointer to a temporary variable "string"
// * 
// * 33    19.03.07 23:24 Paetzold
// * helper functions for unit calculation
// * 
// * 32    14.12.06 16:33 Jesinger
// * removed linux warnings
// * 
// * 31    14.12.06 16:11 Jesinger
// * fix for new directory layout
// * 
// * 30    14.12.06 15:51 Jesinger
// * removed paths from #include statements
// * 
// * 29    15.11.06 14:51 Loeffler
// * - DEBUG_NEW
// * - unnecessary function parameter removed
// * 
// * 28    15.08.06 11:47 Jesinger
// * 
// * 27    15.08.06 11:22 Jesinger
// * changed include name "MCStream..." -> "MC_Stream..."
// * 
// * 26    19.07.06 13:37 Merz
// * several changes for the spike units in the spike analyzer stream
// * 
// * 25    7.07.06 11:12 Merz
// * 
// * 24    22.06.06 15:30 Merz
// * changed type of m_ISI
// * 
// * 23    19.06.06 13:28 Merz
// * added an additional parameter to the spike parameter property
// * 
// * 22    9.06.06 15:15 Merz
// * added structures, classes and functions for the spike analyzer
// * 
// * 21    7.03.06 16:00 Merz
// * changes for files larger than 2 GB
// * 
// * 20    2.02.06 16:33 Merz
// * CMIAnalyzerProperty : changed ReadAnalyzerFormatInfo and added
// * GetRealWorldData and SetTables functions in order to deal with more
// * than 12 parameters
// * added m_SlopePolarity
// * removed histoanalyzer code
// * 
// * 19    19.01.06 12:48 Merz
// * changes for the new calculation of Tmin and Tmax
// * 
// * 18    19.11.03 11:11 Patzwahl
// * added "slope" parameter functionality
// * 
// * 17    24.06.03 10:04 Merz
// * extended CMMEATriggerProperty
// * 
// * 16    2.06.03 16:50 Merz
// * extended trigger property for the parameter trigger
// * 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCSTREAMPROPERTY_H_
#define _MCSTREAMPROPERTY_H_

#include "MCStream.h"

#ifdef _MC_RACK
#include "../StdioFile64.h"
#endif

#include <assert.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

class AnalyzerData
{
public:
	// data which are used for event
	// the types must correspond to the values of CMIAnalyzerProperty.m_FormatTable
	// (MIAnalyzer.cpp: constructor of CMIAnalyzerProperty)
	// CMIAnalyzerPropertyis copied to 
	// CMRBGenericParameter(the to the event corresponding buffer)
	DWORD dwMin;
	DWORD dwMax;
	__int64 i64TMin;
	__int64 i64TMax;
	DWORD  dwHeight;
	DWORDLONG qwWidth;
	DWORD dwAmplitude;
	DWORD dwArea;
	WORD wNumber;
	float fRate;
	float fSlope;
    float fSlope_10_90;
    float fSlope_20_80;
    float fSlope_30_70;

	AnalyzerData() : dwMin(0), dwMax(0), i64TMin(0), i64TMax(0), 
		dwHeight(0), qwWidth(0), dwAmplitude(0), dwArea(0), 
		wNumber(0), fRate(0), fSlope(0), fSlope_10_90(0), fSlope_20_80(0), fSlope_30_70(0) {}

	// some values are set to invalid, in case no events are detected
	void Reset() {dwMin = 0xFFFFFFFF; dwMax = 0xFFFFFFFF; i64TMin = 0; i64TMax = 0; 
		dwHeight = 0xFFFFFFFF; qwWidth = 0; dwAmplitude = 0; 
		dwArea=0; 
		wNumber = 0; fRate = 0; fSlope = 0; fSlope_10_90 = 0; fSlope_20_80 = 0; fSlope_30_70 = 0;}
};

#ifndef AN_NCHOICES
#define AN_NCHOICES 15			// no. of choices in analyzer prop. dialog

enum AnalyzerChoice {
					ac0_MIN, 
					ac1_MAX, 
					ac2_TMIN, 
					ac3_TMAX, 
					ac4_HEIGHT, 
					ac5_WIDTH, 
					ac6_AMPLITUDE, 
					ac7_AREA, 
					ac8_NUMBER, 
					ac9_RATE,
					ac10_SLOPE,
                    ac11_SLOPE_10_90,
                    ac12_SLOPE_20_80,
                    ac13_SLOPE_30_70};

enum SlopePolarity {
                    NEGATIVE,
                    POSITIVE};

				
// only the EN_AN_MEANS analyzer kind is fully implemented
enum en_AnalyzerKind {EN_AN_SIMPLE, EN_AN_MEANS, EN_AN_HISTO, EN_AN_TIMEHISTO, 
						EN_AN_SINGLESPIKE};

#endif

#define NUM_OF_SPIKE_ANALYZER_PARAMS 3	// no. of spike analyzer parameters
#define NUM_OF_BURST_ANALYZER_PARAMS 3	// no. of burst analyzer parameters
#define NUM_OF_SPIKE_UNITS	4			// no. of spike units (includes the value zero which means no unit selected)

enum SpikeAnalyzerChoice {saparam0_ISI, saparam1_RATE, saparam2_TIMESTAMP};

enum BurstAnalyzerChoice {baparam0_DURATION, baparam1_FREQUENCY, baparam2_NUMBER};

enum UnitType {SI_VOLT, SI_SECONDS, SI_TIMESTAMP, SI_TIMEDIFF, SI_VOLTSECONDS, SI_HERTZ, SI_ONE, SI_VOLTPERSECOND, SI_TIMESTAMP_MARKER};

enum SpikeSortMethod {SSM_NOTSELECTED, SSM_SORTWINDOW};
enum SpikeDetectMethod {SDM_THRESHOLD, SDM_SLOPE};
enum SpikeCutOutType {SCO_PREPOST, SCO_LEVEL};



//Following structs and classes (childs of CMCloneObject) are
//used in MCRack and are written - at least in part- to data files
//using sizeof(class) and memcopy.
//This is possible as long these classes and structs do only contain 
//simple types and no pointer or class-members 
//(therefore eg. AnalyzerParams is not written directly).
//To keep downward compatible, do only append member variables!!!!!
//do not delete or change order!!!!!!

class BurstAnalyzerData
{
public:
	BurstAnalyzerData();
	DWORDLONG m_DurationOfBurst;
	int m_NumberOfSpikes;
	float m_SpikeFrequency;
};

class SpikeAnalyzerData
{
public:
	SpikeAnalyzerData();
	DWORDLONG m_ISI;
	float m_Rate;
	DWORDLONG m_TimeStamp;
};

class CUnitType
{
public:	
	int	m_Type;
#ifdef _MC_RACK
	void GetUnitString(CString& s) const;
	void GetUnitString(CString& s,int exponent) const;
	static void GetPreUnitString(CString& s,int exponent);
#else
	void GetUnitString(string& s) const;
	void GetUnitString(string& s,int exponent) const;
	static void GetPreUnitString(string& s,int exponent);
#endif
	int GetBasicExponent() const;
};

struct AnalyzerParams
{
//!!!!!!To keep downward compatible, do only append member variables!!!!!
//!!!!!! do not delete or change order!!!!!!
	float Minimum;		// these are real world values; used for setting the ranges of displays etc.
	float Maximum;
	// change for VC 6.0
	int Enabled;
	double Factor;
	int Exponent;
	CUnitType UType;

#ifdef _MC_RACK
	CString Caption;
#else
	string Caption;
#endif
};

#ifdef _MC_RACK
class CMCloneObject: public CObject
#else
class CMCloneObject
#endif
{
#ifdef _MC_RACK
	DECLARE_DYNCREATE(CMCloneObject)
#endif

public:
	CMCloneObject();
	virtual ~CMCloneObject();

	virtual CMCloneObject* Clone();
};

/////////////////////////////////////////////////////////////////////////////
// CTimeWindowProperty property

class CMTimeWindowProperty: public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMTimeWindowProperty);
#endif

public:
	CMTimeWindowProperty();
#ifdef _MC_RACK
	virtual void Serialize(CArchive& ar);
#endif
	void Reset();

	CMTimeWindowProperty& operator=(const CMTimeWindowProperty& rhs);
	virtual CMCloneObject* Clone();

//	bool WriteTimeWindowFormatInfo(CStdioFile64* pFile);
	bool ReadTimeWindowFormatInfo(char** pInfo, WORD wHdrVersion);


//!!!!!!To keep downward compatible, do only append member variables!!!!!
//!!!!!! do not delete or change order!!!!!!

	int		m_iWindowChoice;		// 0: fixed, 1: start on trigger, 2: start and end on trigger
	float	m_fTime1;				// Time 1 in ms, distance or peritriggertime 1
	float	m_fTime2;				// Time 2 in ms, extent or peritriggertime 2
	WORD	m_wID1;					// Trigger ID 1;
	WORD	m_wID2;					// Trigger ID 2;

#ifdef _MC_RACK
	CString m_csInputBufferID1;
	CString m_csInputBufferID2;
#else
	string m_csInputBufferID1;
	string m_csInputBufferID2;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CMMEATriggerProperty property

class CMMEATriggerProperty: public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMMEATriggerProperty);
#endif

public:
//!!!!!!To keep downward compatible, do only append member variables!!!!!
//!!!!!! do not delete or change order!!!!!!
	int m_iDeadTime;
	
	CMMEATriggerProperty();

#ifdef _MC_RACK
	virtual void Serialize(CArchive& ar);
#endif
	int		m_iTrigger;				// 0=Sweep, 1=Trigger
	int		m_iExtentTrigger;		// Pre trigger Extent in ms
	int		m_iExtent;				// Sweep Extent in ms
	int		m_iLevel;				// Selected trigger Level in 1/10 uV
	int		m_iLevelSuggested;		// Suggested trigger Level in 1/10 uV
	int		m_iSlope;				// 0=positive, 1=negative
	int		m_iChannel;				// Channel for triggering
	int		m_iBuffer;				// Buffer that contains m_iChannel 

	int		m_iLevelDispStyle;		// 0=Don't display, 1=Triangle only, 2=Triangle and line
	int		m_iExtentTrigDispStyle;	// 0=Don't display, 1=Triangle only, 2=Triangle and line
	COLORREF	m_clrLevel;
	COLORREF	m_clrExtentTrig;

	DWORD	m_dwDuration;			// Sampling Duration

	bool m_bDigitalTrigger;			// if true a digital channel is selected
															// if false an analog channel is used
	int m_iDigitalValue;				// Selected Digital value
	int m_iDigitalTriggerType;					// Mask for the digital Input

// DPBufferID: replace m_csBufferID by InputBufferName
// Input Buffer name should be included as m_iBuffer not longer valid

//	char cInputBufferID[8];


#ifdef _MC_RACK
	CString m_csInputBufferID;
#else
	string m_csInputBufferID;
#endif

	int m_iDigitalMask;

	bool m_bParameterTrigger;

	int m_iIndexSelectedParameter;

	bool m_bTrialSynchronization;

#ifdef _MC_RACK
	CString m_csParameterName;
#else
	string m_csParameterName;
#endif

	#ifdef _MC_RACK
	CString m_csParameterUnit;
#else
	string m_csParameterUnit;
#endif


	CMMEATriggerProperty& operator=(const CMMEATriggerProperty& rhs);

	virtual CMCloneObject* Clone();

	bool ReadTriggerFormatInfo(char** pInfo, WORD wHdrVersion);

	static BOOL ReadSpikeFormatInfo(char** pInfo,DWORD dwReadBufferSize,WORD wHeaderVersion,
							void* p_m_ArrTriggerProperty,
							DWORD* pdwDeadTime,DWORD* pdwPreTrigger,DWORD* pdwPostTrigger);

};


// CMSpikeSorterProperty 
// and associated classes CMSpikeUnitInfo and CMSpikeChannelInfo

/////////////////////////////////////////////////////////////////////////////
// CMSpikeSorterProperty


#ifdef _MC_RACK
class CMSpikeUnitInfo : public CMCloneObject
#else
class CMSpikeUnitInfo
#endif
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMSpikeUnitInfo);
#endif

public:
	CMSpikeUnitInfo();
	~CMSpikeUnitInfo();
	CMSpikeUnitInfo& operator=(const CMSpikeUnitInfo& rhs);

#ifdef _MC_RACK
	virtual CMCloneObject* Clone();
	void Serialize(CArchive& ar);
	virtual void AssertValid() const;
#endif

	void SetChannelHWID(WORD wChHWID);
	WORD GetChannelHWID() const;
	void SetUnitID(WORD wUnitID);
	WORD GetUnitID() const;
	void SetWndTime(float fTime);
	float GetWndTime() const;
	void SetWndMin(float fMin);
	float GetWndMin() const;
	void SetWndMax(float fMax);
	float GetWndMax() const;


#ifdef _MC_RACK
	void WriteSpikeUnitFormatInfo(CStdioFile64* pFile);
#endif
	void ReadSpikeUnitFormatInfo(char** pInfo, WORD wHdrVersion);

public:
	float m_fWndMin;			// minimum of the sorting window
	float m_fWndMax;			// maximum of the sorting window
	float m_fWndTime;			// time point of the sorting window relative to trigger
	COLORREF m_clrTrace;	// color of the spike trace
	COLORREF m_clrSortWnd;		// color of the sorting window


private:
	WORD m_wChHWID;
	WORD m_wUnitID;				// ID of the unit
};


typedef std::map <WORD,CMSpikeUnitInfo*> MapSpikeUnitInfo;
typedef MapSpikeUnitInfo::iterator itMapSpikeUnitInfo;
typedef MapSpikeUnitInfo::const_iterator citMapSpikeUnitInfo;

#ifdef _MC_RACK
class CMSpikeChInfo : public CMCloneObject
#else
class CMSpikeChInfo
#endif
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMSpikeChInfo);
#endif

public:
	CMSpikeChInfo();
	~CMSpikeChInfo();
	CMSpikeChInfo& operator=(const CMSpikeChInfo& rhs);

#ifdef _MC_RACK
	virtual CMCloneObject* Clone();
	void Serialize(CArchive& ar);
	virtual void AssertValid() const;
#endif

#ifdef _MC_RACK
	void WriteSpikeChFormatInfo(CStdioFile64* pFile);
#endif
	void ReadSpikeChFormatInfo(char** pInfo, WORD wHdrVersion);

	void SetChannelHWID(WORD wChHWID);
	WORD GetChannelHWID() const;

	void SetChGroupID(WORD wChGroupID);
	WORD GetChGroupID() const;
	void RemoveChGroupID();

	void SetThresholdLevel(float fLevel);
	float GetThresholdLevel() const;
	void SetThresholdSlope(int iSlope);
	int GetThresholdSlope() const;

	void SetSlopeDeltaV(float fDeltaV);
	float GetSlopeDeltaV() const;
	void SetSlopeMin(float fSlopeMin);
	float GetSlopeMin() const;
	void SetSlopeMax(float fSlopeMax);
	float GetSlopeMax() const;

	bool AddSpikeUnitInfo(WORD wUnitID);
	bool RemoveSpikeUnitInfo(WORD wUnitID);
	bool GetSpikeUnitIDs(std::vector<WORD>& arrUnitIDs);

	bool SetSpikeUnitInfo(CMSpikeUnitInfo& UnitInfo);
	CMSpikeUnitInfo* GetSpikeUnitInfo(WORD wUnitID) const;
	int GetSpikeUnitCount() const;

private:
	WORD m_wChHWID;					// the channelHWID
	WORD m_wChGroupID;			// > 0, if the channel belongs to a electrode group (tetrode ...)
													// 
	float m_fThresholdLevel;	// trigger level in [V]
	int		m_iThresholdSlope;	// 0 represents positive slope, 1 negative slope

	float m_fSlopeDeltaV;		// required voltage change [V] for slope detection
	float m_fSlopeMin;			// minimum slope to be accepted as spike [V/s] = [킮/탎]
	float m_fSlopeMax;			// maximum slope to be accepted as spike

	MapSpikeUnitInfo m_mapUnitInfo;
};



typedef std::map <WORD,CMSpikeChInfo*> MapSpikeChInfo;
typedef MapSpikeChInfo::iterator itMapSpikeChInfo;
typedef MapSpikeChInfo::const_iterator citMapSpikeChInfo;

#ifdef _MC_RACK
class CMSpikeProperty : public CMCloneObject
#else
class CMSpikeProperty
#endif
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMSpikeProperty);
#endif

public:
	CMSpikeProperty();
	~CMSpikeProperty();
	CMSpikeProperty& operator=(const CMSpikeProperty& rhs);

#ifdef _MC_RACK
	virtual CMCloneObject* Clone();
	void Serialize(CArchive& ar);
	virtual void AssertValid() const;
#endif

#ifdef _MC_RACK
	void WriteSpikeFormatInfo(CStdioFile64* pFile);
#endif
	bool ReadSpikeFormatInfo(char** pInfo, WORD wHdrVersion);

// access Channel Info
	void SetSpikeChInfo(CMSpikeChInfo& ChInfo);
	CMSpikeChInfo* GetSpikeChInfo(WORD wChHWID) const;
	bool RemoveChannelInfo(WORD wChHWID);
	bool RemoveChannelInfo();

// access Unit info
	/*
	** Add a new spike unit info to each channel
	** @return UnitID
	*/
	bool AddSpikeUnits(WORD wUnitID);
	bool RemoveSpikeUnits(WORD wUnitID);
	bool GetSpikeUnitIDs(std::vector<WORD>& arrUnitIDs);
	bool SetSpikeUnitInfo(CMSpikeUnitInfo& UnitInfo);
	CMSpikeUnitInfo* GetSpikeUnitInfo(WORD wChHWID, WORD wUnitID) const;
	bool InitSpikeUnitWnd(WORD wUnitID, float fWndTime, float fWndMax, float fWndMin);

	void SetSortMethod(SpikeSortMethod sm);
	SpikeSortMethod GetSortMethod() const;
	void SetDetectMethod(SpikeDetectMethod sdm);
	SpikeDetectMethod GetDetectMethod() const;
	void SetCutOutType(SpikeCutOutType SCOType);
	SpikeCutOutType GetCutOutType() const;

	void SetStdDevFactor(float fFactor);
	float GetStdDevFactor() const;
	
	//void SetPreTrigger(float fPreTrigger, DWORD dwTicksPerSample); //normalize to dwTicksPerSample
	//float GetPreTrigger() const;
	//void SetPostTrigger(float fPostTrigger, DWORD dwTicksPerSample);
	//float GetPostTrigger() const;
	//void SetDeadTime(float fDeadTime, DWORD dwTicksPerSample);
	//float GetDeadTime() const;

	//GM use integer values in 탎 instead of floats in sec
	void SetPreTrigger_us(int iPreTrigger);
	int GetPreTrigger_us() const;
	void SetPostTrigger_us(int iPostTrigger);
	int GetPostTrigger_us() const;
	void SetDeadTime_us(int iDeadTime);
	int GetDeadTime_us() const;

	bool AddChannelToGroup(WORD wChHWID, WORD wChGroupID);
	bool RemoveChannelFromGroup(WORD wChHWID);
	bool RemoveChannelGroup(WORD wChGroupID);
	bool GetChannelGroupIDs(std::vector<WORD>& arrChGroupIDs) const;
	bool GetChHWIDsFromGroup(WORD wChGroupID, std::vector<WORD>& arrChHWIDs) const;

#ifdef _MC_RACK
	void SetInputBufferID(const CString& csInputBufferID);
	CString GetInputBufferID() const;
#else
	void SetInputBufferID(const string& csInputBufferID);
	string GetInputBufferID();
#endif

private:
	SpikeSortMethod m_SortMethod;
	SpikeDetectMethod m_DetectMethod;
	SpikeCutOutType m_CutOutType;
	
	float m_fStdDevFactor;

	//GM
	//float m_fPreTrigger;		// pre trigger cut out in [s]
	//float m_fPostTrigger;		// post trigger cut out in [s]
	//float m_fDeadTime;		// dead time between detection in [s]

	int m_iPreTrigger;			// pre trigger cut out in [탎]
	int m_iPostTrigger;			// post trigger cut out in [탎]
	int m_iDeadTime;			// dead time between detection in [탎]

	MapSpikeChInfo m_mapChannelInfo; // ChHWID as key

#ifdef _MC_RACK
	CString m_csInputBufferID;
#else
	string m_csInputBufferID; 
#endif
	friend class CMCSAInfoSpike;
	friend class CMISpikeSorter;
};

///////////////////////////////////////////////////////////////
// CMRealtimeFeedbackProperty

class CMBufferStateMap;

typedef std::map <WORD,WORD> MapStateMap;

class CMRealtimeFeedbackProperty: public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMRealtimeFeedbackProperty);
#endif

public:
	CMRealtimeFeedbackProperty();
	~CMRealtimeFeedbackProperty();
	CMRealtimeFeedbackProperty& operator=(const CMRealtimeFeedbackProperty& rhs);

#ifdef _MC_RACK
	virtual CMCloneObject* Clone();
	void Serialize(CArchive& ar);
	virtual void AssertValid() const;
#endif

	static const int nChannels = 16;

// Filter Page
	BOOL m_onoff;

	int m_RecordFiltered;

	BOOL m_highpass_onoff;
	double m_highpass_frequency;

	BOOL m_lowpass_onoff;
	double m_lowpass_frequency;

	int m_filter_order;

// Logic Page
	int m_PulseLength;
	int m_TimeWindow;
	int m_NumberOfDigitalChannels;
	int m_spikecount[nChannels];
	int m_rate[nChannels];
	int m_andor[nChannels];

	int m_digout[nChannels];

	MapStateMap m_pBufferStates[nChannels];

};
/////////////////////////////////////////////////////////////////////////////
// CMFilterProperty

#define NUM_FILTERS 9

// (HL) FilterNames must correspond to EnFilterTypes
static string FilterNames[NUM_FILTERS] = { "Bessel 2nd order", "Bessel 4th order", "Butterworth 2nd order",
										   "Chebyshev 2nd order 0.5 dB", "Chebyshev 2nd order 1.0 dB", "Chebyshev 2nd order 2.0 dB",
										   "Chebyshev 2nd order 3.0 dB", "Bandstop Resonator", "Savitzky-Golay"};

enum EnFilterTypes {ftBessel_2, ftBessel_4, ftButterworth_2,
					ftChebyshev_0_5dB, ftChebyshev_1dB, ftChebyshev_2dB,
					ftChebyshev_3dB, ftBandstopResonator, ftSG};

#define NUM_BANDSTOP_FREQUENCIES 2
#define NUM_BANDSTOP_Q_FACTORS 6

extern double Bandstop_Frequencies[NUM_BANDSTOP_FREQUENCIES];
extern double Bandstop_Q_Factors[NUM_BANDSTOP_Q_FACTORS];

class CMFilterProperty : public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMFilterProperty);
#endif

public:
	CMFilterProperty();
	CMFilterProperty& operator=(const CMFilterProperty& rhs);

	// these functions only compare the filter names
	static bool IsSavitzkyGolay(const string& FilterName);
	static bool IsIIR(const string& FilterName);

	EnFilterTypes GetFilterType() const;
	static EnFilterTypes GetFilterType(const string& FilterName);


#ifdef _MC_RACK
static void GetDownwsamplingFrequencies(int InputFrequency, CArray<int,int>& arrFrequencies);
#endif

	virtual CMCloneObject* Clone();

#ifdef _MC_RACK
	void Serialize(CArchive& ar);
	virtual void AssertValid() const;
#endif

	BOOL FromFormatInfo(char** pInfo, WORD wHeaderVersion);

	void SetIIRFilter(
		float fLowerCutoff, 
		float fUpperCutoff,
		double dCenterFrequency,
		double dQFactor,
#ifdef _MC_RACK
		CString strFilterName, 
#else
		string strFilterName, 
#endif
		int iPassType);

	bool IsSavitzkyGolayFilter() const;
	bool IsIIRFilter() const;

	int					m_iPassType;		// 0=Undefined, 1=Low Pass, 2=High Pass, 3=Band Pass, 4=Band Stop, 5=All Pass

#ifdef _MC_RACK
	CString				m_strFilterName;

	CStringArray		m_arrParameterNames;
	CStringArray		m_arrUnitNames;
	CArray<float,float>	m_arrParams;

#else
	string				m_strFilterName;

	vector<string> m_arrParameterNames;
	vector<string> m_arrUnitNames;
	vector<float> m_arrParams;
#endif

private:
	double m_CenterFrequency;	// Hz
	double m_Q_Factor;
	bool m_bDownsamplingEnabled;
	int m_iDownsamplingFrequency;

public:
	double GetCenterFrequency() const;
	double GetQFactor() const;
	void SetCenterFrequency(double centerFrequency);
	void SetQFactor(double qFactor);
	bool GetDownsamplingEnabled() const;
	int GetDownsamplingFrequency() const;
	void SetDownsamplingEnabled(bool enable);
	void SetDownsamplingFrequency(int frequency);
	int GetLowerCutoff() const;
	int GetUpperCutoff() const;
	float GetLowerCutoffAsFloat() const;
	float GetUpperCutoffAsFloat() const;
	std::string GetPassTypeAsString() const;
	int GetPassType() const;

    //! these values are for the S-G filter
	struct CSGCoeff
	{
		CSGCoeff();

		std::vector<double> Coeff;

		int Left;
		int Right;
		int Order;
	};

	void SetSGCoeff(const CSGCoeff& coeff);
	CSGCoeff GetSGCoeff() const;

	int GetSGOrder() const;
	int GetSGNumSamples() const;
	int GetSGNumDataPointsLeft() const;

	CSGCoeff SGCoeff;
};

/////////////////////////////////////////////////////////////////////////////
// CMIAnalyzerProperty property

class CMIAnalyzerProperty: public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMIAnalyzerProperty);
#endif
public:
	CMIAnalyzerProperty();

#ifdef _MC_RACK
	virtual void Serialize(CArchive& ar);
#endif

	CMIAnalyzerProperty& operator=(const CMIAnalyzerProperty& rhs);

	virtual CMCloneObject* Clone();

	static BOOL ReadAnalyzerFormatInfo(char** pInfo,DWORD dwReadBufferSize,
									WORD wHeaderVersion, WORD* pwChannelSize,
									CMIAnalyzerProperty* pAnalyzerProperty,
									CMTimeWindowProperty* pTimeWindowProperty,
									int* pPositionTable,AnalyzerParams* pParamTable,
                                    WORD wBits, WORD wZeroAD, double dUnitsPerAD);

    float GetRealWorldData(WORD w, WORD wZeroAD, double dUnitsPerAD) const;
    void SetTables(WORD wBits, WORD wZeroAD, double dUnitsPerAD, int* pPositionTable,AnalyzerParams* pParamTable) const;
    
//	bool WriteAnalyzerFormatInfo(CStdioFile64* pFile);
	int GetChannelSize();	// returns size in bytes of one channel

//!!!!!!To keep downward compatible, do only append member variables!!!!!
//!!!!!! do not delete or change order!!!!!!

	int m_iInputKind;
	en_AnalyzerKind m_AnalyzerKind;
	int m_aiAnalyzerChoice[AN_NCHOICES];

	// could be made static
	int m_FormatTable[AN_NCHOICES];

	// (HL) 22.6. wunschBayer
	int m_iNumTimeWindows;

	// V1.35
	//CString m_strInputBufferName;
#ifdef _MC_RACK
	CString m_strInputBufferName;
#else
	string m_strInputBufferName;
#endif

	// V1.41
	int m_iInputBufferId;

//DPBufferID
// probably not necessary, if necessary adapt also Buffer::OnWriteFormatInfo and ReadAnalyzerFormatInfo
#ifdef _MC_RACK
	CString m_csInputBufferID;
#else
	string m_csInputBufferID;
#endif

    SlopePolarity m_SlopePolarity;

};


/////////////////////////////////////////////////////////////////////////////
// CMGenericEventDataIterator

class AnalyzerData;	
class CMGenericParameterEventDataIterator
{
public:

	CMGenericParameterEventDataIterator();

	CMGenericParameterEventDataIterator
		(WORD wNumChannels,int iDataSizePerChannel,
			char * pData, CMIAnalyzerProperty* pProp, 
			AnalyzerParams* pParms, struct STRMFMT* pFMT, int iHeaderVersion);

	void SetData(AnalyzerData& a);
	void SetWord(WORD w);
	void SetDWord(DWORD dw);
	void SetQuadWord(__int64 dw);
	WORD GetWord() const;
	DWORD GetDWord() const;
	void SetFloat(float f);
	float GetFloat() const;
	__int64 GetQuadWord() const;
	BOOL SetStartPos();
	BOOL Next();
	BOOL NextChannel();
	WORD GetDataSize() const;
	WORD GetState() const;
#ifdef _MC_RACK
	BOOL GetRealWorldData(int iChannel, CArray<float,float>& a);
#else
	BOOL GetRealWorldData(int iChannel, vector<float>& a);
#endif

private:
	char *m_pDataBase;
	char *m_pDataCurrent;

	int m_iState;
	int m_iChannelCount;

	struct STRMFMT*	m_psf;

	AnalyzerParams* m_pParamTable; 
	
	CMIAnalyzerProperty* m_pAnalyzerProperty;

	WORD	m_wNumChannels;
	int m_iDataSizePerChannel;
	int m_iHeaderVersion;
};

inline void CMGenericParameterEventDataIterator::SetWord(WORD w)
{
	*((WORD*)m_pDataCurrent) = w;
}

inline WORD CMGenericParameterEventDataIterator::GetWord() const
{
#ifdef _MC_RACK
	ASSERT(m_iHeaderVersion != -1);
#else
	assert(m_iHeaderVersion != -1);
#endif
	return *((WORD*)m_pDataCurrent);
}

inline void CMGenericParameterEventDataIterator::SetDWord(DWORD dw)
{
	*((DWORD*)m_pDataCurrent) = dw;
}

inline DWORD CMGenericParameterEventDataIterator::GetDWord() const
{
	return *((DWORD*)m_pDataCurrent);
}


inline void CMGenericParameterEventDataIterator::SetFloat(float f)
{
	*((float*)m_pDataCurrent) = f;
}

inline float CMGenericParameterEventDataIterator::GetFloat() const
{
#ifdef _MC_RACK
	ASSERT(m_iHeaderVersion != -1);
#else
	assert(m_iHeaderVersion != -1);
#endif
	return *((float*)m_pDataCurrent);
}


inline void CMGenericParameterEventDataIterator::SetQuadWord(__int64 qw)
{
	*((DWORDLONG*)m_pDataCurrent) = qw;
}

inline __int64 CMGenericParameterEventDataIterator::GetQuadWord() const
{
	return *((__int64*)m_pDataCurrent);
}

inline WORD CMGenericParameterEventDataIterator::GetDataSize() const
{
#ifdef _MC_RACK
	ASSERT(m_iState != -1);
#else
	assert(m_iState != -1);
#endif
	return static_cast<WORD>(m_pAnalyzerProperty->m_FormatTable[m_iState]);
}

/////////////////////////////////////////////////////////////////////////////
// CMEvokedProperty

class CMEvokedProperty : public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMEvokedProperty);
#endif

public:
	CMEvokedProperty();
	virtual ~CMEvokedProperty();
	CMEvokedProperty& operator=(const CMEvokedProperty& rhs);
	virtual CMCloneObject* Clone();
	static BOOL ReadEvokedFormatInfo(char** pInfo,DWORD dwReadBufferSize,WORD wHeaderVersion,
							CMEvokedProperty* pEvokedProperty);

#ifdef _MC_RACK
	void Serialize(CArchive& ar);
	virtual void AssertValid() const;
#endif

//	WORD					m_iNumChannels;
//	WORD*					m_pwOffset;
	CMTimeWindowProperty*	m_pTWProperty;
	WORD					m_iMaxTimeWindowCount;
	BOOL					m_bCalculateSigmaData;

#ifdef _MC_RACK
	CString m_csAveragerTriggerBufferID;
#else
	string m_csAveragerTriggerBufferID;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CMSpikeAnalyzerProperty property

class CMSpikeAnalyzerProperty: public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMSpikeAnalyzerProperty);
#endif
public:
	CMSpikeAnalyzerProperty();
	~CMSpikeAnalyzerProperty();
#ifdef _MC_RACK
	virtual void Serialize(CArchive& ar);
#endif
	CMSpikeAnalyzerProperty& operator=(const CMSpikeAnalyzerProperty& rhs);
	virtual CMCloneObject* Clone();

#ifdef _MC_RACK
	void WriteSpikeParameterFormatInfo(CStdioFile64* pFile);
#endif
	static bool ReadSpikeParameterFormatInfo(char** pInfo, CMSpikeAnalyzerProperty* pSpikeAnalyzerProperty);

	void SetSpikeParamTable();
	BOOL IsParamEnabled(WORD wParamID) const;
	void SetParamEnabled(WORD wParamID, BOOL bEnabled);
	std::vector<AnalyzerParams>	m_arrSpikeParams;
	std::vector<BOOL> m_arrSpikeUnitSelected;
#ifdef _MC_RACK
	CString m_csInputBufferID;
#else
	string m_csInputBufferID;
#endif
	SpikeSortMethod m_SortMethod;
};

/////////////////////////////////////////////////////////////////////////////
// CMBurstAnalyzerProperty property

class CMBurstAnalyzerProperty: public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMBurstAnalyzerProperty);
#endif
public:
	CMBurstAnalyzerProperty();
	~CMBurstAnalyzerProperty();
#ifdef _MC_RACK
	virtual void Serialize(CArchive& ar);
#endif
	CMBurstAnalyzerProperty& operator=(const CMBurstAnalyzerProperty& rhs);
	virtual CMCloneObject* Clone();

#ifdef _MC_RACK
	void WriteBurstParameterFormatInfo(CStdioFile64* pFile);
#endif
	static bool ReadBurstParameterFormatInfo(char** pInfo, CMBurstAnalyzerProperty* pBurstAnalyzerProperty);

	void SetBurstParamTable();
	BOOL IsParamEnabled(WORD wParamID) const;

	void SetParamEnabled(WORD wParamID, BOOL bEnabled);

	std::vector<AnalyzerParams>	m_arrBurstParams;
	std::vector<BOOL> m_arrSpikeUnitSelected;
#ifdef _MC_RACK
	CString m_csInputBufferID;
#else
	string m_csInputBufferID;
#endif
	SpikeSortMethod m_SortMethod;

	int m_iStartBurst;
	int m_iEndBurst;
	int m_iIBI;
	int m_iDurationOfBurst;
	int m_iSpikesInBurst;
};

/////////////////////////////////////////////////////////////////////////////
// CMChannelToolProperty property

class CMChannelToolProperty: public CMCloneObject
{
#ifdef _MC_RACK
	DECLARE_SERIAL(CMChannelToolProperty);
#endif
public:
	CMChannelToolProperty();
	~CMChannelToolProperty();
#ifdef _MC_RACK
	virtual void Serialize(CArchive& ar);
#endif
	CMChannelToolProperty& operator=(const CMChannelToolProperty& rhs);
	virtual CMCloneObject* Clone();

	BOOL FromFormatInfo(char** pInfo);

#ifdef _MC_RACK
	CString m_strInputBufferName;
	CString m_strRefChannelName;
#else
	string m_strInputBufferName;
	string m_strRefChannelName;
#endif
	WORD m_wRefChannelHWID;
};

#endif	// _MCSTREAMPROPERTY_H_
