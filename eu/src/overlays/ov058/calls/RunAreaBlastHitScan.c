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

extern const VecFx32 data_ov058_020d912c;

extern void InitRecord60(HitAttack *attack);
extern void MakeSphereShape(HitVolume *volume, int *bounds, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroBytes0x28(void *obj);
extern void ZeroAndSetField0xd4(void *obj);
extern BOOL StepHitScan(int type, HitAttack *attack, HitOptions *options, HitScan *scan);

void RunAreaBlastHitScan(void)
{
    HitAttack attack;
    HitScan scan;
    HitVolume volume;
    HitOptions options;
    int bounds[4];
    VecFx32 center;

    InitRecord60(&attack);
    center = data_ov058_020d912c;
    MakeSphereShape(&volume, bounds, &center, 0xa000);
    volume.delta = attack.motion;
    OffsetBoxByDelta(&volume.box, &volume.sweptBox, &volume.delta);
    attack.volume = volume;
    ZeroBytes0x28(&options);
    options.power = 0x6000;
    options.knockback = 0;
    options.hitAll = 1;
    options.flag2 = 1;
    options.flag12 = 1;
    options.flag10 = 1;
    ZeroAndSetField0xd4(&scan);
    while (StepHitScan(0, &attack, &options, &scan)) {
    }
}
