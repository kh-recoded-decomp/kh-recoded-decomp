#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 param;
    u16 palette;
} TextFrame;

typedef struct {
    u8 pad_00[0x94];
    TextFrame statsFrame;
    u8 pad_a0[0xc9e8 - 0xa0];
    int messages[3];
    u8 pad_c9f4[0xcc6c - 0xc9f4];
    int introStep;
} MenuScene;

extern BOOL IsGlobalPackedBitSet_02027304(int bit);
extern void SetGlobalPackedBit_02027320(int bit);
extern void SetSceneMode_020c173c(s32 mode, MenuScene *scene);
extern void *func_ov027_020ba2a8(int *messages, int index);
extern void QueuePopup_020c27d8(s32 x, s32 y, const void *text, s32 param);
extern s32 GetPopupState_020c27e4(void);

void RunIntroPopupStep_020c1790(MenuScene *scene)
{
    int height;
    int width;
    int base;
    void *text;

    switch (scene->introStep) {
    case 0:
        if (IsGlobalPackedBitSet_02027304(0xf5c)) {
            SetSceneMode_020c173c(0, scene);
            return;
        }
        scene->introStep++;
        break;
    case 1:
        base = scene->statsFrame.param;
        width = scene->statsFrame.width;
        height = scene->statsFrame.height;
        text = func_ov027_020ba2a8(scene->messages, 7);
        QueuePopup_020c27d8(0x80, 0x60, text, width * height + base);
        scene->introStep++;
        break;
    case 2:
        if (GetPopupState_020c27e4() == 0) {
            SetGlobalPackedBit_02027320(0xf5c);
            SetSceneMode_020c173c(0, scene);
        }
        break;
    }
}
