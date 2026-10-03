#include "nitro/types.h"
#include "nitro/fx_types.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct SceneNode {
    u8 pad_00[0xa4];
    VecFx32 translation;
    VecFx32 scale;
    u8 pad_bc[0x1c];
    u8 blendTable[0x2c];
} SceneNode;

typedef struct ModelIdPair {
    u32 ids[2];
} ModelIdPair;

typedef struct SlotMenu {
    u8 pad_00000[0x18];
    s32 slotArchive;
    s32 commonArchive;
    u8 pad_00020[0x11fb8 - 0x20];
    SceneNode cursorNodes[5];
    SceneNode slotNodes[8][3][6];
    SceneNode extraNodes[2];
} SlotMenu;

extern const u32 data_ov076_020cd0a0[];
extern const ModelIdPair data_ov076_020cd0b8;

extern void func_0202ecf8(SceneNode *node, u32 fileId, int count, int heapId);
extern void selectJointAnimationBlend_0202f2cc(SceneNode *node, int trackIndex, void *blendTable, int blendIndex);

void SlotMenu_InitModels_020c6954(SlotMenu *menu)
{
    VecFx32 offset;
    ModelIdPair extraIds;
    SceneNode *extras[2];
    SceneNode *node;
    int slot;
    int column;
    int i;
    u32 j;

    node = &menu->cursorNodes[0];
    func_0202ecf8(node, ARCHIVE_FILE_ID(menu->commonArchive, 0), 1, 0xe);
    node->translation.x = 0x20000;
    node->translation.y = 0x10000;
    node->translation.z = 0x200000;
    node->scale.z = 0xa000;
    node->scale.y = 0xa000;
    node->scale.x = 0xa000;
    selectJointAnimationBlend_0202f2cc(node, 0, node->blendTable, 0);
    selectJointAnimationBlend_0202f2cc(node, 2, node->blendTable, 0);
    selectJointAnimationBlend_0202f2cc(node, 3, node->blendTable, 0);

    node = &menu->cursorNodes[1];
    func_0202ecf8(node, ARCHIVE_FILE_ID(menu->slotArchive, 3), 1, 0xe);
    node->translation.x = 0x80000;
    node->translation.y = 0x60000;
    node->translation.z = 0x100000;
    node->scale.z = 0xa000;
    node->scale.y = 0xa000;
    node->scale.x = 0xa000;

    node = &menu->cursorNodes[2];
    func_0202ecf8(node, ARCHIVE_FILE_ID(menu->commonArchive, 1), 1, 0xe);
    offset.x = 0x80000;
    offset.y = 0x60000;
    offset.z = 0x300000;
    node->translation = offset;
    node->scale.z = 0xa000;
    node->scale.y = 0xa000;
    node->scale.x = 0xa000;

    node = &menu->cursorNodes[3];
    func_0202ecf8(node, ARCHIVE_FILE_ID(menu->commonArchive, 2), 1, 0xe);
    node->scale.z = 0xa000;
    node->scale.y = 0xa000;
    node->scale.x = 0xa000;

    node = &menu->cursorNodes[4];
    func_0202ecf8(node, ARCHIVE_FILE_ID(menu->commonArchive, 3), 1, 0xe);
    node->translation.x = 0x40000;
    node->translation.z = 0x100000;
    node->scale.z = 0xa000;
    node->scale.y = 0xa000;
    node->scale.x = 0xa000;

    for (slot = 0; slot < 8; slot++) {
        for (column = 0; column < 3; column++) {
            for (i = 0; i < 6; i++) {
                if (i != 0) {
                    node = &menu->slotNodes[slot][column][i];
                    func_0202ecf8(node, ARCHIVE_FILE_ID(menu->slotArchive, data_ov076_020cd0a0[i] & 0x1ff), 1, 0xe);
                    node->scale.z = 0xa000;
                    node->scale.y = node->scale.z;
                    node->scale.x = node->scale.y;
                    selectJointAnimationBlend_0202f2cc(node, 2, node->blendTable, 0);
                }
            }
        }
    }

    extraIds = data_ov076_020cd0b8;
    extras[0] = &menu->extraNodes[0];
    extras[1] = &menu->extraNodes[1];
    for (j = 0; j < 2; j++) {
        node = extras[j];
        func_0202ecf8(node, (extraIds.ids[j] & 0x1ff) | ARCHIVE_FILE_ID(menu->slotArchive, 0), 1, 0xe);
        node->scale.z = 0xa000;
        node->scale.y = node->scale.z;
        node->scale.x = node->scale.y;
        selectJointAnimationBlend_0202f2cc(node, 2, node->blendTable, 0);
    }
}
