/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSAChannel.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSAChannel.h 15    20.05.10 14:21 Loeffler $
//
// $Modtime: 20.05.10 11:16 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSAChannel.h $
// * 
// * 15    20.05.10 14:21 Loeffler
// * functions made const
// * 
// * 14    4.09.09 16:40 Paetzold
// * modified include positions
// * 
// * 13    8.05.08 15:01 Paetzold
// * 
// * 12    16.01.07 11:23 Paetzold
// * Added cloning of Reference Channel
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
// * 8     23.04.06 22:43 Paetzold
// * Update for Merge
// * 
// * 7     9.12.03 13:16 Merz
// * added the function GetGain
// * 
// * 6     22.09.03 15:42 Merz
// * changes for double mea layout
// * 
// * 5     2.06.03 11:57 Patzwahl
// * added SetChId method
// * 
// * 4     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 3     24.03.03 11:03 Patzwahl
// * added GroupID functionality
// * 
// * 2     5-06-02 17:04 Patzwahl
// * added Source Save header
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the Channel object
 */

#ifndef _MCSAChannel_H_
#define _MCSAChannel_H_

#ifdef _WIN32
#include <windows.h>
#else
#include "typedefs.h"
#endif

#include <stdio.h>

struct REFHDR;
struct CHNNLHDR;


//! Retrieve channel information
/*! Retrieve channel relevant information of a given data stream.
Example of reading some channel info of the data stream m_MCSStream.
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

class CMCSAChannel
{
public:
	CMCSAChannel();
	CMCSAChannel* Clone();
	virtual ~CMCSAChannel();

public:

//! Get the channel header version
/*!	 
 * \return header version.
*/
	virtual short GetHeaderVersion();

//! Get channel ID
/*! A channel has two IDs, the channel hardware ID (chHWID), and the channel ID (chID).
		The chHWID corresponds to the input connector pin number, the chID corresponds to the
		buffer offset. The chID of a channel can change depending on the number of channels in a buffer.
		It is an index into the multiplexed data array.
 * \return channel ID (index into data array).
*/
	virtual long GetID();

//! Get channel hardware ID
/*! A channel has two IDs, the channel hardware ID (chHWID), and the channel ID (chID).
		The chHWID corresponds to the input connector pin number, the chID corresponds to the
		buffer offset. The chHWID is fixed.
 * \return channel hardware ID.
*/
	virtual long GetHWID();

//! Get channel name
/*! The channel name is the identifier used by the user. For a linear channel
		layout it corresponds to the chHWID, for the MEA layout it correspons to the
		electrode position within the MEA. 
 * \return name of the channel.
*/
	virtual char* GetName();
    //! Get unique channel name
    /*!
    * the result only differs for files which were recorded with a double MEA layout. The Channel names
    * are then appended by 'A' for the first 60 channels or 'B' for channels 64 to 124
    * \return name of the channel
    */
	virtual char* GetDecoratedName();

	virtual char* GetComment();

//! Get group ID of a channel
/*! Channels can be combined into groups (stereotodes, tetrodes, ...). 
		If the group ID is > 0, the channel is part of a channel group, with
		the group ID. All channels have to be retrieved to build the groups.
 * \return
			<ul>
			<li> group ID = 0: channel is not a member of a group. </li>
			<li> group ID > 0: channel is member of group "ID". </li>
			</ul>
*/
	virtual long GetGroupID();


	void SetChID(long lChID);



//! This method is deprecated
/*
*/
	virtual long GetReferenceCount();

//! This method is deprecated
/*
*/
	virtual long GetRefBufferID(long Index);

//! This method is deprecated
/*
*/
	virtual long GetRefChannelID(long Index);

	virtual long GetGain() const;
	virtual long GetPosX() const;
	virtual long GetPosY() const;
	virtual long GetPosZ() const;
	virtual long GetExtendX() const;
	virtual long GetExtendY() const;
	virtual long GetDiameter() const;
	virtual long GetDisplayX() const;
	virtual long GetDisplayY() const;
	virtual long GetDisplayExtendX() const;
	virtual long GetDisplayExtendY() const;
	virtual long GetLowF() const;
	virtual long GetHighF() const;

	enum		{readOK, readSkipped, readError};
	virtual int	ReadHdr(FILE* pFile, WORD wMCSHdrVersion);
	int WriteHdr(FILE* pFile);
	int GetHdrSize();

private:
	REFHDR**	m_pReferences;
	DWORDLONG	m_qwChnnlHdrSize;
	CHNNLHDR*	m_pChnnlHdr;
};

/////////////////////////////////////////////////////////////////////////////
#endif	// _MCSAChannel_H_
