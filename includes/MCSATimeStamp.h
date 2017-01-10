/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: MCSATimeStamp.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/MCSATimeStamp.h 5     23.10.09 11:04 Paetzold $
//
// $Modtime: 23.10.09 10:53 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/MCSATimeStamp.h $
// * 
// * 5     23.10.09 11:04 Paetzold
// * 
// * 4     4.09.09 16:31 Paetzold
// * Added local time calculation
// * 
// * 3     15.12.06 15:50 Loeffler
// * docu changes
// * 
// * 2     5-06-02 17:43 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

/*! \file
 \brief interface to the TimeStamp object
 */

#ifndef _MCSATIMESTAMP_H_
#define _MCSATIMESTAMP_H_

#ifdef _WIN32
#include <windows.h>
#else
#include "typedefs.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCSATimeStamp

//! time stamp class
/*! used e.g. for getting time stamps of data samples or to retrieve data in a time interval
*/
class CMCSATimeStamp
{
public:
    CMCSATimeStamp();

    // Attributes
public:

    // Operations
public:
    CMCSATimeStamp& operator=(const CMCSATimeStamp& evt);
    virtual ~CMCSATimeStamp();

public:
    //! Get year
    short GetYear();
    //! Get month (0 - 12)
    short GetMonth();
    //! Get day (0 - 31)
    short GetDay();
    //! Get hour (0 - 24)
    short GetHour();
    //! Get minute (0 - 59)
    short GetMinute();
    //! Get second (0 - 59)
    short GetSecond();
    //! Get millisecond (0 - 1000)
    short GetMillisecond();
    //! get microsecond (0 - 1000)
    short GetMicrosecond();
    //! get nanosecond
    short GetNanosecond();
    //! Seconds of time difference from recording start time
    long GetSecondFromStart();
    //! milliseconds of time difference from recording start time
    short GetMillisecondFromStart();
    //! micro of time difference from recording start time
    short GetMicrosecondFromStart();
    //! nanoseconds of time difference from recording start time
    short GetNanosecondFromStart();
    void SetMillisecondFromStart(short sMilli);
    void SetMicrosecondFromStart(short sMicro);
    void SetNanosecondFromStart(short sNano);
    void SetSecondFromStart(long sSecond);
    //! make a copy of the time stamp
    /*! this reserves memory for the new object which must be destroyed by the application
    */
    CMCSATimeStamp* Clone();
#ifdef _WIN32
	CMCSATimeStamp* AsCachedLocal();
#endif

    DWORDLONG GetTimeStamp() const;
    void SetTimeStamp(DWORDLONG qwTimeStamp);
    DWORDLONG GetStart() const;
    void SetStart(DWORDLONG qwStart);
public:
    DWORDLONG		m_qwTimeStamp;
    DWORDLONG		m_qwStart;
    BOOL			m_bTimeCached;

private:
    void			CacheTime();
    SYSTEMTIME		m_st;
};

/////////////////////////////////////////////////////////////////////////////
#endif
