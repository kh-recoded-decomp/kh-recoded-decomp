#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

typedef struct Ov083State {
    u8 pad_00[0xb8];
    u8 window[0x34];
} Ov083State;

extern void Text_VSNPrintfWide_0202e09c(u16 *dst, u32 length, const u16 *format, va_list args);
extern void DrawTextAnchored_020015a0(void *window, int x, int y, int color, u32 flags, const u16 *text);

void DrawFormattedText_020bf56c(Ov083State *state, int x, int y, int color, const u16 *format, ...)
{
    u16 text[0x10];
    va_list args;

    va_start(args, format);
    Text_VSNPrintfWide_0202e09c(text, 0x10, format, args);
    DrawTextAnchored_020015a0(state->window, x, y, color, 0x20, text);
}