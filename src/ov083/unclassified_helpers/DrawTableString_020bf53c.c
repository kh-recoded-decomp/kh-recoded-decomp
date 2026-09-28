#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct ScreenState {
    u8 pad_000[0xb8];
    TextLayer textLayers[2];
    u8 pad_120[0x150 - 0x120];
    StringTable strings;
} ScreenState;

extern u16 *func_ov027_020ba2a8(StringTable *table, int index);
extern void func_020015a0(TextLayer *layer, int x, int y, int color, int flags, const u16 *text);

void DrawTableString_020bf53c(ScreenState *screen, int x, int y, int stringIndex) {
    func_020015a0(&screen->textLayers[0], x, y, 6, 8, func_ov027_020ba2a8(&screen->strings, stringIndex));
}
