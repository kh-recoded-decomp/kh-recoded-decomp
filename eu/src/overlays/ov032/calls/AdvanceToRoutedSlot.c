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

extern Ov032Globals gGroupSceneGlobals;

extern PlayerCursor *GetPendingWorldEntryData(void);
extern u32 NextSharedRandom16Scaled(u32 range);
extern void ApplySlotStyleToSession(void);
extern s8 GetSignedByteAt1(PlayerCursor *cursor);
extern s8 GetSignedByteAt3(PlayerCursor *cursor);
extern void func_ov001_02063848(int a, int b);

int AdvanceToRoutedSlot(void)
{
    SceneState *scene = gGroupSceneGlobals.scene;
    PlayerCursor *cursor = GetPendingWorldEntryData();
    SceneContext *context;

    if (gGroupSceneGlobals.context->overrideActive) {
        gGroupSceneGlobals.context->visitedMask &= ~(1 << gGroupSceneGlobals.context->slotIndex);
        gGroupSceneGlobals.context->overrideActive = 0;
    }
    context = gGroupSceneGlobals.context;
    context->slotIndex = context->routes[context->slotIndex][(cursor->direction + context->routeBase[context->slotIndex] - 1) & 3];
    gGroupSceneGlobals.context->unk_80 = 0;
    gGroupSceneGlobals.context->unk_84 = 1;
    context = gGroupSceneGlobals.context;
    if (context->slotLocked[context->slotIndex] == 0 && (context->visitedMask & (1 << context->slotIndex))) {
        context->overrideActive = 1;
    }
    context = gGroupSceneGlobals.context;
    if (context->slotLocked[context->slotIndex] == 0 && context->lockEnabled != 0 && !(context->lockedMask & (1 << context->slotIndex))) {
        if (context->lockChance > (int)NextSharedRandom16Scaled(100)) {
            gGroupSceneGlobals.context->lockedMask |= 1 << gGroupSceneGlobals.context->slotIndex;
        }
    }
    ApplySlotStyleToSession();
    gGroupSceneGlobals.context->displayMode = 2;
    func_ov001_02063848(GetSignedByteAt1(cursor), GetSignedByteAt3(cursor));
    scene->flags |= 2;
    return 7;
}
