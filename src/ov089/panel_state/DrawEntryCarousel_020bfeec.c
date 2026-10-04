#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    int index;
    u8 node[0xa4];
    VecFx32 translate;
    VecFx32 scale;
    u8 pad_c0[0x48];
} EntryModel;

typedef struct {
    EntryModel entries[7];
    void *defs;
    fx32 scrollX;
    u8 pad_740[4];
    int entryCount;
    int cursor;
    u8 camera[0x28];
} Ov089Menu;

extern VecFx32 data_ov089_020c04f4;

extern void camera_commit_projection_0202a814(void *camera);
extern void AdvanceAnimationTracks_0202ef24(void *node, fx32 step);
extern void SceneNode_Draw_01ffb12c(void *node);
extern fx32 FX_Div_01ff9c84(fx32 numerator, fx32 denominator);

void DrawEntryCarousel_020bfeec(Ov089Menu *menu)
{
    VecFx32 pos = data_ov089_020c04f4;
    int count;
    int i;
    int index;
    fx32 spacing = 0xc800;
    fx32 dist;
    fx32 scale;
    EntryModel *entry;

    camera_commit_projection_0202a814(menu->camera);
    count = menu->entryCount;
    if (count == 1) {
        index = menu->cursor;
        entry = &menu->entries[index];
        entry->scale.x = menu->entries[index].scale.y = menu->entries[index].scale.z = 0x800;
        entry->translate = pos;
        AdvanceAnimationTracks_0202ef24(entry->node, 0x1000);
        SceneNode_Draw_01ffb12c(entry->node);
        return;
    }
    for (i = 0; i < count; i++) {
        pos.x = (i - 2) * spacing + menu->scrollX;
        index = (count + (menu->cursor - 2 + i + count) % count) % count;
        dist = pos.x;
        if (dist > -spacing && dist < spacing) {
            if (dist < 0) {
                dist = -dist;
            }
            scale = 0x400 - FX_Div_01ff9c84((fx32)(((s64)dist * 0x400 + 0x800) >> 12), spacing);
            scale += 0x400;
        } else {
            scale = 0x400;
        }
        entry = &menu->entries[index];
        entry->scale.z = scale;
        entry->scale.y = scale;
        entry->scale.x = scale;
        entry->translate = pos;
        AdvanceAnimationTracks_0202ef24(entry->node, 0x1000);
        SceneNode_Draw_01ffb12c(entry->node);
        count = menu->entryCount;
    }
}
