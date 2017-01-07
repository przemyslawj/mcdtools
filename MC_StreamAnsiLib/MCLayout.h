/////////////////////////////////////////////////////////////////////////////
//
// MC_Rack
// Copyright (C) 2000 Multi Channel Systems, all rights reserved
//
// $Workfile: MCLayout.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_Rack/IncANSI/MCLayout.h 34    9.09.11 11:59 Merz $
//
// $Modtime: 6.09.11 10:21 $
//
// $Log: /MC_Rack_II/MC_Rack/IncANSI/MCLayout.h $
// * 
// * 34    9.09.11 11:59 Merz
// * support for MEA2100 120 channel systems
// * 
// * 33    20.05.10 14:22 Loeffler
// * interface functions added for display of layout in Replay Page and
// * relative positions
// * 
// * 32    18.05.10 14:19 Loeffler
// * new functions in interface added
// * 
// * 31    3.04.09 11:58 Paetzold
// * Unterscheidung ob nur MEA oder auch DOUBLE MEA Layout erlaubt sind
// * Bug: 0000062
// * 
// * 30    19.03.09 15:08 Paetzold
// * Ergänzungen für Analog Channel Mapping
// * 
// * 29    7.11.08 13:41 Loeffler
// * #define added
// * 
// * 28    6.11.08 12:00 Loeffler
// * change for stdmealayout
// * 
// * 27    6.11.08 10:08 Paetzold
// * StdMeaLayout
// * 
// * 26    6.11.08 9:20 Paetzold
// * 
// * 25    5.11.08 8:34 Paetzold
// * 
// * 24    30.10.08 15:46 Merz
// * changes for amplifier/layout selection
// * 
// * 23    17.10.08 13:21 Loeffler
// * - some const char* changed to string
// * - warning removed
// * 
// * 22    8.09.08 10:42 Paetzold
// * 
// * 21    5.09.08 16:31 Paetzold
// * 
// * 20    5.09.08 16:28 Paetzold
// * 
// * 
// * 2     22-02-01 10:25 Patzwahl
// * checked in for Test Version 1.99.0.0, before merge with 1.65.0.0  (it
// * seems that between 1.65 and 1.67 there was a merge with MC_Rack_I to
// * include the display changes of Michael Wegelin, but there is no label!)
// * 
// * 1     20-07-00 15:28 Patzwahl
// * Initial check in
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _MCLayout_H_
#define _MCLayout_H_

#ifndef _AFX
#include "typedefs.h"
#endif

#include "MCStream.h"

// (HL) eliminate boost security warnings, alternately use #pragma, see cpp file
//#define _SCL_SECURE_NO_WARNINGS		
#include <vector>
#include <string>
#include <map>
//#undef _SCL_SECURE_NO_WARNINGS
using namespace std;


#define MAX_NUM_LAYOUT_CONFIGS 4


/////////////////////////////////////////////////////////////////////////////
// CMCLayout

//class CMInstrument;

class CMCLayout
{
	// Data for each HWID
public:
	class CChannelLayout 
	{
	public:
		int hwid;
		MeaSubType subtype;
		int gain;
		int lowF;
		int highF;
		char name[257];
		char decoratedname[257];
		int meanumber;
		char meaname[257];
		int electype;
		int x;
		int y;
		int z;
		int xextend;
		int yextend;
		int diameter;
		int dx;
		int dy;
		int dxextend;
		int dyextend;
		char pinname[257];
		char amplifiername[257];
		int map_hwid;
		int max_channels;

		CChannelLayout();
		void SetHardwareChannel(WORD HWID,const char* amplifiername,MeaSubType type,int gain,int lowF,int highF);
		void SetChannelName(const char* name,const char* decoratedname, const char* pinname);
		void SetLayoutChannel(const char* name,const char* decoratedname, const char* pinname, int meanumber,const char* meaname,int type,
			int x,int y,int z,int xextend,int yextend,int diameter,
			int dx,int dy,int dxextend,int dyextend);
		void SetMapHWID(int map_hwid, int max_channels);
		string BuildNameString(int mea) const;

		static int getSize(int version);
		void WriteLayout(FILE* file);
		bool ReadLayout(FILE* file,int version);
	};

	class CType
	{
	public:
		virtual ~CType(){};

		string m_name;

		vector<int> m_offsets;
		vector<CChannelLayout> m_channels;

		virtual int ReadLayout(const char* filename) = 0;
	};

