/////////////////////////////////////////////////////////////////////////////
//
// MC_Rack
// Copyright (C) 2010-2012 Multi Channel Systems, all rights reserved
//
// $Workfile: MMea21StimulatorProperty.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_Rack/IncANSI/MMea21StimulatorProperty.h 15    4.12.12 10:12 Merz $
//
// $Modtime: 28.11.12 10:43 $
//
// $Log: /MC_Rack_II/MC_Rack/IncANSI/MMea21StimulatorProperty.h $
// * 
// * 15    4.12.12 10:12 Merz
// * dedicated stimulation electrodes
// * 
// * 14    13.09.12 9:44 Paetzold
// * changes for linux
// * 
// * 13    22.08.12 9:21 Merz
// * added a parameter to SetModeAndDefaults
// * 
// * 12    26.06.12 13:24 Merz
// * 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MMea21StimulatorProperty_H
#define _MMea21StimulatorProperty_H

#ifndef _AFX
#include "typedefs.h"
#endif

#include "MCStream.h"
#include <map>
#include <string>
#include <vector>

const int MANUAL_TRIGGER_BUFFER_ID = -2;
const int START_TRIGGER_BUFFER_ID = -3;

const int NumberOfMea21Stimuli = 3;

enum EnMea21StimulusMode {VoltageMode, CurrentMode};
enum EnMea21RepeatMode {ContinuousMode, DiscontinuousMode};
enum EnTriggerType {Software, Hardware};

/////////////////////////////////////////////////////////////////////////////
// CMMea21StimulatorProperty property

typedef std::map<std::string, std::map<WORD, WORD> > StimulationStates_Type;
typedef std::pair<std::string, StimulationStates_Type> ListModeEntry_Type;

class CMMea21StimulatorProperty
{
public:
	CMMea21StimulatorProperty();
	virtual ~CMMea21StimulatorProperty();

	static CMMea21StimulatorProperty* GetMea21StimulatorProperty();

#ifdef _MC_RACK
	void WriteProperty(FILE* file);
#endif
	bool ReadProperty(FILE* file);

#ifdef _MC_RACK
	void Serialize(CArchive& ar);
#endif
	CMMea21StimulatorProperty& operator=(const CMMea21StimulatorProperty& rhs);

	class CStimulus
	{
	public:
		CStimulus();
		int m_iPre;
		int m_iA1;
		int m_iT1;
		int m_iA2;
		int m_iT2;
		int m_iIPI;
		int m_iPulseRepeat;
		int m_iIBI;
		int m_iBurstRepeat;
		EnMea21RepeatMode m_RepeatMode;
	};

	class CStimulusTrigger
	{
	public:
		CStimulusTrigger();
		CStimulusTrigger(EnTriggerType type, int source);
		bool operator==(const CStimulusTrigger& rhs) const;
		EnTriggerType Type;
		int Source;
	};

private:
	bool m_bListMode;
	std::vector<ListModeEntry_Type> ListModeEntries;

	CStimulus m_Stimulus[NumberOfMea21Stimuli];
	CStimulusTrigger m_Trigger[NumberOfMea21Stimuli];

	int m_iVoltageRangeInMicroVolt;
	int m_iVoltageResolutionInMicroVolt;
	int m_iCurrentRangeInNanoAmp;
	int m_iCurrentResolutionInNanoAmp;
	unsigned int m_uiDacResolution;
	int m_iDacOffset;
	int m_iChannelNumber;
	int m_iSyncNumber;
	int m_iTriggerNumber;

	EnMea21StimulusMode m_Mode;
	bool m_bBlanking;
	bool m_bAPS;

	bool m_bUseAsciiFile;
	std::string m_strAsciiPathFileName;

	bool m_bDedicatedStimulationElectrodes;

public:
	std::vector<ListModeEntry_Type>& GetListModeEntries();

	bool GetListMode() const;

	int GetPre(int i) const;
	int GetA1(int i) const;
	int GetT1(int i) const;
	int GetA2(int i) const;
	int GetT2(int i) const;
	int GetIPI(int i) const;
	int GetPulseRepeat(int i) const;
	int GetIBI(int index) const ;
	int GetBurstRepeat(int i) const;
	EnMea21RepeatMode GetRepeatMode(int i) const;

	const CStimulusTrigger& GetStimulusTrigger(int i) const;
	EnTriggerType GetTriggerType(int i) const;
	int GetTriggerSource(int i) const;

	int GetVoltageRangeInMicroVolt() const;
	int GetVoltageResolutionInMicroVolt() const;
	int GetCurrentRangeInNanoAmp() const;
	int GetCurrentResolutionInNanoAmp() const;
	unsigned int GetDacResolution() const;
	int GetDacOffset() const;
	int GetChannelNumber() const;
	int GetSyncNumber() const ;
	int GetTriggerNumber()const;

	EnMea21StimulusMode GetMode() const;
	bool GetBlanking() const;
	bool GetAPS() const;
	bool GetDedicatedStimulationElectrodes() const;

	bool GetUseAsciiFile() const;
	std::string GetAsciiPathFileName() const;

	void SetListMode(bool listMode);

	void SetModeAndDefaults(EnMea21StimulusMode Mode, bool SetAllDefaults);
	void SetBlanking(bool bBlanking);
	void SetAPS(bool bAPS);
	void SetDedicatedStimulationElectrodes(bool bDedicatedStimulationElectrodes);

	void SetPre(int i, int iPre);
	void SetA1(int i, int iA1);
	void SetT1(int i, int iT1);
	void SetA2(int i, int iA2);
	void SetT2(int i, int iT2);
	void SetIPI(int i, int iIPI);
	void SetPulseRepeat(int i, int iPulseRepeat);
	void SetIBI(int i, int iIBI);
	void SetBurstRepeat(int i, int iBurstRepeat);
	void SetRepeatMode(int i, EnMea21RepeatMode repeatMode);

	void SetStimulusTrigger(int i, const CStimulusTrigger* Trigger);
	void SetTriggerType(int i, EnTriggerType Type);
	void SetTriggerSource(int i, int Source);

	void SetVoltageRangeInMicroVolt(int VoltageRangeInMicroVolt);
	void SetVoltageResolutionInMicroVolt(int VoltageResolutionInMicroVolt);
	void SetCurrentRangeInNanoAmp(int CurrentRangeInNanoAmp);
	void SetCurrentResolutionInNanoAmp(int CurrentResolutionInNanoAmp);
	void SetDacResolution(unsigned int DacResolution);
	void SetDacOffset(int DacOffset);
	void SetChannelNumber(int ChannelNumber);
	void SetSyncNumber(int SyncNumber);
	void SetTriggerNumber(int TriggerNumber);

	void SetUseAsciiFile(bool bUseAsciiFile);
	void SetAsciiPathFileName(const std::string& strAsciiPathFileName);

private:
	static CMMea21StimulatorProperty Mea21StimulatorProperty;
};

#endif	// _MMea21StimulatorProperty_H

/////////////////////////////////////////////////////////////////////////////