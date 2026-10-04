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
    u8 pad_00[0xc];
} PackedFileView;

typedef struct {
    int threshold;
    u32 handle;
} RewardEntry;

typedef struct {
    u8 pad_0000[0x150];
    TextFrame frames[6];
    u8 pad_01b0[0xcf1c - 0x1b0];
    PackedFileView views[4];
    u8 pad_cf4c[0xd1a4 - 0xcf4c];
    int skipEntries;
    u8 pad_d1a8[0xd1b8 - 0xd1a8];
    int unlockedCount;
    u8 pad_d1bc[0xd1d0 - 0xd1bc];
    int rewardState;
} SceneWork;

extern RewardEntry data_ov093_020c3f74[8];
extern char data_ov093_020c4d6c[];
extern char data_ov093_020c4d84[];

extern BOOL IsEntryFlagSet_020c22a4(int flagSet, int entryIndex);
extern void SetEntryFlag_020c22d4(int flagSet, int entryIndex);
extern void ClearEntryFlag_020c22f8(int flagSet, int entryIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void func_ov093_020c231c(int state, SceneWork *work);
extern void *func_ov027_020ba2a8(PackedFileView *view, int index);
extern u32 func_0202b788(void);
extern void *OS_SNPrintf_0202e080(char *dst, unsigned int len, const char *fmt, ...);
extern void func_ov093_020c3c18(int x, int y, char *text, int charBase);
extern BOOL func_ov093_020c3c24(void);

void RunEntryUnlockSequence_020c23a8(SceneWork *work)
{
    char text[0x200];
    TextFrame *frame;
    void *name;
    void *label;
    int charBase;
    int found;
    int last;
    int i;
    int j;

    switch (work->rewardState) {
    case 0:
        if (work->skipEntries != 0) {
            work->rewardState++;
            return;
        }
        work->unlockedCount = 0;
        for (i = 0; i < 30; i++) {
            if (IsEntryFlagSet_020c22a4(0, i)) {
                work->unlockedCount++;
            }
        }
        last = -1;
        for (i = 0; i < 8; i++) {
            if (work->unlockedCount >= data_ov093_020c3f74[i].threshold) {
                last = i;
            }
        }
        if (last != -1) {
            for (j = 0; j <= last; j++) {
                if (!IsEntryFlagSet_020c22a4(2, j)) {
                    SetEntryFlag_020c22d4(3, j);
                }
            }
        }
        for (i = 0; i < 30; i++) {
            if (IsEntryFlagSet_020c22a4(0, i)) {
                SetGlobalPackedBit_02027320(i + 0xf1a);
            }
        }
        func_ov093_020c231c(3, work);
        break;
    case 1:
        for (i = 0; i < 30; i++) {
            if (IsEntryFlagSet_020c22a4(1, i)) {
                found = i;
                ClearEntryFlag_020c22f8(1, i);
                SetEntryFlag_020c22d4(0, i);
                break;
            }
        }
        frame = &work->frames[5];
        charBase = frame->charBase + frame->width * frame->height * 2;
        name = func_ov027_020ba2a8(&work->views[1], found);
        label = func_ov027_020ba2a8(&work->views[0], 3);
        if (func_0202b788() == 1) {
            OS_SNPrintf_0202e080(text, 0x100, data_ov093_020c4d6c, label, name, func_ov027_020ba2a8(&work->views[0], 1));
        } else {
            OS_SNPrintf_0202e080(text, 0x100, data_ov093_020c4d84, name, label);
        }
        func_ov093_020c3c18(0x80, 0x60, text, charBase);
        work->rewardState++;
        break;
    case 2:
        if (!func_ov093_020c3c24()) {
            work->rewardState = 0;
        }
        break;
    }
}