	class CHardware: public CType
	{
	public:
		CHardware();
		virtual ~CHardware(){};
		virtual int ReadLayout(const char* filename);
		std::map<int, int> GetLayoutConfig() const;
		int GetStdMeaLayouts() const;
	private:
		std::map<int, int> m_LayoutConfig;
		int m_StdMeaLayouts;
	};

	class CAmplifier: public CType
	{
	public:
		virtual ~CAmplifier(){};
		virtual int ReadLayout(const char* filename);
	};

	class CMea: public CType
	{
	public:
		virtual ~CMea(){};
		virtual int ReadLayout(const char* filename);
	};

	class CLayoutSelection
	{
	public:
		int typeindex;
		int offsetindex;
		CLayoutSelection(){typeindex=0;offsetindex=0;};
		CLayoutSelection(int ti,int oi){typeindex=ti;offsetindex=oi;};
	};

	typedef vector<string> StringArray;

	class CAvailTypes : public vector<CType*>
	{
	public:
		virtual ~CAvailTypes();
		virtual void LoadAvail(const string& path) = 0;

		string GetAvailType(int typeindex) const;
		int GetAvailTypeIndex(const char* type) const;
		void GetAvailTypes(StringArray& types);
		string GetAvailOffsetAsString(int typeindex,int offsetindex) const;
		int GetAvailOffsetAsInt(int typeindex,int offsetindex) const;
		int GetAvailOffsetIndex(int typeindex,int offset) const;
		void GetAvailOffsets(int typeindex,StringArray& offsets) const;
		int GetNumberOfAvailOffsets(int typeindex) const;
		std::map<int, int> GetHwLayoutConfig(int typeindex) const;
		int GetStdMeaLayout(int typeindex) const;
	};

	class CAvailHard: public CAvailTypes
	{
		virtual void LoadAvail(const string& path);
	};

	class CAvailAmpl: public CAvailTypes
	{
		virtual void LoadAvail(const string& path);
	};

	class CAvailMeas: public CAvailTypes
	{
		virtual void LoadAvail(const string& path);
	};

	class CConfiguration : public vector<CLayoutSelection>
	{
	private:
		CAvailTypes* m_avail;
	public:
		CConfiguration(CAvailTypes* avail);

		const CAvailTypes* GetAvail() const{return m_avail;};
		CAvailTypes* GetAvail();

		int GetNumberOfLayouts() const;
		void AddNewType(int meaindex,int offsetindex);
		void ChangeType(int index,int meaindex);
		void ChangeTypeOffset(int index, int offsetindex);
		void RemoveType(int index);
		void RemoveAll();
		void MoveType(int index,int direction);
		int GetSelectedTypeIndex(int index);
		string GetSelectedType(int index) const;
		int GetSelectedOffsetIndex(int index) const;
		string GetSelectedOffsetAsString(int index) const;
		int GetSelectedOffsetAsInt(int index);
		void GetSelectedTypes(StringArray& meas);

#ifdef _MC_RACK
		void	SerializeConfig(CArchive& ar);
#endif
	};

public:
	CMCLayout();
	virtual ~CMCLayout();

	UINT	GetCount() const;
	UINT	GetElectrodeChannelCount() const { return m_iElec; }
	UINT	GetElectrodeChannelCount(int meanumber) const;
	UINT	GetAnalogChannelCount() const { return m_iAnlg; }
	UINT	GetDigitalChannelCount() const { return m_iDigi; }
	UINT	GetCheckChannelCount() const { return m_iCheck; }
	void	GetElectrodePoint(UINT iChHWID,int& x, int& y, int& z) const;
	void	GetElectrodeExtends(UINT iChHWID,int& extendx, int& extendy, int& diameter) const;
	void	GetElectrodeDisplayPoint(UINT iChHWID,int& dx, int& dy) const;
	void	GetElectrodeDisplayExtend(UINT iChHWID,int& dxextend, int& dyextend) const;
	string	GetElectrodeName(UINT iChHWID) const;
	string	GetElectrodeNameEx(UINT iChHWID,int mea) const;
	void	GetElectrodeFrequency(UINT iChHWID,int& lowF,int& highF) const;

