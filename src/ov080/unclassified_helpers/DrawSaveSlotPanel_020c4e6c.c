#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 x;
    fx32 y;
} Position2D;

typedef struct {
    u8 pad_00[0x10];
    int bgId;
} SlotFrame;

typedef struct {
    s32 status : 8;
    s32 frameIndex : 8;
    u32 statusHigh : 16;
    u8 pad_04[2];
    s16 emptyElement;
    s16 filledElement;
    u8 pad_0A[2];
    void *cursorElement;
    SlotFrame *frames[5];
    u16 playerName[11];
    u16 worldName[10];
    u16 playTime[(0x3830 - 0x4e) / 2];
} SaveSlot;

typedef struct {
    u8 slotIndex;
    u8 pad_01[0x2b];
    Position2D origin;
    u8 pad_34[0x1c];
    void *tagTracker;
    void *panel;
    u8 pad_58[0x20];
    SaveSlot slots[2];
    u8 pad_70D8[0x3760];
    const u16 *playTimeLabel;
    u8 pad_A83C[4];
    const u16 *emptyLabel;
    u8 pad_A844[0x68];
    int textLayer[8];
} SaveSelectScreen;

extern void *func_ov039_020bc994(void);
extern void Obj_SetField14_02001490(int *layer, void *font);
extern void func_ov039_020bc14c(int bgId, int x, int y, int width, int height);
extern void func_0204f378(void *panel, int index, BOOL visible);
extern void func_0204f13c(void *panel, int index, Position2D *position);
extern void DrawTextAnchored_020015a0(int *layer, int x, int y, int color, u32 flags, const u16 *text);
extern int func_02001908(int *layer, const u16 *text, int flags);
extern void func_ov039_020be528(int *layer, int x, int y, int color, u32 flags, const u16 *text, u32 style);
extern void func_ov027_020b81e8(void *tracker, SlotFrame *frame, int x, int y);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, SlotFrame *frame);
extern Position2D *func_ov027_020b91a8(void *panel, void *element);
extern void func_ov027_020b9580(void *panel, void *element, BOOL visible);
extern void func_ov027_020b91c8(void *panel, void *element, Position2D *position, int mode);

void DrawSaveSlotPanel_020c4e6c(SaveSelectScreen *screen, u8 slotIndex)
{
    SaveSlot *slot;
    void *panel;
    u16 y;
    void *font;
    const u16 *label;
    u32 isSelected;
    int topY;
    int bottomY;
    int nameX;
    int row;
    u8 x;
    struct {
        Position2D offset;
        Position2D empty;
        Position2D filled;
    } pos;
    int nameWidth;
    const u16 *emptyLabel;

    slot = &screen->slots[slotIndex];
    panel = screen->panel;
    isSelected = (u8)(slotIndex == screen->slotIndex);
    x = isSelected * 8 + 30;
    y = slotIndex * 40 + 12;
    font = func_ov039_020bc994();

    Obj_SetField14_02001490(screen->textLayer, font);
    pos.offset.x = isSelected * 8 * FX32_ONE;
    pos.offset.y = slotIndex * 5 << 15;
    pos.empty.x = screen->origin.x + pos.offset.x;
    pos.empty.y = screen->origin.y + pos.offset.y;
    pos.filled.x = pos.offset.x + 0x80000;
    pos.filled.y = pos.offset.y + 0x48000;
    row = slotIndex * 5 + 7;
    func_ov039_020bc14c(slot->frames[0]->bgId, 3, row, 0x1b, 5);

    switch (slot->status) {
    case 0:
        func_0204f378(panel, slot->emptyElement, FALSE);
        func_0204f378(panel, slot->filledElement, TRUE);
        func_0204f13c(panel, slot->filledElement, &pos.filled);
        break;
    case 1:
        func_0204f378(panel, slot->emptyElement, FALSE);
        func_0204f378(panel, slot->filledElement, FALSE);
        emptyLabel = screen->emptyLabel;
        DrawTextAnchored_020015a0(screen->textLayer, x + 0x55, y + 8, 0xb, 0x10, emptyLabel);
        DrawTextAnchored_020015a0(screen->textLayer, x + 0x54, y + 7, 0xa, 0x10, emptyLabel);
        break;
    default:
        func_0204f378(panel, slot->filledElement, FALSE);
        func_0204f378(panel, slot->emptyElement, slot->status == 3);
        func_0204f13c(panel, slot->emptyElement, &pos.empty);
        nameWidth = func_02001908(screen->textLayer, screen->playTimeLabel, 0);
        label = screen->playTimeLabel;
        topY = y + 15;
        DrawTextAnchored_020015a0(screen->textLayer, x + 1, topY, 7, 8, label);
        bottomY = y + 14;
        DrawTextAnchored_020015a0(screen->textLayer, x, bottomY, 6, 8, label);
        nameX = x + 6 + nameWidth;
        DrawTextAnchored_020015a0(screen->textLayer, nameX + 1, topY, 3, 8, slot->playerName);
        DrawTextAnchored_020015a0(screen->textLayer, nameX, bottomY, 2, 8, slot->playerName);
        func_ov039_020be528(screen->textLayer, x, y, 2, 8, slot->playTime, 0xac);
        Obj_SetField14_02001490(screen->textLayer, font);
        DrawTextAnchored_020015a0(screen->textLayer, x + 0xa9, topY, 3, 0x20, slot->worldName);
        DrawTextAnchored_020015a0(screen->textLayer, x + 0xa8, bottomY, 2, 0x20, slot->worldName);
        break;
    }

    func_ov027_020b81e8(screen->tagTracker, slot->frames[slot->frameIndex], (s16)(isSelected + 3), (s16)row);
    TagTracker_InvokeCallback_020b8210(screen->tagTracker, slot->frames[slot->frameIndex]);
    pos.filled = *func_ov027_020b91a8(screen->panel, slot->cursorElement);
    pos.filled.x += pos.offset.x;
    func_ov027_020b9580(screen->panel, slot->cursorElement, TRUE);
    func_ov027_020b91c8(screen->panel, slot->cursorElement, &pos.filled, 0);
}
