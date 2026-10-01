#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenPoint {
    fx32 x;
    fx32 y;
} ScreenPoint;

typedef struct SpriteSlot {
    u8 pad_00[0x10];
    ScreenPoint position;
    u8 pad_18[0xc];
    u8 isVisible;
    u8 pad_25[0xb];
} SpriteSlot;

typedef struct ScreenManager {
    u8 pad_00[0x30];
    SpriteSlot sprite;
    u32 vramOffset;
} ScreenManager;

typedef struct VariantTable {
    s8 entries[10];
} VariantTable;

extern ScreenManager *data_ov001_020a0480;
extern const ScreenPoint data_ov001_0209da6c;
extern const VariantTable data_ov001_0209da74;
extern void func_ov001_02069fb4(SpriteSlot *slot, u32 resourceKey);

void LoadCenteredScreenSprite_0206a860(int variant)
{
    VariantTable table = data_ov001_0209da74;

    func_ov001_02069fb4(&data_ov001_020a0480->sprite,
                        0x80000000 | ((data_ov001_020a0480->vramOffset + 0x8000) & 0xfffffc) << 7 |
                            (table.entries[variant] & 0x1ff));
    data_ov001_020a0480->sprite.isVisible = 1;
    data_ov001_020a0480->sprite.position = data_ov001_0209da6c;
}
