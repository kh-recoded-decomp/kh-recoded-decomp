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

extern MenuScene *data_ov001_020a048c;
extern const char sOv001_FormatSFormat02d_0209ea90[];
extern const char sOv001_FormatSFormat02dFormatD_0209eac0[];
extern const char sOv001_Pent_0209eab8[];

extern void *FindGroupItemById(u32 id, int groupIndex);
extern int OS_SPrintf();
extern WorldMarker *FindWorldCollisionEntry(void *name);

void GetMenuItemWorldMarker(int variant, u32 itemId, VecFx32 *position, u16 *angle)
{
    char name[16];
    WorldMarker *marker;

    FindGroupItemById(itemId, data_ov001_020a048c->selected);
    if (variant == 0) {
        OS_SPrintf(name, sOv001_FormatSFormat02d_0209ea90, sOv001_Pent_0209eab8, itemId);
    } else {
        OS_SPrintf(name, sOv001_FormatSFormat02dFormatD_0209eac0, sOv001_Pent_0209eab8, itemId, variant);
    }
    marker = FindWorldCollisionEntry(name);
    position->x = marker->position.x;
    position->y = marker->position.y;
    position->z = marker->position.z;
    *angle = marker->angle;
}


