#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
    u16 unk_26;
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x10];
    s32 markerIndex;
} MarkerConfig;

typedef struct {
    s32 state;
    VecFx32 velocity;
} CarryMotion;

typedef struct CarryActor CarryActor;

struct CarryActor {
    u8 pad_000[0x230];
    u8 *model;
    u8 pad_234[0x9ac - 0x234];
    u64 flags;
    u8 entryId;
    u8 pad_9b5[0x9c4 - 0x9b5];
    s32 stateTimer;
    VecFx32 recoil;
    u8 pad_9d4[0x10ec - 0x9d4];
    void (*setState)(CarryActor *actor, int state);
};

extern MarkerConfig data_ov030_020bd004;
extern CarryMotion g_carryMotion_020bd004;
extern const VecFx32 data_02053438;
extern void *func_ov001_0206db78(int index);
extern int func_ov001_0206db8c(int index);
extern BOOL func_ov001_020645c8(int flagId);
extern BOOL IsGroupMemberActive_020a8d1c(int groupId, int member);
extern void StopAndClearSoundEmitter_020a8e14(int groupId, int emitterIndex);
extern void SnapCarriedActorToView_020bb474(CarryActor *actor, CarryMotion *motion);
extern void SteerCarriedActorInView_020bb870(CarryActor *actor, CarryMotion *motion, int input, BOOL force);
extern BOOL CheckHeadroomClear_020bb9c8(CarryActor *actor);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern u16 GetFieldAt0xe_020a7558(void *entry);
extern BOOL HasFlagsAt0xc_020a751c(void *holder, u16 mask);
extern VecFx32 *func_ov042_020bd324(void);
extern u16 GetGroupSlotValue_020a8f1c(int groupId, int index);
extern void SetSlotEntryValue_020a8f4c(int groupId, int slot, int value);
extern void InvokeHandlerOnIndexedRecord_020a8e88(int groupId, int index, int value);
extern void func_020359f8(int index, int param2, void *param3);

void UpdateCarriedActor_020bc110(CarryActor *actor)
{
    MarkerRequest dropRequest;
    MarkerRequest landRequest;
    void *entry = func_ov001_0206db78(actor->entryId);
    int group = func_ov001_0206db8c(7);
    int prevState;
    int markerGroup;
    VecFx32 *drift;
    int input;
    BOOL moving;
    BOOL movingXY;

    if (func_ov001_020645c8(0x3625)) {
        if (actor->flags & 0x20000) {
            actor->flags &= ~0x20000;
        }
        if (IsGroupMemberActive_020a8d1c(group, 0)) {
            StopAndClearSoundEmitter_020a8e14(group, 0);
        }
        return;
    }
    prevState = g_carryMotion_020bd004.state;
    switch (prevState) {
    case 0:
        markerGroup = func_ov001_0206db8c(6);
        SnapCarriedActorToView_020bb474(actor, &g_carryMotion_020bd004);
        if (!IsGroupMemberActive_020a8d1c(markerGroup, 0)) {
            func_ov021_020a8ab4(&dropRequest);
            dropRequest.id = actor->entryId;
            dropRequest.unk_25 = 1;
            dropRequest.unk_26 = 1;
            dropRequest.unk_24 = 0;
            dropRequest.prevIndex = data_ov030_020bd004.markerIndex;
            dropRequest.index = 1;
            dropRequest.pos.x -= 0x1000;
            func_ov021_020a8ca0(&dropRequest, group);
            g_carryMotion_020bd004.state = 1;
        }
        break;
    case 1:
        SnapCarriedActorToView_020bb474(actor, &g_carryMotion_020bd004);
        if (!IsGroupMemberActive_020a8d1c(group, 0)) {
            func_ov021_020a8ab4(&landRequest);
            landRequest.id = actor->entryId;
            landRequest.unk_25 = 1;
            landRequest.unk_26 = 5;
            landRequest.unk_24 = 1;
            landRequest.pos.x -= 0x1000;
            func_ov021_020a8ca0(&landRequest, group);
            g_carryMotion_020bd004.state = 2;
        }
        break;
    case 2:
        SteerCarriedActorInView_020bb870(actor, &g_carryMotion_020bd004, GetFieldAt0xe_020a7558(entry), FALSE);
        SnapCarriedActorToView_020bb474(actor, &g_carryMotion_020bd004);
        if (actor->stateTimer >= 0x5a000) {
            g_carryMotion_020bd004.state = 3;
        }
        if (HasFlagsAt0xc_020a751c(entry, 1)) {
            g_carryMotion_020bd004.state = 3;
        }
        break;
    case 3:
        if (CheckHeadroomClear_020bb9c8(actor)) {
            SetSlotEntryValue_020a8f4c(group, 0, GetGroupSlotValue_020a8f1c(group, 0) & ~4);
            InvokeHandlerOnIndexedRecord_020a8e88(group, 0, 2);
            func_020359f8(actor->entryId, 0, actor->model + 0xa8);
            actor->flags &= ~0x20000;
            actor->flags &= ~0x40000;
            actor->recoil.x = data_02053438.x;
            actor->recoil.y = data_02053438.y;
            actor->recoil.z = data_02053438.z;
            actor->setState(actor, 4);
        } else {
            drift = func_ov042_020bd324();
            input = 0x10;
            moving = TRUE;
            movingXY = TRUE;
            if (drift->x == 0 && drift->y == 0) {
                movingXY = FALSE;
            }
            if (!movingXY && drift->z == 0) {
                moving = FALSE;
            }
            if (moving) {
                if (drift->x <= 0) {
                    input = 0x20;
                }
            } else {
                input = 0x40;
            }
            SteerCarriedActorInView_020bb870(actor, &g_carryMotion_020bd004, input, TRUE);
        }
        SnapCarriedActorToView_020bb474(actor, &g_carryMotion_020bd004);
        break;
    }
    if (prevState != g_carryMotion_020bd004.state) {
        actor->stateTimer = 0;
    }
}
