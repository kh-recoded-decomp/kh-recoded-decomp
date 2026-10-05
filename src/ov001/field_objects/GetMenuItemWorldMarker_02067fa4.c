#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct WorldMarker {
    u8 pad_00[8];
    VecFx32 position;
    s32 angle;
} WorldMarker;

typedef struct MenuScene {
    u8 pad_00[0xd];
    s8 selected;
} MenuScene;

extern MenuScene *data_ov001_020a046c;
extern const char data_ov001_0209ea70[];
extern const char data_ov001_0209eaa0[];
extern const char data_ov001_0209ea98[];

extern void *FindGroupItemById_02067108(u32 id, int groupIndex);
extern int OS_SPrintf_02002428();
extern WorldMarker *FindWorldCollisionEntry_02036548(void *name);

void GetMenuItemWorldMarker_02067fa4(int variant, u32 itemId, VecFx32 *position, u16 *angle)
{
    char name[16];
    WorldMarker *marker;

    FindGroupItemById_02067108(itemId, data_ov001_020a046c->selected);
    if (variant == 0) {
        OS_SPrintf_02002428(name, data_ov001_0209ea70, data_ov001_0209ea98, itemId);
    } else {
        OS_SPrintf_02002428(name, data_ov001_0209eaa0, data_ov001_0209ea98, itemId, variant);
    }
    marker = FindWorldCollisionEntry_02036548(name);
    position->x = marker->position.x;
    position->y = marker->position.y;
    position->z = marker->position.z;
    *angle = marker->angle;
}


