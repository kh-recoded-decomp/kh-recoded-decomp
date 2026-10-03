#include "nitro/types.h"

extern int LookupTableOffset_02069dd8(int index, int offset);
extern s32 SetRecordFlagBit_02069bc8(void *flagSets, s32 recordId, BOOL value, BOOL usePrimary);

s32 SetRecordFlagFromTable_02069cd4(void *flagSets, int index, int offset, BOOL value, BOOL usePrimary)
{
    return SetRecordFlagBit_02069bc8(flagSets, LookupTableOffset_02069dd8(index, offset), value, usePrimary);
}
