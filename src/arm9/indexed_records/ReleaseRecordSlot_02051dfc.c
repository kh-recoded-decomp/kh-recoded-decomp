#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u8 refCounts[14];
} RecordManager;

extern RecordManager *g_recordManager_020613d0;

extern void FreeRecordSlotPair0_02051af0(void);
extern void FreeRecordSlotPair1_02051b10(void);
extern void FreeRecordSlotPair2_02051b30(void);
extern void FreeRecordSlotPair3_02051b50(void);
extern void FreeRecordSlot4_02051b70(void);
extern void FreeRecordSlot5_02051b88(void);
extern void FreeRecordSlot6_02051ba0(void);
extern void FreeRecordSlot7_02051bb8(void);
extern void FreeRecordSlot8_02051bd0(void);
extern void ReleaseRecordTableA_02051be8(void);
extern void ReleaseRecordTableB_02051c00(void);
extern void ReleaseRecordTableC_02051c20(void);
extern void ReleaseRecordTableD_02051c40(void);
extern void ReleaseRecordTableE_02051c68(void);

/* Drops a record slot's reference count. */
BOOL ReleaseRecordSlot_02051dfc(s32 slot)
{
    RecordManager *manager = g_recordManager_020613d0;

    if (manager->refCounts[slot] == 0) {
        return FALSE;
    }
    manager->refCounts[slot]--;
    if (manager->refCounts[slot] != 0) {
        return TRUE;
    }
    switch (slot) {
    case 0:
        FreeRecordSlotPair0_02051af0();
        break;
    case 1:
        FreeRecordSlotPair1_02051b10();
        break;
    case 2:
        FreeRecordSlotPair2_02051b30();
        break;
    case 3:
        FreeRecordSlot4_02051b70();
        break;
    case 4:
        FreeRecordSlot5_02051b88();
        break;
    case 5:
        FreeRecordSlot6_02051ba0();
        break;
    case 6:
        FreeRecordSlot7_02051bb8();
        break;
    case 7:
        FreeRecordSlot8_02051bd0();
        break;
    case 8:
        ReleaseRecordTableA_02051be8();
        break;
    case 9:
        ReleaseRecordTableB_02051c00();
        break;
    case 10:
        ReleaseRecordTableC_02051c20();
        break;
    case 11:
        ReleaseRecordTableD_02051c40();
        break;
    case 12:
        ReleaseRecordTableE_02051c68();
        break;
    case 13:
        FreeRecordSlotPair3_02051b50();
        break;
    }
    return TRUE;
}
