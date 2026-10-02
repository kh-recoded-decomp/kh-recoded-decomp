#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u32 *data_ov001_020a0508;
extern int Session_Exists_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);
extern void func_ov021_020af544(int kind, int value);
extern void func_ov042_020bd74c(u32 first, u32 second);
extern void func_ov021_020af8d4(VecFx32 *out, u32 angle);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_ov043_020bcb38(VecFx32 *pos, int id, int speed, fx32 radius);
extern void func_ov043_020bca50(int value);

void HandleSessionEffectEvent_0209cb64(int event, int value) {
    if (data_ov001_020a0508 == NULL || (*data_ov001_020a0508 & 0x10000) != 0) {
        return;
    }
    if (!Session_Exists_02063a24()) {
        return;
    }
    switch (func_ov001_02063a38()) {
    case 0:
    case 2:
    case 3:
    case 6:
        if (event == 1) {
            func_ov021_020af544(3, value);
        }
        break;
    case 4:
        if (event == 1) {
            func_ov042_020bd74c(0x333, 0xf000);
        }
        break;
    case 7:
        switch (event) {
        case 1: {
            int sign;
            VecFx32 position;
            VecFx32 direction;
            VecFx32 scaled;
            sign = random_next_scaled_0202aa04(2) != 0 ? 1 : -1;
            func_ov021_020af8d4(&direction, random_next_scaled_0202aa04(0x6488));
            scaled = direction;
            func_0204a5e4(&scaled, 0x1ec);
            position = scaled;
            func_ov043_020bcb38(&position, 0x333, (int)((s64)sign * 0x430), 0xa000);
            break;
        }
        case 2:
            func_ov043_020bca50((int)((s64)value * 0x3244 / 0xb4000));
            break;
        }
        break;
    }
}
