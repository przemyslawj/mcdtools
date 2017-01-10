/////////////////////////////////////////////////////////////////////////////
//
// MC_Stream
// Copyright (C) 2002 Multi Channel Systems, all rights reserved
//
// $Workfile: typedefs.h $
//
// Description:
//
// $Header: /MC_Rack_II/MC_StreamANSI/typedefs.h 7     16.02.09 9:50 Paetzold $
//
// $Modtime: 16.02.09 9:20 $
//
// $Log: /MC_Rack_II/MC_StreamANSI/typedefs.h $
// * 
// * 7     16.02.09 9:50 Paetzold
// * 
// * 6     4.11.08 15:06 Loeffler
// * use windows.h instead of typedefs.h if _WIN32 is defined
// * 
// * 5     25.01.08 9:18 Paetzold
// * Removed warnings
// * adjustments for 64bit Linux
// * 
// * 4     2.06.03 11:03 Patzwahl
// * added HANDLE and LPVOID defines in order to avoid windows.h in the
// * neuroshare DLL project.
// * 
// * 3     10.04.03 9:19 Patzwahl
// * started with a docu, and changes for compiling under linux 
// * 
// * 2     5-06-02 17:45 Patzwahl
// * added Source Safe header
/////////////////////////////////////////////////////////////////////////////

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#ifdef _WIN32
#include <windows.h>
#endif

typedef void* HANDLE;
typedef void* LPVOID;


#define FALSE   0
#define TRUE    1

#ifndef NULL
#define NULL 0
#endif

#ifndef CONST
#define CONST               const
#endif

#ifndef _WIN32
#define __int64 long long
#endif

typedef unsigned __int64 ULONGLONG;
typedef ULONGLONG		DWORDLONG;
typedef unsigned short  WORD;
typedef int             BOOL;
#ifndef _WIN32
typedef unsigned int    DWORD;
#else
typedef unsigned long    DWORD;
#endif
typedef __int64			LONGLONG;

typedef unsigned int	UINT;
typedef const char*		LPCTSTR;
typedef unsigned char	BYTE;

typedef struct IDispatch*	LPDISPATCH;

typedef DWORD   COLORREF;
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef struct _GUID {          // size is 16
    DWORD Data1;
    WORD   Data2;
    WORD   Data3;
    BYTE  Data4[8];
} GUID;

#endif

#ifndef _WIN32

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;


typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

BOOL
FileTimeToSystemTime(
    CONST FILETIME *lpFileTime,
    LPSYSTEMTIME lpSystemTime
    );
#endif


#endif
