#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct EffectAsset {
    u32 id;
    u32 handle;
} EffectAsset;

typedef struct EffectParams {
    s32 type;
    VecFx32 position;
    VecFx32 velocity;
    EffectAsset asset;
    fx32 scale;
    fx32 spin;
    fx32 drag;
    fx32 life;
} EffectParams;

typedef struct UnitCircle {
    fx32 cos;
    fx32 sin;
} UnitCircle;

typedef struct BasisMatrix {
    VecFx32 row[3];
} BasisMatrix;

typedef struct Actor {
    u8 pad_0000[0x934];
    s32 hitState : 8;
    s32 hitFlags : 24;
    u8 pad_0938[0xec4 - 0x938];
    u8 effects[0x1614 - 0xec4];
    EffectAsset assets[24];
    u8 effectCount;
    u8 pad_16d5[0x171c - 0x16d5];
    s32 effectKind : 8;
    s32 effectFlags : 24;
} Actor;

extern const s16 data_0205356c[];
extern const VecFx32 data_ov059_020cfe60;

extern u16 GetLinkedAngleOffset_020cd0e4(Actor *actor);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);
extern int FixedPointMultiply12(int left, int right);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void BuildBasisMatrix_0204bf28(const VecFx32 *forward, const VecFx32 *up, BasisMatrix *out);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern BOOL func_ov059_020ceefc(void *effects, EffectParams *params);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, u32 *position, u32 flags);

#define TO_RADIANS(a) ((s32)(((s64)(a) * 0x6488) / 0x10000))
#define ANGLE_INDEX(r) ((s32)((((s64)(r) << 16) / 0x6488) & 0xffff) >> 4)
#define SIN_AT(i) data_0205356c[i]
#define COS_AT(i) data_0205356c[(0x400 - (i)) & 0xfff]

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline EffectParams MakeEffectParams(s32 type, VecFx32 position, VecFx32 velocity, const EffectAsset *asset,
                                            fx32 scale, fx32 spin, fx32 drag, fx32 life)
{
    EffectParams params;
    EffectAsset copy;
    EffectAsset zero;

    params.type = type;
    params.position = position;
    params.velocity = velocity;
    if (asset) {
        copy = *asset;
    } else {
        zero.id = 0;
        zero.handle = 0;
        copy = zero;
    }
    params.asset = copy;
    params.scale = scale;
    params.spin = spin;
    params.drag = drag;
    params.life = life;
    return params;
}

static inline VecFx32 ScaledVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 result = *vec;
    ScaleVecFx32InPlace_0204a5e4(&result, scale);
    return result;
}

static inline VecFx32 MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd_01ffa09c(scale, v, add, &result);
    return result;
}

static inline BasisMatrix MakeBasis(const VecFx32 *forward, const VecFx32 *up)
{
    BasisMatrix result;
    BasisMatrix basis;

    BuildBasisMatrix_0204bf28(forward, up, &basis);
    *(BasisMatrix *)&result = *(BasisMatrix *)&basis;
    return result;
}

static inline const VecFx32 *StoreVec(VecFx32 *dst, VecFx32 value)
{
    *dst = value;
    return dst;
}

static inline UnitCircle AngleToUnit(int index)
{
    UnitCircle unit;
    unit.cos = COS_AT(index);
    unit.sin = SIN_AT(index);
    return unit;
}

