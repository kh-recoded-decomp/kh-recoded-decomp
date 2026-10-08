#include "nitro/types.h"

#define FormatString OS_SPrintf
#define RetainOrInitializeSharedRecord SND_RegisterSeq
#define SetResourceAccessMode func_0202c6a4
#define SelectResourceTable IndexedPointer_GetFirstWord
#define ClearFast MIi_CpuClearFast
#define GetResourceEntry NestedPointer_GetFirstWord

extern int data_ov035_020bc500;
extern char sOv041_RpgUiLanguagePZ_020cf958[];
extern void FormatString(char *dst, const char *fmt, ...);
extern void *RetainOrInitializeSharedRecord(char *name, int kind);
extern void SetResourceAccessMode(int mode);
extern void *AcquireOrRefreshResourceBlock(void *info, void *dst, int flag);
extern void SelectResourceTable(void *base, int kind);
extern void *GetResourceEntry(void *base, int kind, int index);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void ClearFast(int value, void *dst, u32 size);
extern void SetSlotKeyAndRebind(void *slot, void *key, int flag);
extern void ReleaseSharedRecordSlot(void *info);
extern void RegisterSessionCallback(int callback);

typedef struct SlotGroup {
    u8 *slots;
    u8 count;
    u8 pad_05[3];
} SlotGroup;

typedef struct SlotGroupWork {
    u8 pad_000[0x314];
    SlotGroup groups[4];
} SlotGroupWork;

void InitSlotGroups(void)
{
    SlotGroupWork *work;
    void *base;
    void *info;
    int groupIndex;
    int index;
    char name[32];

    work = *(SlotGroupWork **)(data_ov035_020bc500 + 0xb8);
    FormatString(name, sOv041_RpgUiLanguagePZ_020cf958);
    info = RetainOrInitializeSharedRecord(name, 0x12);
    groupIndex = 0;
    SetResourceAccessMode(0);
    base = AcquireOrRefreshResourceBlock(info, NULL, 1);
    SetResourceAccessMode(1);
    SelectResourceTable(base, 7);
    do {
        work->groups[groupIndex].count = 3;
        if (groupIndex == 3) {
            work->groups[groupIndex].count = 9;
        }
        work->groups[groupIndex].slots = NNSi_FndAllocFromDefaultHeap(
            work->groups[groupIndex].count * 0x34);
        ClearFast(0, work->groups[groupIndex].slots,
                  work->groups[groupIndex].count * 0x34);
        for (index = 0; index < work->groups[groupIndex].count; index++) {
            SetSlotKeyAndRebind(
                work->groups[groupIndex].slots + index * 0x34,
                GetResourceEntry(base, 7, groupIndex), 0);
        }
        groupIndex++;
    } while (groupIndex < 4);
    ReleaseSharedRecordSlot(info);
    RegisterSessionCallback(0x20bdb75);
}
