#ifndef _WIN32K_CURSORICON_H
#define _WIN32K_CURSORICON_H

#define MAXCURICONHANDLES 4096

typedef struct tagCURICON_PROCESS
{
  LIST_ENTRY ListEntry;
  PPROCESSINFO Process;
} CURICON_PROCESS, *PCURICON_PROCESS;

typedef struct _CURICON_OBJECT
{
  LIST_ENTRY ListEntry;
  HANDLE Self;
  LIST_ENTRY ProcessList;
  HMODULE hModule;
  HRSRC hRsrc;
  HRSRC hGroupRsrc;
  SIZE Size;
  BYTE Shadow;
  ICONINFO IconInfo;
} CURICON_OBJECT, *PCURICON_OBJECT;

typedef struct _CURSORCLIP_INFO
{
  BOOL IsClipped;
  UINT Left;
  UINT Top;
  UINT Right;
  UINT Bottom;
} CURSORCLIP_INFO, *PCURSORCLIP_INFO;

typedef struct _CURSORACCELERATION_INFO
{
    UINT FirstThreshold;
    UINT SecondThreshold;
    UINT Acceleration;
} CURSORACCELERATION_INFO, *PCURSORACCELERATION_INFO;

typedef struct _SYSTEM_CURSORINFO
{
  BOOL Enabled;
  BOOL SwapButtons;//
  UINT ButtonsDown;
  CURSORCLIP_INFO CursorClipInfo;
  PCURICON_OBJECT CurrentCursorObject;
//  UINT WheelScroLines;
//  UINT WheelScroChars;
  BYTE ShowingCursor;
  UINT DblClickSpeed;//
  UINT DblClickWidth;
  UINT DblClickHeight;

  UINT MouseHoverTime;
  UINT MouseHoverWidth;
  UINT MouseHoverHeight;

//  UINT MouseSpeed;
//  CURSORACCELERATION_INFO CursorAccelerationInfo;

  DWORD LastBtnDown;
  LONG LastBtnDownX;
  LONG LastBtnDownY;
  HANDLE LastClkWnd;
  BOOL ScreenSaverRunning;
} SYSTEM_CURSORINFO, *PSYSTEM_CURSORINFO;

HCURSOR FASTCALL IntSetCursor(PWINSTATION_OBJECT WinStaObject, PCURICON_OBJECT NewCursor, BOOL ForceChange);
BOOL FASTCALL IntSetupCurIconHandles(PWINSTATION_OBJECT WinStaObject);
PCURICON_OBJECT FASTCALL IntCreateCurIconHandle(PWINSTATION_OBJECT WinStaObject);
VOID FASTCALL IntCleanupCurIcons(struct _EPROCESS *Process, PPROCESSINFO Win32Process);

BOOL FASTCALL IntGetCursorLocation(PWINSTATION_OBJECT WinStaObject, POINT *loc);

BOOL UserDrawIconEx(HDC hDc, INT xLeft, INT yTop, PCURICON_OBJECT pIcon, INT cxWidth,
   INT cyHeight, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
PCURICON_OBJECT FASTCALL UserGetCurIconObject(HCURSOR hCurIcon);

int APIENTRY UserShowCursor(BOOL bShow);

#define IntGetSysCursorInfo(WinStaObj) \
  (PSYSTEM_CURSORINFO)((WinStaObj)->SystemCursor)

#define IntReleaseCurIconObject(CurIconObj) \
  UserDereferenceObject(CurIconObj)

ULONG
NTAPI
GreSetPointerShape(
    HDC hdc,
    HBITMAP hbmMask,
    HBITMAP hbmColor,
    LONG xHot,
    LONG yHot,
    LONG x,
    LONG y);

VOID
NTAPI
GreMovePointer(
    HDC hdc,
    LONG x,
    LONG y);

#endif /* _WIN32K_CURSORICON_H */

/* EOF */


