#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_0206084c;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *vec);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);
extern void func_0201d7bc(void *player, u32 trackMask, int pan);
extern void func_0201d78c(void *player, u32 trackMask, int volume);

void UpdateSoundSlotSpatial_0204cd64(int slot)
{
    u8 *base = data_0206084c;
    VecFx32 delta;
    fx32 distance;
    int pan;
    int volume;

    if ((*(u16 *)(slot + 0x14) & 4) != 0) {
        volume = 0;
    } else {
        pan = 0;
        VEC_Subtract_01ff9e3c((VecFx32 *)(slot + 8), (VecFx32 *)(base + 0xb4500), &delta);
        distance = VEC_Mag_01ff9f28(&delta);
        if ((*(u16 *)(slot + 0x14) & 2) == 0) {
            fx32 nearDist = *(fx32 *)(base + 0xb4720);
            if (distance <= nearDist) {
                volume = *(s16 *)(base + 0xb4728);
            } else if (distance < *(fx32 *)(base + 0xb4724)) {
                fx32 ratio = FX_Div_01ff9c84(distance - nearDist, *(fx32 *)(base + 0xb4724) - nearDist);
                volume = (0x1000 - ratio) * *(s16 *)(base + 0xb4728) >> 12;
            } else {
                volume = pan;
            }
        } else {
            volume = 0x7f;
        }
        if ((*(u16 *)(slot + 0x14) & 8) == 0 && distance > 0) {
            pan = FX_Div_01ff9c84(VEC_DotProduct_01ff9e6c(&delta, (VecFx32 *)(base + 0xb450c)), distance);
        }
        func_0201d7bc((void *)(slot + 0x1c), 0xffff, pan * *(s16 *)(base + 0xb47d6) >> 12);
    }
    func_0201d78c((void *)(slot + 0x1c), 0xffff, volume);
}
