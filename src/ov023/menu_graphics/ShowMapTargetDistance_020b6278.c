#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapMenu {
    u8 pad_00[0x40];
    BOOL markerShown;
    u8 pad_44[0x14];
    u8 renderer[0x6444];
    s32 markerSlot;
} MapMenu;

extern fx32 FixedPointMultiply12(fx32 left, fx32 right);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void func_0204f378(void *owner, int slot, int value);
extern void func_0204f298(void *owner, int slot, fx32 scale);
extern void SetClampedFadeLevel_0204f448(void *owner, int level);
extern void func_ov023_020b61a0(MapMenu *menu, int blend);

void ShowMapTargetDistance_020b6278(MapMenu *menu, void *renderer, fx32 distance)
{
    fx32 scale;
    int level;
    int blend;

    if (distance < 0x1c000) {
        if (distance >= 0x5000) {
            scale = 0x800 - FX_Div_01ff9c84(FixedPointMultiply12(0x333, distance - 0x5000), 0x17000);
            level = (FX_Div_01ff9c84(FixedPointMultiply12(0x3000 - (distance - 0x5000), 0x8000), 0x3000) >> 12) + 8;
            if (level > 16) {
                level = 16;
            } else if (level < 8) {
                level = 8;
            }
            blend = 0;
        } else {
            scale = 0x1000 - FX_Div_01ff9c84(FixedPointMultiply12(0x800, distance), 0x5000);
            blend = FX_Div_01ff9c84(FixedPointMultiply12(scale - 0x800, 0x10000), 0x800) >> 12;
            level = 16;
        }
        func_0204f378(renderer, menu->markerSlot, 1);
        menu->markerShown = TRUE;
    } else {
        scale = 0x4cd;
        func_0204f378(renderer, menu->markerSlot, 1);
        menu->markerShown = TRUE;
        level = 8;
        blend = 0;
    }
    func_0204f298(renderer, menu->markerSlot, FixedPointMultiply12(scale, 0x1800));
    SetClampedFadeLevel_0204f448(renderer, level);
    func_ov023_020b61a0(menu, blend);
}
