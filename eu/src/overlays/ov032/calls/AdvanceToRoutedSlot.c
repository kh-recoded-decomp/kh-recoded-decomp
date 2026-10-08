#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x37];
    s8 routeBase[6];
    s8 routes[6][4];
    s8 slotIndex;
    s8 slotLocked[6];
    u8 pad_5c;
    u8 visitedMask;
    u8 pad_5e;
    u8 lockedMask;
    u8 pad_60;
    u8 lockChance;
    u8 pad_62[0xd];
    u8 displayMode;
    u8 pad_70[4];
    s32 overrideActive;
    u8 pad_78[8];
    s32 unk_80;
    s32 unk_84;
    s32 lockEnabled;
} SceneContext;

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

typedef struct {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

typedef struct {
    s8 unk_00;
    s8 unk_01;
    s8 direction;
} PlayerCursor;

extern Ov032Globals data_ov032_020c0080;

extern PlayerCursor *func_ov001_0206e644(void);
extern u32 func_0202a9e4(u32 range);
extern void ApplySlotStyleToSession(void);
extern s8 GetSignedByteAt1(PlayerCursor *cursor);
extern s8 GetSignedByteAt3(PlayerCursor *cursor);
extern void func_ov001_02063848(int a, int b);

int AdvanceToRoutedSlot(void)
{
    SceneState *scene = data_ov032_020c0080.scene;
    PlayerCursor *cursor = func_ov001_0206e644();
    SceneContext *context;

    if (data_ov032_020c0080.context->overrideActive) {
        data_ov032_020c0080.context->visitedMask &= ~(1 << data_ov032_020c0080.context->slotIndex);
        data_ov032_020c0080.context->overrideActive = 0;
    }
    context = data_ov032_020c0080.context;
    context->slotIndex = context->routes[context->slotIndex][(cursor->direction + context->routeBase[context->slotIndex] - 1) & 3];
    data_ov032_020c0080.context->unk_80 = 0;
    data_ov032_020c0080.context->unk_84 = 1;
    context = data_ov032_020c0080.context;
    if (context->slotLocked[context->slotIndex] == 0 && (context->visitedMask & (1 << context->slotIndex))) {
        context->overrideActive = 1;
    }
    context = data_ov032_020c0080.context;
    if (context->slotLocked[context->slotIndex] == 0 && context->lockEnabled != 0 && !(context->lockedMask & (1 << context->slotIndex))) {
        if (context->lockChance > (int)func_0202a9e4(100)) {
            data_ov032_020c0080.context->lockedMask |= 1 << data_ov032_020c0080.context->slotIndex;
        }
    }
    ApplySlotStyleToSession();
    data_ov032_020c0080.context->displayMode = 2;
    func_ov001_02063848(GetSignedByteAt1(cursor), GetSignedByteAt3(cursor));
    scene->flags |= 2;
    return 7;
}
