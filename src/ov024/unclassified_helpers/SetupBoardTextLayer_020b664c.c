#include "nitro/types.h"

typedef struct TextColors {
    u16 colors[8];
} TextColors;

typedef struct BoardState {
    char pad0000[8];
    void *widget;
    char pad000c[0x64fc - 0xc];
    int textReady;
    char layer[0x650c - 0x6500];
    char fontA[0xc];
    char fontB[0xc];
    char textLayer[0x66e0 - 0x6524];
    int useCustomFont;
} BoardState;

typedef struct BoardGlobals {
    BoardState *state;
    int unk04;
    void *widget;
} BoardGlobals;

extern TextColors data_ov024_020b7320;
extern BoardGlobals data_ov024_020b7520;
extern char data_ov024_020b7494[];
extern char data_ov024_020b74ac[];
extern char data_ov024_020b74c4[];

extern void *func_ov027_020b9df0(void *widget, int layer);
extern void func_ov027_020b9e00(void *widget, int layer);
extern void func_ov027_020ba25c(void *layer, u32 key, int value);
extern void func_02001458(void *font, const char *path);
extern void func_020014d0(void *textLayer, int count, void *screen, void *font, TextColors *colors);
extern void *func_ov001_020711e0(void);
extern int func_0202cc6c(const char *path, int heap, int flags);
extern void func_0202cd78(int handle);

void SetupBoardTextLayer_020b664c(void)
{
    TextColors colors = data_ov024_020b7320;
    void *widget = data_ov024_020b7520.state->widget;
    void *screen = func_ov027_020b9df0(widget, 0x18);
    int handle;

    if (data_ov024_020b7520.state->useCustomFont) {
        func_02001458(data_ov024_020b7520.state->fontA, data_ov024_020b7494);
        func_020014d0(data_ov024_020b7520.state->textLayer, 4, screen, data_ov024_020b7520.state->fontA, &colors);
        func_02001458(data_ov024_020b7520.state->fontB, data_ov024_020b74ac);
    } else {
        func_020014d0(data_ov024_020b7520.state->textLayer, 4, screen, func_ov001_020711e0(), &colors);
    }
    func_ov027_020b9e00(widget, 0x18);
    handle = func_0202cc6c(data_ov024_020b74c4, 0xe, 0);
    func_ov027_020ba25c(data_ov024_020b7520.state->layer, ((handle + 0x8000) & 0xfffffc) << 7 | 0x80000007, 1);
    func_0202cd78(handle);
    data_ov024_020b7520.state->textReady = 1;
}
