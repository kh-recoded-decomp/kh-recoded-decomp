#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct {
    u8 pad_00[0x14];
    int nameId;
} RecordB;

typedef struct {
    u8 pad_00[0xc];
} PackedFileView;

typedef struct {
    int itemId;
    u32 handle;
} RewardEntry;

typedef struct {
    u8 pad_0000[0x150];
    TextFrame frames[6];
    u8 pad_01b0[0xcf1c - 0x1b0];
    PackedFileView views[4];
    u8 pad_cf4c[0xd1ac - 0xcf4c];
    int skipRewards;
    u8 pad_d1b0[0xd1d0 - 0xd1b0];
    int rewardState;
} SceneWork;

extern RewardEntry data_ov093_020c3f94[8];
extern char data_ov093_020c4dd4[];
extern char data_ov093_020c4df4[];
extern char data_ov093_020c4db4[];
extern char data_ov093_020c4e10[];

extern BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex);
extern void SetEntryFlag_020c22f4(int flagSet, int entryIndex);
extern void ClearEntryFlag(int flagSet, int entryIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void SetSceneState(int state, SceneWork *work);
extern RecordB *GetRecordTableBEntry(s32 index);
extern void *func_ov027_020ba2c8(PackedFileView *view, int index);
extern u32 GetLanguageIndex(void);
extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);
extern s32 SetSharedFlagBits(u32 handle);
extern void func_ov093_020c3c38(int x, int y, char *text, int charBase);
extern BOOL func_ov093_020c3c44(void);

void RunRewardUnlockSequence(SceneWork *work)
{
    char text[0x200];
    int found;
    RewardEntry *entry;
    void *label;
    void *prefix;
    RecordB *record;
    int nameId;
    u32 handle;
    int charBase;
    PackedFileView *views;
    void *suffix;
    TextFrame *frame;
    int i;
    int slot;

    switch (work->rewardState) {
    case 0:
        if (work->skipRewards != 0) {
            work->rewardState++;
            return;
        }
        for (i = 0; i < 30; i++) {
            if (IsEntryFlagSet_020c22c4(2, i)) {
                SetGlobalPackedBit(i + 0xf3c);
            }
        }
        SetSceneState(4, work);
        break;
    case 1:
        for (slot = 0; slot < 8; slot++) {
            if (IsEntryFlagSet_020c22c4(3, slot)) {
                found = slot;
                ClearEntryFlag(3, slot);
                SetEntryFlag_020c22f4(2, slot);
                SetGlobalPackedBit(slot + 0xf3c);
                break;
            }
        }
        entry = &data_ov093_020c3f94[found];
        frame = &work->frames[5];
        charBase = frame->charBase + frame->width * frame->height * 2;
        handle = entry->handle;
        record = GetRecordTableBEntry(handle);
        views = &work->views[0];
        label = func_ov027_020ba2c8(views, 4);
        prefix = func_ov027_020ba2c8(views, 5);
        nameId = record->nameId;
        suffix = func_ov027_020ba2c8(views, 6);
        switch (GetLanguageIndex()) {
        case 3:
            OS_SNPrintf_0202e094(text, 0x100, data_ov093_020c4db4, label, entry->itemId, prefix, nameId, suffix);
            break;
        case 1:
            OS_SNPrintf_0202e094(text, 0x100, data_ov093_020c4dd4, label, entry->itemId, prefix, nameId, suffix);
            break;
        case 5:
            OS_SNPrintf_0202e094(text, 0x100, data_ov093_020c4df4, label, entry->itemId, prefix, nameId, suffix);
            break;
        case 4:
            OS_SNPrintf_0202e094(text, 0x100, data_ov093_020c4db4, label, entry->itemId, prefix, nameId, suffix);
            break;
        case 2:
            OS_SNPrintf_0202e094(text, 0x100, data_ov093_020c4db4, label, entry->itemId, prefix, nameId, suffix);
            break;
        default:
            OS_SNPrintf_0202e094(text, 0x100, data_ov093_020c4e10, label, entry->itemId, prefix, nameId, suffix);
            break;
        }
        SetSharedFlagBits(handle);
        func_ov093_020c3c38(0x80, 0x60, text, charBase);
        work->rewardState++;
        break;
    case 2:
        if (!func_ov093_020c3c44()) {
            work->rewardState = 0;
        }
        break;
    }
}