	//! Get  hardware ID from electrode name 
	/*! return true if found
	 */
	bool GetHWIDFromName(const char* name, WORD* pHWID) const;
	void GetElectrodeNames(StringArray& rNames) const;
	void GetElectrodeNamesEx(StringArray& rNames,int mea) const;
	string GetDecoratedElectrodeName(UINT iChHWID) const;
	void GetDecoratedElectrodeNames(StringArray& rNames) const;
	MeaSourceType GetLayoutType() const { return m_iLayoutType; }
	int GetMeaNumber(WORD HWID) const;
	string GetMeaName(WORD HWID) const;
	MeaSubType GetMeaSubType(WORD HWID) const;
	string GetMeaSubTypeAsString(WORD HWID) const;
	bool IsConnected(WORD HWID) const;
	bool IsAvail(WORD HWID) const;
	int GetGain(WORD HWID) const;
	int GetElectrodeType(WORD HWID) const;

	string GetAmplifierName(WORD HWID) const;

	//! Get number of configured amplifiers (1 - 4) for individual MEA layout
	/*! 
	*/
	int GetNumberOfConfigAmps() const;
	string GetNameOfConfigAmp(int MeaIndex) const;
	int GetNumberOfConfigMEAs() const;
	string GetNameOfConfigMEA(int MeaIndex) const;

	//! get channel layout of channel with HWID
	/*! \param HWID hardware ID 
	 */
	CChannelLayout GetChannelLayout(WORD HWID) const;

	void GetMaxDisplayExtend(int MeaIndex, MeaSubType subtype, int& x, int& y) const;

	//! Get x channel position in a range from 0 (left) to 100 (right)
	/*! \param Index the channel index
	 * \attention this might not be the same as the relative position from the stream if not
	 * all channels of the MEA are in the stream
	 */
	int GetRelativeChannelPosX(int MeaIndex, WORD HWID) const;

	//! Get y channel position in a range from 0 (top) to 100 (bottom)
	/*! \param Index the channel index
	 * \attention this might not be the same as the relative position from the layout if not
	 * all channels of the MEA are in the stream
	 */
	int GetRelativeChannelPosY(int MeaIndex, WORD HWID) const;

	void WriteLayout(FILE* file);
	bool ReadLayout(FILE* file);

	static CMCLayout* GetMEALayout();
	const CConfiguration* GetMeaConfig() const;
	CConfiguration* GetMeaConfig();
	const CConfiguration* GetAmplConfig() const;
	CConfiguration* GetAmplConfig();
	const CConfiguration* GetHwConfig() const;
	CConfiguration* GetHwConfig();

	void InitLayoutIfNeeded(MeaSourceType iLayoutType, UINT iTotal, UINT iElec,
								   UINT iAnlg, UINT iDigi, bool onlysize = false);

	void SetHardwareChannel(WORD HWID,MeaSubType subtype,const char* amplifiername,int gain,int lowF,int highF);
	void SetLayoutChannel(WORD HWID,const char* name,const char* decoratedname,const char* pinname,int meanumber,const char* meaname,int electype,
		int x,int y,int z,int xextend,int yextend,int diameter,
		int dx,int dy,int dxextend,int dyextend); 
	void SetMapHWID(WORD HWID,int map_hwid, int max_channels);
	void SetLayoutChannel(int offset,const CChannelLayout& chlayout);

	int GetNumberOfElectrodeChannels(const string& amplifiername) const;

private:
	MeaSourceType	m_iLayoutType;
	int m_iTotal;
	UINT				m_iElec;
	UINT				m_iAnlg;
	UINT				m_iDigi;
	UINT				m_iCheck;
	
	static CMCLayout		MEALayout;

	vector<CChannelLayout>  m_ChannelList;

	// available Hardware
	CAvailHard m_availhard;

	// available Amplifiers
	CAvailAmpl m_availampl;

	// available Meas
	CAvailMeas m_availmeas;

    // current configuration (hardware)
	CConfiguration m_hw_configuration;

	// current configuration (amplifier)
	CConfiguration m_ampl_configuration;

	// current configuration (meas)
	CConfiguration m_mea_configuration;

	// helper functions to recreate data source setup structure
	int GetNumberOfMEAs() const;
	int GetTotalNumberOfAmps() const;
	int GetNumberOfAmps(const vector<CChannelLayout>& chLayouts) const;
	int GetNumberOfAmpsForMEA(int MeaIndex) const;
	vector<int> GetMEAIndices() const;
	int GetNumberOfMEAIndices() const;
	string GetAmplifierNameForMEA(int MeaIndex) const;
	vector<CChannelLayout> GetChannelLayoutsForMea(int MeaIndex) const;

	void GetMaxChannelPos(int meanumber, MeaSubType subtype, int& x, int& y) const;

};

#endif	// _MCLayout_H_

/////////////////////////////////////////////////////////////////////////////
