#include "nitro/types.h"

typedef struct ControllerOwner {
    u8 pad_00[0xd];
    u8 actorId;
} ControllerOwner;

typedef struct ControlledActor {
    u8 pad_000[0x1d0];
    u16 controlMode;
    u16 controllerIndex;
    u8 pad_1d4[0x278 - 0x1d4];
    void *controlData;
} ControlledActor;

extern ControlledActor *func_ov001_0209c040(s16 actorId);
extern u32 func_ov001_0209c584(u32 mask);
extern s32 *func_ov001_0209c120(u16 index);
extern BOOL IsCommandType4_0209838c(s32 *type);
extern void func_ov001_020981e8(s32 *controller);

void PostUpdateActorController_02097fe0(ControllerOwner *owner)
{
    ControlledActor *actor = func_ov001_0209c040(owner->actorId);
    s32 *controller;

    if (actor != NULL && actor->controlData != NULL && func_ov001_0209c584(0x40000000) == 0 &&
        actor->controlMode == 2) {
        controller = func_ov001_0209c120(actor->controllerIndex);
        if (controller != NULL && !IsCommandType4_0209838c(controller)) {
            func_ov001_020981e8(controller);
        }
    }
}
