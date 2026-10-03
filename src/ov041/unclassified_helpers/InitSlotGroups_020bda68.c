#include "nitro/types.h"

extern int data_ov035_020bc4e0;
extern char data_ov041_020cf938[];
extern void OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *RetainOrInitializeSharedRecord_0202c80c(char *name, int kind);
extern void func_0202c690(int mode);
extern void *func_0202c940(void *info, void *dst, int flag);
extern void func_0202d3c8(void *base, int kind);
extern void *func_0202d3e0(void *base, int kind, int index);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(int value, void *dst, u32 size);
extern void SetSlotKeyAndRebind_0206a94c(void *slot, void *key, int flag);
extern void ReleaseSharedRecordSlot_0202c8a8(void *info);
extern void RegisterSessionCallback_0206c704(int callback);

typedef struct {
    u8 *slots;
    u8 count;
    u8 pad_05[3];
} SlotGroup;

typedef struct {
    u8 pad_000[0x314];
    SlotGroup groups[4];
} Work;

void InitSlotGroups_020bda68(void) {
    Work *work;
    void *base;
    void *info;
    int groupIndex;
    int index;
    char name[32];

    work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    OS_SPrintf_02002428(name, data_ov041_020cf938);
    info = RetainOrInitializeSharedRecord_0202c80c(name, 0x12);
    groupIndex = 0;
    func_0202c690(0);
    base = func_0202c940(info, NULL, 1);
    func_0202c690(1);
    func_0202d3c8(base, 7);
    do {
        work->groups[groupIndex].count = 3;
        if (groupIndex == 3) {
            work->groups[groupIndex].count = 9;
        }
        work->groups[groupIndex].slots = NNSi_FndAllocFromDefaultHeap_0202a178(work->groups[groupIndex].count * 0x34);
        func_01ff8740(0, work->groups[groupIndex].slots, work->groups[groupIndex].count * 0x34);
        for (index = 0; index < work->groups[groupIndex].count; index++) {
            SetSlotKeyAndRebind_0206a94c(work->groups[groupIndex].slots + index * 0x34,
                                         func_0202d3e0(base, 7, groupIndex), 0);
        }
        groupIndex++;
    } while (groupIndex < 4);
    ReleaseSharedRecordSlot_0202c8a8(info);
    RegisterSessionCallback_0206c704(0x20bdb55);
}