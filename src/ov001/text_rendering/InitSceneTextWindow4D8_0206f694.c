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

extern const TextWindowLayout data_ov001_0209dc24;
extern void func_020014b0(void *window, int bgLayer, void *charBase, void *font, TextWindowLayout *layout);

void InitSceneTextWindow4D8_0206f694(u8 *scene)
{
    TextWindowLayout layout = data_ov001_0209dc24;

    func_020014b0(scene + 0x4d8, 3, 0, scene + 0x78, &layout);
}