void SpawnHitEffects_020caea0(Actor *actor)
{
    VecFx32 soundPos;
    EffectParams params;
    VecFx32 velocity3;
    VecFx32 velocity4;
    EffectParams single;
    VecFx32 velocity;
    BasisMatrix basis;
    EffectParams burst;
    VecFx32 position;
    VecFx32 forward;
    VecFx32 up;
    VecFx32 axisInit;
    VecFx32 axis;
    VecFx32 offset;
    u16 angle;
    UnitCircle pitch;
    fx32 tiltSin;
    fx32 tiltCos;
    int i;

    offset = data_ov059_020cfe60;
    angle = GetLinkedAngleOffset_020cd0e4(actor) + 0x8000;
    axisInit.x = 0;
    axisInit.y = FX32_ONE;
    axisInit.z = 0;
    axis = axisInit;
    RotateVectorAroundAxis_0204b34c(&offset, &axis, TO_RADIANS(angle));
    VEC_Add_01ff9e0c(&offset, Actor_GetModelPosition_020cd0d8(actor), &offset);
    position = offset;
    *(VecFx32 *)&soundPos = *(VecFx32 *)&offset;

    if (actor->effectKind != 1 && actor->effectKind != 2) {
        switch (actor->effectKind) {
        case 3: {
            fx32 tilt = random_next_scaled_0202aa04(0x430) + 0x1922;
            s32 yaw = random_next_scaled_0202aa04(0x6488);

            velocity3.x = FixedPointMultiply12(COS_AT(ANGLE_INDEX(yaw)), COS_AT(ANGLE_INDEX(tilt)));
            velocity3.y = FixedPointMultiply12(SIN_AT(ANGLE_INDEX(yaw)), COS_AT(ANGLE_INDEX(tilt)));
            velocity3.z = -SIN_AT(ANGLE_INDEX(tilt));
            ScaleVecFx32InPlace_0204a5e4(&velocity3, 0x2333);
            params = MakeEffectParams(3, position, velocity3, NULL, FX32_ONE, 0, 0, 0);
            break;
        }
        case 4: {
            fx32 tilt = random_next_scaled_0202aa04(0x1657) + 0x1922;
            s32 yaw = random_next_scaled_0202aa04(0x6488);

            velocity4.x = FixedPointMultiply12(COS_AT(ANGLE_INDEX(yaw)), COS_AT(ANGLE_INDEX(tilt)));
            velocity4.y = FixedPointMultiply12(SIN_AT(ANGLE_INDEX(yaw)), COS_AT(ANGLE_INDEX(tilt)));
            velocity4.z = -SIN_AT(ANGLE_INDEX(tilt));
            ScaleVecFx32InPlace_0204a5e4(&velocity4, 0x99a);
            params = MakeEffectParams(4, position, velocity4, NULL, 0x2000, 0, 0, 0);
            break;
        }
        }
        func_ov059_020ceefc(actor->effects, &params);
    } else {
        if (actor->hitState < 3 || actor->effectCount == 0) {
            single = MakeEffectParams(1, position, MakeVec(0, 0, -0xccd), NULL, FX32_ONE, 0, FX32_ONE, 0x1e000);
            func_ov059_020ceefc(actor->effects, &single);
            PlaySoundEffect_0204d924(0x19d, 0);
        } else {
            for (i = 0; i < actor->effectCount; i++) {
                tiltSin = SIN_AT(0x156);
                tiltCos = COS_AT(0x156);
                if (actor->effectCount != 1) {
                    s32 yaw;
                    int yawIndex;

                    pitch = AngleToUnit(ANGLE_INDEX((s32)(random_next_scaled_0202aa04(0xc91) + 0x25b3)));
                    yaw = random_next_scaled_0202aa04(0x6488);
                    basis = MakeBasis(StoreVec(&forward, MakeVec(FX32_ONE, 0, 0)), StoreVec(&up, MakeVec(0, tiltCos, -tiltSin)));
                    yawIndex = ANGLE_INDEX(yaw);
                    velocity = ScaledVec(&basis.row[0], FixedPointMultiply12(COS_AT(yawIndex), *(volatile fx32 *)&pitch.cos));
                    velocity = MultAdd(FixedPointMultiply12(SIN_AT(yawIndex), *(volatile fx32 *)&pitch.cos), &basis.row[1], &velocity);
                    velocity = MultAdd(pitch.sin, &basis.row[2], &velocity);
                    ScaleVecFx32InPlace_0204a5e4(&velocity, 0x666);
                } else {
                    velocity = MakeVec(0, 0, -0x666);
                }
                burst = MakeEffectParams(2, position, velocity, &actor->assets[i], 0x1800, 0xf33, 0x800, 0);
                if (!func_ov059_020ceefc(actor->effects, &burst)) {
                    return;
                }
                SpawnSoundSlot_0204da8c(0x19d, 1, (u32 *)&soundPos, 0);
            }
        }
    }
}
