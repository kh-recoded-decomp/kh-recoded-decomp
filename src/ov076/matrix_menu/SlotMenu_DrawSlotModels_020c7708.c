#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SceneNode {
    u8 pad_00[0xa4];
    VecFx32 translation;
    VecFx32 scale;
    u8 pad_bc[0x48];
} SceneNode;

typedef struct LabelSource {
    u8 pad_00[0x10];
    u32 imageId;
} LabelSource;

typedef struct LabelEntry {
    LabelSource *source;
    u8 pad_04[8];
} LabelEntry;

typedef struct SlotMenu {
    u8 pad_00000[0x58];
    u8 images[0x824 - 0x58];
    LabelEntry labels[(0x11f18 - 0x824) / 12];
    s32 scrollY;
    u8 pad_11F1C[0x124cc - 0x11f1c];
    SceneNode slotNodes[8][3][6];
    SceneNode extraNodes[2];
    u8 pad_1B914[0x497f8 - 0x1b914];
    RecordEntry slotRecords[8];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;

extern void AdvanceAnimationTracks_0202ef24(SceneNode *node, fx32 step);
extern RecordEntry *GetActiveRecordEntryOrNull_02029548(int index);
extern void func_ov076_020c76f4(int x, int y, fx32 *outX, fx32 *outY);
extern void SceneNode_Draw_01ffb12c(SceneNode *node);
extern void DrawMenuImageModulated_020ccf14(void *images, u32 select, u32 pos, fx32 depth);

static inline void DrawSlotLabel(SlotMenu *menu, int itemId, s16 x, s16 y)
{
    DrawMenuImageModulated_020ccf14(menu->images, ((u16)menu->labels[itemId].source->imageId << 16) | 0x7fff,
                                    (x << 16) | (u16)y, 0);
}

void SlotMenu_DrawSlotModels_020c7708(SlotMenu *menu, int subScreen)
{
    int slot;
    int x;
    int y;
    int group;
    int lane;
    int column;
    int i;
    int width;
    u32 itemId;
    u16 handle;
    u32 pairHandle;
    RecordEntry *record;
    SceneNode *node;
    BOOL visible[2];

    for (group = 0; group < 8; group++) {
        for (lane = 0; lane < 3; lane++) {
            for (i = 0; i < 6; i++) {
                if (i != 0) {
                    AdvanceAnimationTracks_0202ef24(&menu->slotNodes[group][lane][i], 0x2000);
                }
            }
        }
    }
    AdvanceAnimationTracks_0202ef24(&menu->extraNodes[0], 0x2000);
    AdvanceAnimationTracks_0202ef24(&menu->extraNodes[1], 0x2000);

    for (slot = 0; slot < 8; slot++) {
        if (data_0205fe0c->slotHandles[slot * 2] == 0xffff) {
            continue;
        }
        for (column = 0; column < 3; column++) {
            if (column < 2) {
                visible[column] = FALSE;
            }
            if (column == 1 && data_0205fe0c->slotHandles[slot * 2 + 1] == 0xffff) {
                continue;
            }
            width = 0x40;
            if (column != 2) {
                width = 0x30;
            }
            x = subScreen != 0 ? 0 : 0x18;
            x += width;
            y = slot * 0x40 + 0x20 + column * 0x10 - menu->scrollY;
            if (y < 8 || y > 0x98) {
                continue;
            }
            if (column != 2) {
                handle = data_0205fe0c->slotHandles[slot * 2 + column];
                if (handle >= 0x200 && handle < 0x458) {
                    record = GetActiveRecordEntryOrNull_02029548((u16)(handle - 0x200));
                    itemId = (u8)record->category;
                    visible[column] = record->variant != 0;
                    if (visible[column]) {
                        node = &menu->slotNodes[slot][column][record->variant];
                        func_ov076_020c76f4(x, y, &node->translation.x, &node->translation.y);
                        node->translation.z = 0x80000;
                        SceneNode_Draw_01ffb12c(node);
                        menu->extraNodes[0].translation = node->translation;
                        menu->extraNodes[0].translation.x -= 0xb000;
                        SceneNode_Draw_01ffb12c(&menu->extraNodes[0]);
                    }
                } else {
                    itemId = handle;
                }
            } else {
                handle = data_0205fe0c->slotHandles[slot * 2];
                pairHandle = data_0205fe0c->slotHandles[slot * 2 + 1];
                if (handle < 0x200 || handle >= 0x458 || pairHandle < 0x200 || pairHandle >= 0x458) {
                    continue;
                }
                itemId = (u8)menu->slotRecords[slot].category;
                if (pairHandle >= 0x200 && pairHandle < 0x458 && visible[0] && visible[1]) {
                    record = GetActiveRecordEntryOrNull_02029548((u16)(pairHandle - 0x200));
                    node = &menu->slotNodes[slot][2][record->variant];
                    func_ov076_020c76f4(x, y, &node->translation.x, &node->translation.y);
                    node->translation.z = 0x80000;
                    SceneNode_Draw_01ffb12c(node);
                    menu->extraNodes[1].translation = node->translation;
                    menu->extraNodes[1].translation.x -= 0xf000;
                    SceneNode_Draw_01ffb12c(&menu->extraNodes[1]);
                }
            }
            DrawSlotLabel(menu, itemId, x, y);
        }
    }
}
