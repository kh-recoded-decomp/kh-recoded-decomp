#include "nitro/types.h"

typedef struct GaugeContext {
    u8 pad_000[0x6c];
    u32 archive;
    u8 pad_070[0x474 - 0x70];
    s16 displayedLevel;
    u16 gauge;
    u32 isMaxed;
    u8 pad_47c[0x4];
    u32 flags;
} GaugeContext;

typedef struct GaugeGlobals {
    u32 unk_00;
    GaugeContext *context;
} GaugeGlobals;

typedef struct LevelFileTable {
    u32 fileIds[4];
} LevelFileTable;

typedef struct LevelThresholdTable {
    s32 values[5];
} LevelThresholdTable;

extern GaugeGlobals data_ov001_020a04c4;
extern LevelFileTable data_ov001_0209dc1c;
extern LevelThresholdTable data_ov001_0209dcf8;

extern u32 func_ov001_02064784(void);
extern u32 IsSessionFlagSet(u32 id);
extern int GetPartySize(void);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern u32 func_ov001_02077bcc(void);
extern void SetFieldMenuMode(int id);
extern void *Archive_LoadFile(u32 fileId, u32 mode);
extern void func_ov001_0206efac(GaugeContext *context, void *file);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void *QueueFileLoadRequest(u32 path, int loadMode, void (*callback)(void *, void *), void *userData);
extern void ApplyFieldResourceAndRelease(void *request, void *userData);
extern void SelectSlotTitleLine(GaugeContext *context, int slot);
extern void func_ov001_0207b520(void);
extern void ResetGaugeDisplay(void);
extern void func_ov001_0206ed8c(u32 value);

#define LEVEL_FILE(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void AddGaugePoints(int delta, BOOL loadNow)
{
    GaugeContext *context = data_ov001_020a04c4.context;
    LevelFileTable files = data_ov001_0209dc1c;
    LevelThresholdTable thresholds = data_ov001_0209dcf8;
    int maxLevel;
    int level;
    int slot;
    int value;
    int limit;
    int i;
    void *file;
    u32 menuState;

    if (func_ov001_02064784() == 0 && IsSessionFlagSet(0x3708) != 0) {
        return;
    }
    maxLevel = GetPartySize();
    if (IsFieldFlag13OrSessionFlagSet()) {
        value = context->gauge + delta;
        context->gauge = value > 0xce4 ? 0xce4 : value < 0 ? 0 : value;
        if (context->gauge == 0xce4) {
            level = 4;
            context->isMaxed = 1;
        } else {
            level = 3;
        }
        slot = 3;
        maxLevel = 4;
    } else {
        limit = thresholds.values[maxLevel];
        value = context->gauge + delta;
        context->gauge = value > limit ? limit : value < 0 ? 0 : value;
        if (context->gauge == 0x283c) {
            level = 4;
            context->isMaxed = 1;
        } else if (context->gauge >= 7000) {
            level = 3;
        } else if (context->gauge >= 0xf3c) {
            level = 2;
        } else if (context->gauge >= 1000) {
            level = 1;
        } else {
            level = 0;
        }
        if (level > maxLevel - 1) {
            slot = maxLevel - 1;
        } else if (level < 0) {
            slot = 0;
        } else {
            slot = level;
        }
    }

    if (context->displayedLevel == -1) {
        if (context->gauge == thresholds.values[maxLevel]) {
            context->flags |= 0x10000;
            menuState = func_ov001_02077bcc();
            if (menuState == 0 || menuState == 7) {
                SetFieldMenuMode(0xd);
            }
        }
    } else if (level == maxLevel && context->displayedLevel != maxLevel) {
        context->flags |= 0x10000;
        menuState = func_ov001_02077bcc();
        if (menuState == 0 || menuState == 7) {
            SetFieldMenuMode(0xd);
        }
    }

    if (IsFieldFlag13OrSessionFlagSet()) {
        if (context->displayedLevel == -1) {
            context->flags |= 0x8000;
            if (loadNow) {
                context->displayedLevel = slot;
                file = Archive_LoadFile(LEVEL_FILE(context->archive, files.fileIds[3]), 0xe);
                func_ov001_0206efac(context, file);
                NNSi_FndFreeFromDefaultHeap(file);
            } else {
                QueueFileLoadRequest(LEVEL_FILE(context->archive, files.fileIds[3]), 1, ApplyFieldResourceAndRelease, NULL);
            }
            if (context->gauge == 0xce4) {
                context->flags |= 0x10000;
                menuState = func_ov001_02077bcc();
                if (menuState == 0 || menuState == 7) {
                    SetFieldMenuMode(0xd);
                }
            }
        } else if (context->gauge == 0) {
            ResetGaugeDisplay();
        } else {
            func_ov001_0206ed8c(context->gauge);
        }
    } else if (context->displayedLevel != maxLevel && context->displayedLevel != slot) {
        if (slot < context->displayedLevel) {
            ResetGaugeDisplay();
            return;
        }
        if (context->displayedLevel != -1 && slot > 0) {
            context->gauge = thresholds.values[slot] + (thresholds.values[slot + 1] - thresholds.values[slot]) / 2;
        }
        if (slot - context->displayedLevel > 0 && context->displayedLevel != -1) {
            SelectSlotTitleLine(context, slot);
        }
        i = context->displayedLevel;
        if (i < 0) {
            i = 0;
        }
        for (; i < slot; i++) {
            func_ov001_0207b520();
        }
        context->flags |= 0x8000;
        if (loadNow) {
            context->displayedLevel = slot;
            file = Archive_LoadFile(LEVEL_FILE(context->archive, files.fileIds[slot]), 0xe);
            func_ov001_0206efac(context, file);
            NNSi_FndFreeFromDefaultHeap(file);
        } else {
            QueueFileLoadRequest(LEVEL_FILE(context->archive, files.fileIds[slot]), 1, ApplyFieldResourceAndRelease, NULL);
        }
    } else {
        func_ov001_0206ed8c(context->gauge);
    }
    context->displayedLevel = slot;
}
