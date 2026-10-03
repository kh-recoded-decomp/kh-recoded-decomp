#include "nitro/types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

typedef struct {
    u8 pad_00[0x14];
    void *glyphTiles;
} MessageFont;

typedef struct {
    u8 data[0x1c];
} WindowAnim;

typedef struct {
    s32 state;
    u32 owner;
    u8 pad_0008[0x9c08 - 8];
    MessageFont *font;
    s16 x;
    s16 y;
    u16 width;
    u16 height;
    WindowAnim anim;
    u32 onClose;
    u32 closeParam;
    u32 active : 1;
    u32 closing : 1;
    u32 finished : 1;
} MessageWindow;

extern void func_02052514(WindowAnim *anim, int value0, int value1, int value2, int value3);
extern void func_0205255c(WindowAnim *anim);
extern void *G2_GetBG1CharPtr_020070cc(void);
extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);

void InitMessageWindow_020c83dc(MessageWindow *window, u32 owner, s16 x, s16 y, u16 width, u16 height,
                                int animParam, u32 onClose, u32 closeParam)
{
    u32 planes;

    window->state = 0;
    window->owner = owner;
    window->x = x + (0x20 - width) / 2;
    window->y = y;
    window->width = width;
    window->height = height;
    window->onClose = onClose;
    window->closeParam = closeParam;
    window->active = FALSE;
    window->closing = FALSE;
    window->finished = FALSE;
    func_02052514(&window->anim, 0, 0, 0x1000, animParam);
    func_0205255c(&window->anim);
    MIi_CpuCopyFast_01ff878c(window->font->glyphTiles, G2_GetBG1CharPtr_020070cc(), 0x140);
    SetSecondaryElementEnabled_020bc084(FALSE);
    planes = (REG_DISPCNT & 0x1f00) >> 8;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes | 2) << 8);
}
