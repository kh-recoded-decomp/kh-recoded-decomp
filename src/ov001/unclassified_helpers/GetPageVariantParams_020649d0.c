#include "nitro/types.h"

typedef struct {
    s16 value;
    u8 paramA;
    u8 paramB;
} PageVariant;

typedef struct {
    u16 id;
    PageVariant primary[3];
    PageVariant secondary[3];
} PageEntry;

extern PageEntry *GetPageTableEntry_02052124(u32 index);
extern int func_ov001_02064574(int bitOffset, int bitCount);

BOOL GetPageVariantParams_020649d0(u32 index, int *outValue, u32 *outParamA, u32 *outParamB, BOOL usePrimary)
{
    PageEntry *entry = GetPageTableEntry_02052124(index);
    int slot;

    if (entry == NULL)
    {
        return FALSE;
    }
    slot = func_ov001_02064574(index * 2 + 0x9f7, 2);
    if (slot == 3)
    {
        return FALSE;
    }
    if (usePrimary)
    {
        *outValue = entry->primary[slot].value;
        *outParamA = entry->primary[slot].paramA;
        *outParamB = entry->primary[slot].paramB;
    }
    else
    {
        *outValue = entry->secondary[slot].value;
        *outParamA = entry->secondary[slot].paramA;
        *outParamB = entry->secondary[slot].paramB;
    }
    return TRUE;
}
