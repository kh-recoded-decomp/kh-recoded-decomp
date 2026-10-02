#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RangeResult {
    fx32 distance;
    int zone;
    int tag;
} RangeResult;

typedef struct RangeConfig {
    u8 pad_00[0x48];
    fx32 farLimit;
    fx32 midLimit;
} RangeConfig;

extern RangeConfig *data_ov001_020a0484;
extern const s16 data_0205356c[];
extern void func_ov001_0206ba18(RangeResult *result);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern int QuerySubModeStatus_020af3f4(void);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

void ClassifyTargetRange_0206ba2c(int index, VecFx32 *target, RangeResult *result, int tag) {
    RangeConfig *config = data_ov001_020a0484;
    VecFx32 *origin;
    fx32 distance;
    fx32 leaderDot;
    fx32 cameraDot;
    VecFx32 direction;
    VecFx32 facing;
    int angle;

    func_ov001_0206ba18(result);
    result->tag = tag;
    origin = func_ov001_0206dc4c(index);
    distance = func_01ffa0f4(target, origin);
    VEC_Subtract_01ff9e3c(target, origin, &direction);
    if (direction.x != 0 || direction.y != 0 || direction.z != 0) {
        func_01ff9f88(&direction, &direction);
    }
    direction.y = 0;
    angle = GetBiasAdjustedField_0206dc80(index) >> 4;
    facing.y = 0;
    facing.x = -data_0205356c[angle];
    facing.z = -data_0205356c[(0x400 - angle) & 0xfff];
    leaderDot = VEC_DotProduct_01ff9e6c(&facing, &direction);
    angle = (u16)QuerySubModeStatus_020af3f4() >> 4;
    facing.y = 0;
    facing.x = -data_0205356c[angle];
    facing.z = -data_0205356c[(0x400 - angle) & 0xfff];
    cameraDot = VEC_DotProduct_01ff9e6c(&facing, &direction);
    if (distance <= 0x3000) {
        result->distance = distance;
        if (leaderDot >= 0xab8) {
            result->zone = 3;
        } else {
            result->zone = 2;
        }
    } else if (distance <= 0x5000) {
        result->distance = distance;
        if (cameraDot >= 0xab8) {
            result->zone = 1;
        } else {
            result->zone = 0;
        }
    } else if (distance <= config->midLimit) {
        result->distance = distance;
        result->zone = 0;
    } else if (distance <= config->farLimit) {
        result->distance = distance;
        result->zone = -1;
    }
}
