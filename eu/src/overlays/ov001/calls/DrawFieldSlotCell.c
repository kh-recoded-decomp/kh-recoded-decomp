#include "nitro/types.h"

typedef struct SlotNameTable {
    int messageIds[4];
} SlotNameTable;

typedef struct TextCanvas {
    u8 pad_00[0x24];
    u8 *pixels;
} TextCanvas;

typedef struct SlotCell {
    s32 cursorX;
    s32 cursorY;
    s32 slot;
    u8 pad_0c[4];
    s32 highlight;
    u8 pad_14[8];
    TextCanvas *canvas;
    u8 pad_20[8];
    u16 flags;
} SlotCell;

typedef struct SlotPanel {
    u8 pad_00[0xdc];
    s32 filledCount;
    u8 *blankTiles;
} SlotPanel;

typedef struct MessageSet MessageSet;

extern const SlotNameTable data_ov001_0209dec8;
extern const u16 data_ov001_0209eee8[];

extern const u16 *func_ov027_020ba2c8(MessageSet *messages, int index);
extern int GetFieldSlotValue(int index);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void *GetFieldFont1(void);
extern void func_02001620(int *context, u32 x, u32 y, u32 color, u32 flags, const u16 *text,
                          void *overrideFont, int maxWidth);

void DrawFieldSlotCell(SlotPanel *panel, int *layer, SlotCell *cell, MessageSet *messages, int slot)
{
    SlotNameTable table = data_ov001_0209dec8;
    const u16 *text = data_ov001_0209eee8;
    int value;

    if (slot == 0) {
        text = func_ov027_020ba2c8(messages, 0);
        cell->slot = 0;
        panel->filledCount++;
    } else {
        value = GetFieldSlotValue(slot - 1);
        if (value != -1) {
            text = func_ov027_020ba2c8(messages, table.messageIds[value]);
            if (cell->slot == -1) {
                panel->filledCount++;
            }
            cell->slot = slot;
        } else {
            if (cell->slot != -1) {
                panel->filledCount--;
            }
            cell->slot = -1;
        }
    }
    cell->cursorY = 0;
    cell->cursorX = 0;
    cell->highlight = -1;
    cell->flags |= 1;
    cell->flags |= 4;
    MIi_CpuCopyFast(panel->blankTiles, cell->canvas->pixels, 0x200);
    func_02001620(layer, 0, 4, 4, 0, text, GetFieldFont1(), 0x38);
}
