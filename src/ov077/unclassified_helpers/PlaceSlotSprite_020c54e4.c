#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} PointFx32;

typedef struct {
    int x;
    int y;
    u8 pad_08[0xc];
    int id;
} SpriteSlot;

extern void func_0204f13c(void *sprite, int id, PointFx32 *pos);

void PlaceSlotSprite_020c54e4(SpriteSlot *slot, void *sprite, BOOL shifted)
{
    PointFx32 pos;
    int offset;

    if (shifted) {
        offset = 0x20;
    } else {
        offset = 0;
    }
    pos.x = (slot->x - offset) << 12;
    pos.y = slot->y << 12;
    func_0204f13c(sprite, slot->id, &pos);
}


