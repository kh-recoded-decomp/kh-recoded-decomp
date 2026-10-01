#include "nitro/types.h"

typedef struct FieldGraphics {
    u8 pad_00[0x24];
    void *charData;
} FieldGraphics;

typedef struct FieldScene {
    u8 pad_000[0x5a4];
    FieldGraphics *graphics;
} FieldScene;

extern void *func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(void *widgets, int layer);
extern int GFXi_EnqueueCommand_02014090(int command, int offset, void *data, int size);
extern void func_ov027_020b9e00(void *widgets, int layer);

void LoadFieldBottomRowTiles_0206ed30(FieldScene *scene)
{
    void *charData = scene->graphics->charData;
    void *widgets = func_ov001_0207123c();
    u16 *screen = UpdateWidgetLayerDefault_020b9df0(widgets, 0x19);
    int tile = 0;
    int y;
    int x;

    GFXi_EnqueueCommand_02014090(0x15, 0x1000, charData, 0x780);
    for (y = 0x16; y < 0x18; y++) {
        for (x = 1; x < 0x1f; x++) {
            screen[y * 32 + x] = (tile + 0x80) | 0x1000;
            tile++;
        }
    }
    func_ov027_020b9e00(widgets, 0x19);
}
