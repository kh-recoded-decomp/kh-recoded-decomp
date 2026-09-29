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

extern GaugeGlobals data_ov001_020a04a4;
extern LevelFileTable data_ov001_0209dbf4;
extern LevelThresholdTable data_ov001_0209dcd0;

extern u32 func_ov001_02064784(void);
extern u32 func_ov001_020645c8(u32 id);
extern int func_ov001_0207b590(void);
extern BOOL func_ov001_020728e4(void);
extern u32 func_ov001_02077bcc(void);
extern void func_ov001_020781a4(int id);
extern void *func_0202c478(u32 fileId, u32 mode);
extern void func_ov001_0206efac(GaugeContext *context, void *file);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void *QueueFileLoadRequest_020ba114(u32 path, int loadMode, void (*callback)(void *, void *), void *userData);
extern void func_ov001_0206f040(void *request, void *userData);
extern void SelectSlotTitleLine_0206ff9c(GaugeContext *context, int slot);
extern void func_ov001_0207b4f8(void);
extern void func_ov001_020734f8(void);
extern void BlendIconTiles_0206ed8c(u32 value);

#define LEVEL_FILE(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void AddGaugePoints_02073074(int delta, BOOL loadNow)
{
    GaugeContext *context = data_ov001_020a04a4.context;
    LevelFileTable files = data_ov001_0209dbf4;
    LevelThresholdTable thresholds = data_ov001_0209dcd0;
    int maxLevel;
    int level;
    int slot;
    int value;
    int limit;
    int i;
    void *file;
    u32 menuState;

    if (func_ov001_02064784() == 0 && func_ov001_020645c8(0x3708) != 0) {
        return;
    }
    maxLevel = func_ov001_0207b590();
    if (func_ov001_020728e4()) {
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
                func_ov001_020781a4(0xd);
            }
        }
    } else if (level == maxLevel && context->displayedLevel != maxLevel) {
        context->flags |= 0x10000;
        menuState = func_ov001_02077bcc();
        if (menuState == 0 || menuState == 7) {
            func_ov001_020781a4(0xd);
        }
    }

    if (func_ov001_020728e4()) {
        if (context->displayedLevel == -1) {
            context->flags |= 0x8000;
            if (loadNow) {
                context->displayedLevel = slot;
                file = func_0202c478(LEVEL_FILE(context->archive, files.fileIds[3]), 0xe);
                func_ov001_0206efac(context, file);
                NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
            } else {
                QueueFileLoadRequest_020ba114(LEVEL_FILE(context->archive, files.fileIds[3]), 1, func_ov001_0206f040, NULL);
            }
            if (context->gauge == 0xce4) {
                context->flags |= 0x10000;
                menuState = func_ov001_02077bcc();
                if (menuState == 0 || menuState == 7) {
                    func_ov001_020781a4(0xd);
                }
            }
        } else if (context->gauge == 0) {
            func_ov001_020734f8();
        } else {
            BlendIconTiles_0206ed8c(context->gauge);
        }
    } else if (context->displayedLevel != maxLevel && context->displayedLevel != slot) {
        if (slot < context->displayedLevel) {
            func_ov001_020734f8();
            return;
        }
        if (context->displayedLevel != -1 && slot > 0) {
            context->gauge = thresholds.values[slot] + (thresholds.values[slot + 1] - thresholds.values[slot]) / 2;
        }
        if (slot - context->displayedLevel > 0 && context->displayedLevel != -1) {
            SelectSlotTitleLine_0206ff9c(context, slot);
        }
        i = context->displayedLevel;
        if (i < 0) {
            i = 0;
        }
        for (; i < slot; i++) {
            func_ov001_0207b4f8();
        }
        context->flags |= 0x8000;
        if (loadNow) {
            context->displayedLevel = slot;
            file = func_0202c478(LEVEL_FILE(context->archive, files.fileIds[slot]), 0xe);
            func_ov001_0206efac(context, file);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
        } else {
            QueueFileLoadRequest_020ba114(LEVEL_FILE(context->archive, files.fileIds[slot]), 1, func_ov001_0206f040, NULL);
        }
    } else {
        BlendIconTiles_0206ed8c(context->gauge);
    }
    context->displayedLevel = slot;
}
