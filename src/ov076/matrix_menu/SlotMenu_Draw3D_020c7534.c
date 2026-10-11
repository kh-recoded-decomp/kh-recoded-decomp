#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SceneNode {
    u8 pad_00[0xa8];
    s32 posY;
    u8 pad_ac[0x104 - 0xac];
} SceneNode;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x20];
    u8 panel[0x7fc0 - 0x24];
    s32 viewMode;
    u8 pad_07FC4[0x11ee6 - 0x7fc4];
    s16 focusColumn;
    u8 pad_11EE8[4];
    u8 rowHeight;
    u8 pad_11EED[0x11f18 - 0x11eed];
    s32 scrollY;
    u8 pad_11F1C[0x11fb8 - 0x11f1c];
    SceneNode nodes[5];
    u8 pad_124CC[0x1c6f4 - 0x124cc];
    u32 introTimer;
    u8 pad_1C6F8[0x49818 - 0x1c6f8];
    u16 columnFrames[8];
    s16 focusFrame;
    u8 pad_4982A[0x49854 - 0x4982a];
    u8 showCursor;
    u8 showBadge;
} SlotMenu;

typedef struct CameraState {
    u8 pad_000[0xd4];
    u32 dirtyFlags;
    u8 pad_0d8[0x218 - 0xd8];
    VecFx32 camPos;
    VecFx32 camUp;
    VecFx32 camTarget;
} CameraState;

extern char OverlayId0_00000000[];
extern CameraState data_0205a924;
extern u8 data_0205a92c[];
extern u8 data_0205a970[];

extern void MTX_OrthoW_02005f10(fx32 top, fx32 bottom, fx32 left, fx32 right, fx32 near, fx32 far, fx32 scaleW, void *mtx);
extern void func_01ff9b70(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *target, void *mtx);
extern int *func_01ffb2f8(SceneNode *node, int channel, int frame);
extern void SceneNode_Draw_01ffb12c(SceneNode *node);
extern void func_ov076_020cc81c(void *panel);
extern int func_ov076_020c44c0(SlotMenu *menu, int row);
extern void func_ov076_020c7708(SlotMenu *menu, int subScreen);

void SlotMenu_Draw3D_020c7534(SlotMenu *menu, int subScreen)
{
    int frame = 0;
    int i;
    int y;
    int row;
    SceneNode *node;

    VecFx32 camPos;
    VecFx32 camTarget;
    VecFx32 camUp;

    MTX_OrthoW_02005f10(0xc0000, 0, 0, 0x100000, 0, 0x400000, 0x200000, data_0205a92c);
    data_0205a924.dirtyFlags &= ~0x50;
    camPos.y = 0;
    camPos.x = 0;
    camPos.z = 0x400000;
    camUp.z = 0;
    camUp.y = FX32_ONE;
    camUp.x = 0;
    camTarget.z = 0;
    camTarget.y = 0;
    camTarget.x = 0;
    data_0205a924.camPos = camPos;
    data_0205a924.camUp = camUp;
    data_0205a924.camTarget = camTarget;
    func_01ff9b70(&camPos, &camUp, &camTarget, data_0205a970);
    data_0205a924.dirtyFlags &= ~0xe8;
    func_ov076_020cc81c(menu->panel);
    node = &menu->nodes[0];

    for (i = 0; i < 8; i++) {
        int value;
        if (i == menu->focusColumn && menu->focusFrame >= 0) {
            value = menu->focusFrame;
        } else {
            value = menu->columnFrames[i];
        }
        frame += value;
    }
    frame <<= 12;
    func_01ffb2f8(node, 0, frame);
    func_01ffb2f8(node, 2, frame);
    func_01ffb2f8(node, 3, frame);
    SceneNode_Draw_01ffb12c(node);

    if (subScreen == 0 && menu->showCursor) {
        SceneNode_Draw_01ffb12c(&menu->nodes[1]);
    }
    if (menu->state == 10) {
        SceneNode_Draw_01ffb12c(&menu->nodes[2]);
    }
    if (menu->showBadge) {
        SceneNode_Draw_01ffb12c(&menu->nodes[3]);
    }

    if (menu->state == 1 && subScreen == 0 && menu->introTimer < 0x14 && menu->viewMode == 4) {
        row = (int)OverlayId0_00000000;
        y = menu->rowHeight + 8 - menu->scrollY;
        while (y < 0) {
            y += menu->rowHeight;
            row++;
        }
        do {
            if (func_ov076_020c44c0(menu, row)) {
                menu->nodes[4].posY = (0xc0 - y) << 12;
                SceneNode_Draw_01ffb12c(&menu->nodes[4]);
            }
            row++;
            y += menu->rowHeight;
        } while (y < 0xa0);
    }
    func_ov076_020c7708(menu, subScreen);
}
