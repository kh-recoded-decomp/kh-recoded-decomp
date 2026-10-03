#include "nitro/types.h"

typedef struct {
    u32 values[4];
} LevelTable4;

typedef struct {
    u32 values[5];
} LevelTable5;

typedef struct {
    u8 pad_000[0x6c];
    u32 vramBase;
    u8 pad_070[0x404];
    s16 level;
    u16 titleId;
    s32 titleShown;
    u8 pad_47C[0x4];
    u32 flags;
} LevelContext;

typedef struct {
    u32 unk_00;
    LevelContext *context;
} LevelContextHandle;

extern LevelContextHandle data_ov001_020a04a4;
extern const LevelTable4 data_ov001_0209dc64;
extern const LevelTable4 data_ov001_0209dc84;
extern const LevelTable5 data_ov001_0209dca8;

extern BOOL func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(int bitId);
extern BOOL func_ov001_020728e4(void);
extern void func_ov001_0206ed8c(u16 titleId);
extern int func_ov001_0207b590(void);
extern int func_ov001_02077bcc(void);
extern void SetFieldMenuMode_020781a4(int mode);
extern void SelectSlotTitleLine_0206ff9c(LevelContext *context, int slot);
extern void func_ov001_0207b4f8(void);
extern void func_ov001_0206f040(void);
extern void func_ov027_020ba114(u32 params, int count, void (*callback)(void), int arg);

void AdvanceMenuLevel_02073388(int step) {
    LevelContext *context = data_ov001_020a04a4.context;
    LevelTable4 paletteIds = data_ov001_0209dc64;
    LevelTable4 titleIds = data_ov001_0209dc84;
    LevelTable5 finalTitleIds = data_ov001_0209dca8;
    int count;
    int level;
    int slot;
    int i;

    if (!func_ov001_02064784() && func_ov001_020645c8(0x3708)) {
        return;
    }
    if (func_ov001_020728e4()) {
        context->titleId = 0xce4;
        context->level = 4;
        context->titleShown = 1;
        context->flags |= 0x10000;
        func_ov001_0206ed8c(context->titleId);
        return;
    }
    count = func_ov001_0207b590();
    level = context->level + step;
    if (count <= level) {
        level = count;
    }
    slot = count - 1;
    if (slot > level) {
        slot = level;
    }
    if (level <= 0) {
        return;
    }
    if (level == count) {
        context->titleId = finalTitleIds.values[level];
    } else {
        context->titleId = titleIds.values[level - 1];
    }
    if (level == count && context->level != count) {
        context->flags |= 0x10000;
        switch (func_ov001_02077bcc()) {
        case 0:
        case 7:
            SetFieldMenuMode_020781a4(0xd);
            break;
        }
    }
    if (slot - context->level > 0 && context->level != -1) {
        SelectSlotTitleLine_0206ff9c(context, slot);
    }
    for (i = 0; i < slot - context->level; i++) {
        func_ov001_0207b4f8();
    }
    context->flags |= 0x8000;
    func_ov027_020ba114(0x80000000 | (((context->vramBase + 0x8000) & 0xfffffc) << 7) | (paletteIds.values[slot] & 0x1ff), 1, func_ov001_0206f040, 0);
    context->level = slot;
}
