#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct AttachPoint {
    u32 key;
    s32 nameIndex;
    u8 pad_08[0xc];
    VecFx32 scale;
} AttachPoint;

typedef struct SpawnRequest {
    u16 unk_00;
    u16 objectId;
    u16 unk_04;
    u16 ownerId;
    u16 active : 1;
    u16 mirrored : 1;
    u16 hidden : 1;
    u16 unk_08_3 : 13;
    u16 unk_0a;
    s32 nameIndex;
} SpawnRequest;

typedef struct DisplayStyle {
    s32 anim;
    s32 alpha;
    s32 offsetIndex;
    fx32 scale;
    s32 blend;
    s32 tint;
} DisplayStyle;

typedef struct StageController {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[2];
    u16 actorId;
} StageController;

typedef struct StageActor {
    u8 pad_000[0xec];
    u8 material[0x31c - 0xec];
    s32 tint;
    u8 alpha;
    u8 alphaB;
    u8 alphaC;
    u8 pad_323;
    s32 fadeA;
    s32 fadeB;
    u8 pad_32c[0x3a0 - 0x32c];
    s32 blend;
} StageActor;

typedef struct StageEvent {
    u8 pad_000[9];
    u8 mode;
    u8 style;
    u8 pendingStyle;
    u8 pad_00c[2];
    u16 objectId;
    u16 actorId;
    u8 pad_012[0x20 - 0x12];
    fx32 baseScale;
    u8 pad_024[0x64 - 0x24];
    fx32 offsetPair[2];
    u8 pad_06c;
    u8 defaultOffsetIndex;
    u8 pad_06e[2];
    fx32 width;
    fx32 height;
    u8 pad_078[0x1ba - 0x78];
    u16 markerSlot;
} StageEvent;

extern const DisplayStyle data_ov001_0209e4b4[];
extern BOOL func_ov001_0209d064(u32 id);
extern StageActor *GetStageActor_0209c040(s16 id);
extern void LoadScaledOffsetPair_0209d230(fx32 *out, int index);
extern void PlayActorAnimationSlot_02091a00(StageActor *actor, int slot, u32 anim, int frames, BOOL loop);
extern void HookMaterialAnimAlpha_0208f554(void *target);
extern StageActor *GetLinkedStageActor_0209c2f0(StageActor *actor);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void FindStageAttachPoint_02097890(StageEvent *event, u32 key, AttachPoint *out);
extern u16 SpawnStageObjectActor_02096ae0(StageEvent *event, SpawnRequest *request, int flags);
extern StageController *GetStageController_0209c120(u16 slot);
extern void Obj_SetField14_0209839c(StageController *controller, s32 value);
extern s64 FX_DivFx64c_01ff9c94(fx32 numer, fx32 denom);
extern fx32 FX_Mul32x64c_02006468(fx32 value, s64 scale);
extern int ArmObject_0205116c(void);
extern int FixedPointMultiply12(int left, int right);

void RefreshStageEventDisplay_02093330(StageEvent *event)
{
    const DisplayStyle *style;
    fx32 scale = FX32_ONE;
    StageActor *actor;
    fx32 width;
    s64 ratio;
    fx32 height;

    if (event->actorId == 0) {
        return;
    }
    if (event->objectId != 0x63 && func_ov001_0209d064(event->objectId)) {
        GetStageActor_0209c040(event->actorId);
        if (event->mode == 4 && event->width == event->height) {
            event->pendingStyle = 4;
            event->style = event->pendingStyle;
        }
        style = &data_ov001_0209e4b4[event->style];
        if (style->offsetIndex != -1) {
            LoadScaledOffsetPair_0209d230(event->offsetPair, style->offsetIndex);
        } else {
            LoadScaledOffsetPair_0209d230(event->offsetPair, event->defaultOffsetIndex);
        }
        scale = style->scale;
        actor = GetStageActor_0209c040(event->actorId);
        if (actor != NULL) {
            do {
                if (event->mode == 4) {
                    actor->alpha = 0x1f;
                } else if (style->alpha != -1) {
                    actor->alpha = style->alpha;
                } else {
                    actor->alpha = 0x1f;
                }
                actor->alphaB = actor->alpha;
                actor->alphaC = actor->alpha;
                actor->fadeA = 0;
                actor->fadeB = 0;
                actor->blend = style->blend;
                actor->tint = style->tint;
                PlayActorAnimationSlot_02091a00(actor, 3, (s16)style->anim, 0, 1);
                PlayActorAnimationSlot_02091a00(actor, 4, (s16)style->anim, 0, 1);
                PlayActorAnimationSlot_02091a00(actor, 2, (s16)style->anim, 0, 1);
                if (event->style == 4) {
                    HookMaterialAnimAlpha_0208f554(actor->material);
                }
                actor->blend = style->blend;
                actor = GetLinkedStageActor_0209c2f0(actor);
            } while (actor != NULL);
        }
        if (event->markerSlot == 0) {
            AttachPoint point;
            SpawnRequest request;
            u16 slot;
            StageController *controller;

            func_01ff88c4(&request, 0, sizeof(SpawnRequest));
            FindStageAttachPoint_02097890(event, 6, &point);
            request.objectId = 0x1b;
            request.active = 1;
            request.hidden = 0;
            request.ownerId = event->actorId;
            request.nameIndex = point.nameIndex;
            request.mirrored = 0;
            slot = SpawnStageObjectActor_02096ae0(event, &request, 0);
            controller = GetStageController_0209c120(slot);
            if (controller != NULL) {
                controller->flags |= 4;
                controller->flags |= 8;
                Obj_SetField14_0209839c(controller, point.scale.x);
            }
            event->markerSlot = slot;
        }
        if (event->markerSlot != 0) {
            StageController *controller = GetStageController_0209c120(event->markerSlot);
            if (controller != NULL && controller->actorId != 0) {
                StageActor *marker = GetStageActor_0209c040(controller->actorId);
                PlayActorAnimationSlot_02091a00(marker, 0, (s16)style->anim, 0, 1);
                PlayActorAnimationSlot_02091a00(marker, 4, (s16)style->anim, 0, 1);
                PlayActorAnimationSlot_02091a00(marker, 3, (s16)style->anim, 0, 1);
                PlayActorAnimationSlot_02091a00(marker, 2, (s16)style->anim, 0, 1);
            }
        }
    }
    width = event->width;
    if (event->height != 0) {
        ratio = FX_DivFx64c_01ff9c94(width, event->height);
    } else {
        ratio = 0;
    }
    if (event->mode != 4 && event->mode != 3) {
        scale = FixedPointMultiply12(scale, ArmObject_0205116c());
    }
    height = FixedPointMultiply12(event->baseScale, scale);
    if (height <= FX32_ONE) {
        height = FX32_ONE;
    }
    event->height = height;
    event->width = FX_Mul32x64c_02006468(height, ratio);
    if (width > 0 && ratio == 0) {
        event->width = FX32_ONE;
    }
}
