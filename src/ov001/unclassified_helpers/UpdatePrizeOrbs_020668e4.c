#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PrizeOrb {
    struct PrizeOrb *next;
    u8 pad_04[0x8];
    VecFx32 drawPos;
    u8 pad_18[0x8];
    s16 blinkAlpha;
    u8 pad_22[0x6];
    int payload;
    u8 kind;
    u8 pad_2d;
    s8 targetSlot : 4;
    s8 homingScale : 4;
    u8 floating : 1;
    u8 despawnOnFall : 1;
    u8 unk_2f_bit2 : 1;
    u8 targetIsCursor : 1;
    u8 blinkPhase : 1;
    u8 blinking : 1;
    s16 timer;
    s16 lifetime;
    u8 pad_34[0x4];
    VecFx32 pos;
    VecFx32 velocity;
} PrizeOrb;

typedef struct OrbHost {
    u8 pad_00[0x4c];
    PrizeOrb *activeList;
    u8 pad_50[0x1bf];
    u8 suspended : 1;
} OrbHost;

typedef struct OrbReceiver {
    u8 pad_000[0x1f4];
    void (*onCollect)(struct OrbReceiver *receiver, int kind, int payload);
} OrbReceiver;

extern OrbHost *data_ov001_020a0464;
extern const s16 data_0205356c[];
extern BOOL func_ov001_020642d0(int mode);
extern BOOL PXI_Init_020880d8(VecFx32 *out);
extern void PXI_Init_020880d0(int payload);
extern VecFx32 *func_ov001_0206dc60(int slot);
extern OrbReceiver *GetBoundedEntryField_0206db5c(int slot);
extern void func_ov001_02072254(int *payload, int count);
extern void func_ov001_0206674c(PrizeOrb *orb);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_NormalizeLength_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void UpdatePrizeOrbs_020668e4(void)
{
    PrizeOrb *orb;
    PrizeOrb *next;
    VecFx32 steer;
    VecFx32 direction;
    VecFx32 target;
    fx32 distance;

    if (data_ov001_020a0464->suspended) {
        return;
    }
    orb = data_ov001_020a0464->activeList;
    while (orb != NULL) {
        next = orb->next;
        if (orb->targetSlot >= 0) {
            if (func_ov001_020642d0(0)) {
                orb->targetSlot = -1;
                orb->timer = 0;
                continue;
            }
            if (orb->targetIsCursor) {
                if (!PXI_Init_020880d8(&target)) {
                    orb->targetSlot = -1;
                    orb->despawnOnFall = 1;
                    continue;
                }
            } else {
                target = *func_ov001_0206dc60(orb->targetSlot);
            }
            VEC_Subtract_01ff9e3c(&target, &orb->pos, &direction);
            distance = VEC_NormalizeLength_01ffaff4(&direction, &direction);
            orb->timer += 0x100;
            if (orb->timer > 0x1000) {
                orb->timer = 0x1000;
            }
            if (orb->timer >= 0x1000 && distance < 0x800) {
                int kind = orb->kind;
                if (kind != 6) {
                    if (orb->targetIsCursor) {
                        PXI_Init_020880d0(orb->payload);
                    } else {
                        int payload = orb->payload;
                        OrbReceiver *receiver = GetBoundedEntryField_0206db5c(orb->targetSlot);
                        if (receiver->onCollect != NULL) {
                            receiver->onCollect(receiver, kind, payload);
                        }
                    }
                } else {
                    func_ov001_02072254(&orb->payload, 1);
                }
                func_ov001_0206674c(orb);
                orb = next;
                continue;
            }
            steer.x = (fx32)(((fx64)-direction.z * ((0x1000 - orb->timer) * orb->homingScale) + 0x800) >> 12);
            steer.z = (fx32)(((fx64)direction.x * ((0x1000 - orb->timer) * orb->homingScale) + 0x800) >> 12);
            steer.y = 0;
            VEC_MultAdd_01ffa09c(orb->timer, &direction, &steer, &steer);
            distance *= 2;
            if (distance > 0x800) {
                distance = 0x800;
            }
            orb->velocity.x = (fx32)(((fx64)steer.x * distance + 0x800) >> 12);
            orb->velocity.y = (fx32)(((fx64)steer.y * distance + 0x800) >> 12);
            orb->velocity.z = (fx32)(((fx64)steer.z * distance + 0x800) >> 12);
            VEC_MultAdd_01ffa09c(0x1000, &orb->velocity, &orb->pos, &orb->pos);
        } else {
            if (orb->lifetime > 0) {
                orb->lifetime--;
            }
            if (orb->floating) {
                orb->timer += 0x400;
                orb->pos.y = orb->velocity.y + (data_0205356c[(u16)orb->timer >> 4] >> 4);
                goto copy;
            }
            VEC_Add_01ff9e0c(&orb->pos, &orb->velocity, &orb->pos);
            orb->velocity.y -= 0x45;
            if (orb->despawnOnFall && orb->pos.y < -0xa000) {
                func_ov001_0206674c(orb);
                orb = next;
                continue;
            }
        }
        if (orb->blinking) {
            orb->blinkAlpha = orb->blinkPhase * 31;
            orb->blinkPhase = !orb->blinkPhase;
        }
    copy:
        orb->drawPos = orb->pos;
        orb = next;
    }
}
