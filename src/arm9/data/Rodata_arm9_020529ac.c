#include "nitro/types.h"

extern void ClampLengthAndDispatchWrite_0200c810(void);
extern void ClampLengthAndDispatch_0200c7cc(void);
extern void FSi_FindPathCommand_0200c058(void);
extern void FSi_GetPathCommand_0200c26c(void);
extern void FSi_ROMFAT_FindPath_0200c9d4(void);
extern void FSi_ROMFAT_GetArchiveResource_0200cf0c(void);
extern void FSi_ROMFAT_GetPathInfo_0200cde0(void);
extern void FSi_ROMFAT_GetPath_0200ca60(void);
extern void FSi_ROMFAT_OpenFileDirect_0200caec(void);
extern void FSi_ROMFAT_OpenFileFast_0200caa4(void);
extern void FSi_ROMFAT_SeekFile_0200cc90(void);
extern void OpenFileFastCommand_0200c5e8(void);
extern void ReadDirCommand_0200bf2c(void);
extern void ReadDirectoryEntry_0200c8ac(void);
extern void ReadFileCommand_0200c694(void);
extern void SetupFileRequestAndDispatch_0200c854(void);
extern void WriteFileCommand_0200c6c4(void);
extern void func_0200be90(void);
extern void func_0200c670(void);
extern void func_0200c6f4(void);
extern void func_0200cb40(void);
extern void func_0200cb70(void);
extern void func_0200cba4(void);
extern void func_0200cbd8(void);
extern void func_0200cc0c(void);
extern void func_0200cc40(void);
extern void func_0200ccfc(void);
extern void func_0200cd18(void);
extern void func_0200cd34(void);
extern void func_0200cd64(void);
extern void func_0200cd70(void);
extern void func_0200cdc8(void);

void (*const data_020529e0[64])(void) = {
    ClampLengthAndDispatch_0200c7cc,
    ClampLengthAndDispatchWrite_0200c810,
    SetupFileRequestAndDispatch_0200c854,
    ReadDirectoryEntry_0200c8ac,
    FSi_ROMFAT_FindPath_0200c9d4,
    FSi_ROMFAT_GetPath_0200ca60,
    FSi_ROMFAT_OpenFileFast_0200caa4,
    FSi_ROMFAT_OpenFileDirect_0200caec,
    func_0200cb40,
    func_0200cb70,
    func_0200cba4,
    func_0200cbd8,
    func_0200cc0c,
    func_0200cc40,
    FSi_ROMFAT_SeekFile_0200cc90,
    func_0200ccfc,
    func_0200cd18,
    NULL,
    func_0200cd34,
    func_0200cd64,
    NULL,
    NULL,
    NULL,
    FSi_ROMFAT_GetPathInfo_0200cde0,
    NULL,
    NULL,
    NULL,
    NULL,
    FSi_ROMFAT_GetArchiveResource_0200cf0c,
    NULL,
    NULL,
    NULL,
    func_0200cd70,
    func_0200cdc8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

void (*const data_020529ac[13])(void) = {
    ReadFileCommand_0200c694,
    WriteFileCommand_0200c6c4,
    func_0200be90,
    ReadDirCommand_0200bf2c,
    FSi_FindPathCommand_0200c058,
    FSi_GetPathCommand_0200c26c,
    OpenFileFastCommand_0200c5e8,
    func_0200c670,
    func_0200c6f4,
    func_0200c6f4,
    func_0200c6f4,
    func_0200c6f4,
    func_0200c6f4,
};
