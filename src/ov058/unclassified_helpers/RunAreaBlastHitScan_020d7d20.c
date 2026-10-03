#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    u32 kind;
    Box box;
    int index;
    VecFx32 delta;
    Box sweptBox;
} HitVolume;

typedef struct {
    HitVolume volume;
    u32 owner;
    VecFx32 motion;
    fx32 scale;
    u16 angle;
    u8 pad_5a[2];
    int target;
} HitAttack;

typedef struct {
    s32 power;
    u8 pad_04[0x1c];
    s32 knockback;
    u16 hitAll : 1;
    u16 flag1 : 1;
    u16 flag2 : 1;
    u16 flag3 : 7;
    u16 flag10 : 1;
    u16 flag11 : 1;
    u16 flag12 : 1;
    u8 pad_26[2];
} HitOptions;

typedef struct {
    u8 data[0xdc];
} HitScan;

extern const VecFx32 data_ov058_020d910c;

extern void InitRecord60_020ac0b8(HitAttack *attack);
extern void func_0203ad14(HitVolume *volume, int *bounds, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroBytes0x28_020ac0f8(void *obj);
extern void ZeroAndSetField0xd4_020ac150(void *obj);
extern BOOL StepHitScan_020ac164(int type, HitAttack *attack, HitOptions *options, HitScan *scan);

void RunAreaBlastHitScan_020d7d20(void)
{
    HitAttack attack;
    HitScan scan;
    HitVolume volume;
    HitOptions options;
    int bounds[4];
    VecFx32 center;

    InitRecord60_020ac0b8(&attack);
    center = data_ov058_020d910c;
    func_0203ad14(&volume, bounds, &center, 0xa000);
    volume.delta = attack.motion;
    OffsetBoxByDelta_0203ac70(&volume.box, &volume.sweptBox, &volume.delta);
    attack.volume = volume;
    ZeroBytes0x28_020ac0f8(&options);
    options.power = 0x6000;
    options.knockback = 0;
    options.hitAll = 1;
    options.flag2 = 1;
    options.flag12 = 1;
    options.flag10 = 1;
    ZeroAndSetField0xd4_020ac150(&scan);
    while (StepHitScan_020ac164(0, &attack, &options, &scan)) {
    }
}
