#include "nitro/types.h"

typedef struct {
    u16 unk_0;
    u16 count;
} EntryInfo;

typedef struct {
    u8 pad_000[0x1d4];
    EntryInfo *info;
} ManagerEntry;

typedef struct {
    u8 unk_0 : 4;
    u8 bit4 : 1;
    u8 unk_5 : 3;
} SessionStateFlags;

typedef struct {
    u8 pad_0000[0x27b6];
    SessionStateFlags stateFlags;
} Session;

extern Session *data_ov001_020a0480;
extern s32 func_ov001_02063a38(void);
extern int func_ov042_020bd39c(void);
extern ManagerEntry *GetBoundedEntryField(int index);
extern void ClearSessionPackedBit(int bitOffset);
extern void func_ov001_020645dc(int bitOffset);

BOOL func_ov001_020656d4(void)
{
    if (func_ov001_02063a38() == 4 && func_ov042_020bd39c() > 0)
    {
        if (GetBoundedEntryField(0)->info->count == 0)
        {
            ClearSessionPackedBit(0x3525);
            data_ov001_020a0480->stateFlags.bit4 = FALSE;
            func_ov001_020645dc(0x3637);
        }
        return FALSE;
    }
    return TRUE;
}
