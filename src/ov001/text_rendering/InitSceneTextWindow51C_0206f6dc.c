#include "nitro/types.h"

typedef struct TextWindowLayout {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 tileOffset;
    u16 palette;
    u16 unk_0C;
    u16 unk_0E;
} TextWindowLayout;

extern const TextWindowLayout data_ov001_0209dc34;
extern void *func_ov001_0207123c(void *owner);
extern void *UpdateWidgetLayerDefault_020b9df0(void *widgets, int layer);
extern void func_020014b0(void *window, int bgLayer, void *charBase, void *font, TextWindowLayout *layout);

void InitSceneTextWindow51C_0206f6dc(u8 *scene)
{
    TextWindowLayout layout = data_ov001_0209dc34;

    func_020014b0(scene + 0x51c, 3, UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(scene), 0xb), scene + 0x78,
                  &layout);
}
