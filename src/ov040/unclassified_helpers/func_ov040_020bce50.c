#include "nitro/types.h"

typedef struct SlotEntry {
    u8 unk_00;
    u8 state : 7;
    u8 active : 1;
    u8 pad_02[0x1A];
} SlotEntry;

typedef struct SlotTable {
    u8 pad_00[2];
    u8 count;
    s8 unk_03;
    s8 selectedIndex;
    u8 pad_05[0x10 - 0x05];
    SlotEntry *slots;
} SlotTable;

typedef struct FieldState {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x1C - 0x08];
    s8 unk_1C;
    u8 pad_1D[0x21 - 0x1D];
    s8 pendingAction;
    u8 pad_22[2];
    u16 flags24;
    s16 actionParam;
    u8 pad_28[0x40 - 0x28];
    SlotTable slotTable;
    u8 pad_54[0x85 - 0x54];
    u8 bufferActive;
    u8 pad_86[2];
    u8 buffer[0x30];
} FieldState;

typedef struct OverlayState {
    u8 pad_000[0x13C];
    u16 flags;
    u8 pad_13E[0x148 - 0x13E];
    void *task;
} OverlayState;

typedef struct SessionFlags {
    u8 unk_0 : 5;
    u8 bit5 : 1;
    u8 unk_6 : 2;
} SessionFlags;

typedef struct Session {
    u8 pad_0000[0x27B6];
    SessionFlags flags;
} Session;

typedef struct TaskArgs {
    int unk_00;
    int heap;
    int unk_08;
} TaskArgs;

typedef struct PartyMember {
    u8 pad_00[0x7D];
    u8 kind;
} PartyMember;

extern FieldState *data_ov035_020bc4e0;
extern OverlayState *data_ov040_020be260;
extern Session *data_ov001_020a0460;
extern u8 data_ov021_020b52a0[];

extern void func_ov001_0207d120(u16 value);
extern int func_0202a158(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern s32 func_ov001_02063a6c(void);
extern void func_ov021_020af57c(int value, int mode);
extern void func_ov021_020af7b8(void);
extern void ResumeTaskAndClearFlags_02066780(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_0206e444(int value);
extern void func_ov001_0206c2f8(int value);
extern void func_ov035_020bb334(int stopSeq);
extern void func_ov040_020bc838(void);
extern void func_ov040_020bc970(void);
extern int func_ov001_0207f018(void);
extern PartyMember *func_ov001_0207f028(int index);
extern void func_ov007_020a1b18(PartyMember *member, u8 value);
extern int func_ov035_020bafb4(void);
extern int func_ov001_02087214(int value);
extern void func_ov019_020a3608(int value);
extern void StoreToGlobalPtr4Field28_0202a778(int value);
extern void func_ov001_02087fd4(void);
extern void func_ov046_020c0e38(void *buffer);
extern void func_01ff86fc(int value, void *dst, u32 size);
extern void func_ov001_02087e80(u16 groupIndex, s32 value);
extern void func_ov001_02087e34(s16 value);
extern void func_ov001_02087f00(int value);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern int func_ov031_020bb054(int value);
extern void func_ov021_020a75d8(u32 entry, u16 value);
extern void func_ov040_020bc81c(int slot);
extern void func_ov001_02087ed0(void);
extern void func_ov001_0207ef40(int value);
extern void func_ov035_020bc1f0(int index, int arg1, int arg2);
extern void func_ov001_02072ec8(void);
extern void func_ov001_02064184(int value, int mode);
extern void func_ov001_02087628(int enable);

int func_ov040_020bce50(void)
{
    FieldState *state;
    SlotTable *slotTable;
    TaskArgs args;
    PartyMember *member;
    SlotEntry *slot;
    int index;
    int count;

    state = data_ov035_020bc4e0;
    func_ov001_0207d120(0x10);
    {
        TaskArgs temp;
        int heap = func_0202a158();
        temp.unk_00 = 0;
        temp.heap = heap;
        temp.unk_08 = 0;
        args = temp;
    }
    data_ov040_020be260->task = func_0202a448(data_ov021_020b52a0, &args);
    func_ov021_020af57c(func_ov001_02063a6c(), 0);
    if (data_ov001_020a0460->flags.bit5) {
        func_ov021_020af7b8();
        data_ov001_020a0460->flags.bit5 = 0;
    }
    ResumeTaskAndClearFlags_02066780();
    if (!func_ov001_020645c8(0x3309) && state->unk_1C != 3) {
        func_ov001_0206e444(0);
    }
    state->flags |= 0xC;
    if (state->unk_1C == -1) {
        state->flags &= ~0x20;
    }
    index = 0;
    func_ov001_0206c2f8(0);
    if (data_ov040_020be260->flags & 1) {
        func_ov035_020bb334(1);
        func_ov040_020bc838();
        func_ov040_020bc970();
        slotTable = &data_ov035_020bc4e0->slotTable;
        count = (s8)func_ov001_0207f018();
        slotTable->selectedIndex = -1;
        for (; index < count; index++) {
            member = func_ov001_0207f028(index);
            if (member != NULL && member->kind == 5) {
                slotTable->selectedIndex = index;
            }
        }
        if (slotTable->selectedIndex >= 0) {
            func_ov007_020a1b18(func_ov001_0207f028(slotTable->selectedIndex), slotTable->count);
        }
        if (func_ov035_020bafb4() >= 0) {
            func_ov019_020a3608(func_ov001_02087214(func_ov035_020bafb4()));
        }
        StoreToGlobalPtr4Field28_0202a778(0);
    } else {
        func_ov035_020bb334(0);
        func_ov001_02087fd4();
        if (state->bufferActive) {
            func_ov046_020c0e38(state->buffer);
            func_01ff86fc(0, state->buffer, sizeof(state->buffer));
            state->bufferActive = 0;
        }
        state->flags &= ~0x80;
        if (state->pendingAction == 1) {
            func_ov001_02087e80(state->actionParam, 0x5A000);
        } else if (state->pendingAction == 2) {
            func_ov001_02087e34(state->actionParam);
        } else if (state->pendingAction == 3) {
            state->flags |= 0x10;
        }
        func_ov001_02087f00(1);
        state->pendingAction = 0;
        state->flags24 |= 0x10;
        state->actionParam = -1;
        func_ov021_020a75d8(GetBoundedEntryField_0206db5c(0), func_ov031_020bb054(0));
    }
    for (index = 0; index < state->slotTable.count; index++) {
        slot = &state->slotTable.slots[index];
        slot->state = 4;
        func_ov040_020bc81c((s8)index);
        if (slot->state != 0) {
            slot->active = 1;
        }
    }
    func_ov001_02087ed0();
    func_ov001_0207ef40(0);
    for (index = 0; index < 3; index++) {
        func_ov035_020bc1f0(index, 0, 0);
    }
    func_ov001_02072ec8();
    data_ov040_020be260->flags &= ~1;
    if (!func_ov001_020645c8(0x3308)) {
        func_ov001_02064184(0, -1);
    }
    func_ov001_02087628(0);
    data_ov040_020be260->flags |= 0x8000;
    return 4;
}
