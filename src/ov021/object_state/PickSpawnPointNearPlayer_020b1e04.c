#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x12];
    u16 stageObjectId;
} StageInfo;

typedef struct {
    u8 pad_00[0x2c0];
    VecFx32 position;
} PlayerActor;

typedef struct {
    StageInfo *stage;
    u32 pad_04;
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[8];
    VecFx32 center;
    fx32 radius;
} SpawnArea;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} SpawnTarget;

extern FieldContext data_ov021_020b56a4;
extern const s16 data_0205356c[];

extern u16 *GetStageObjectHandle_0209c0c4(u32 id);
extern SpawnArea *GetLargeTableEntry_0209c30c(u32 index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern s32 func_ov001_02063a38(void);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern u16 FixedPointAtan2_020062bc(int y, int x);
extern int nextRandom12_0202aa58(void);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

s32 PickSpawnPointNearPlayer_020b1e04(SpawnTarget *target)
{
    StageInfo *stage = data_ov021_020b56a4.stage;
    PlayerActor *player = data_ov021_020b56a4.player;
    SpawnArea *area;
    fx32 distance;
    VecFx32 normal;
    VecFx32 direction;
    VecFx32 offset;

    if (stage == NULL) {
        return 0;
    }
    if (player == NULL) {
        return 0;
    }
    area = GetLargeTableEntry_0209c30c(*GetStageObjectHandle_0209c0c4(stage->stageObjectId));
    VEC_Subtract_01ff9e3c(&player->position, &area->center, &offset);
    distance = VEC_Mag_01ff9f28(&offset);
    if (func_ov001_02063a38() != 4) {
        int angle;
        int index;
        if (distance < 0x19a) {
            angle = random_next_scaled_0202aa04(0x10000);
        } else {
            int heading;
            func_01ff9f88(&offset, &normal);
            heading = FixedPointAtan2_020062bc(-normal.x, -normal.z);
            angle = random_next_scaled_0202aa04(0x4000) - 0x4000;
            angle = (heading + angle + 0xffff) % 0xffff;
        }
        index = angle >> 4;
        direction.x = data_0205356c[index];
        direction.y = 0;
        direction.z = data_0205356c[(0x400 - index) & 0xfff];
        VEC_MultAdd_01ffa09c((area->radius >> 1) + FixedPointMultiply12(area->radius >> 1, nextRandom12_0202aa58()), &direction, &area->center, &target->position);
    } else {
        target->position = area->center;
        target->position.z = 0;
        if (distance < 0x19a) {
            if (random_next_scaled_0202aa04(2) == 0) {
                target->position.x = area->center.x + area->radius;
            } else {
                target->position.x = area->center.x - area->radius;
            }
        } else {
            target->position = area->center;
            if (offset.x < 0) {
                target->position.x = area->center.x + area->radius;
            } else {
                target->position.x = area->center.x - area->radius;
            }
        }
    }
    return 0;
}
