#include "nitro/types.h"
#include "nitro/fx_types.h"

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
    u8 pad_01[3];
    s32 step : 8;
    u32 stepHigh : 24;
    u8 pad_08[3];
    u8 overwriting;
    u8 pad_0C[0x20];
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
    int textLayer[26];
    void *messages;
} SaveSelectScreen;

extern void *func_ov039_020bc994(void);
extern void Obj_SetField14_02001490(int *layer, void *font);
extern void func_ov039_020bc14c(int bgId, int x, int y, int width, int height);
extern void func_0204f378(void *panel, int index, BOOL visible);
extern void func_0204f13c(void *panel, int index, Position2D *position);
extern void DrawTextAnchored_020015a0(int *layer, int x, int y, int color, u32 flags, const u16 *text);
extern int func_02001908(int *layer, const u16 *text, int flags);
extern void func_ov039_020be528(int *layer, int x, int y, int color, u32 flags, const u16 *text, u32 style);
extern void func_ov039_020be574(int *layer, int x, int y, int color, const u16 *text);
extern void func_ov027_020b81e8(void *tracker, SlotFrame *frame, int x, int y);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, SlotFrame *frame);
extern Position2D *func_ov027_020b91a8(void *panel, void *element);
extern void func_ov027_020b9580(void *panel, void *element, BOOL visible);
extern void func_ov027_020b91c8(void *panel, void *element, Position2D *position, int mode);
extern int func_ov039_020bc914(void);
extern const u16 *func_ov027_020ba2a8(void **messages, int id);
extern void *OS_SNPrintf_0202e080(u16 *dst, unsigned int len, const u16 *fmt, ...);

void DrawSlotDetailPanel_020c50f8(SaveSelectScreen *screen, int slotIndex)
{
    int i;
    SaveSlot *slot = &screen->slots[slotIndex];
    void *panel = screen->panel;
    u8 confirming = (screen->step == 1 && screen->overwriting && screen->slots[screen->slotIndex].status == 1) ? 1 : 0;
    u16 row = confirming ? 0 : 2;
    u16 y = row * 8 + 12;
    void *font = func_ov039_020bc994();
    Position2D positions[3];
    u16 text[128];
    SaveSlot *other;
    BOOL visible;
    int nameWidth;
    const u16 *emptyLabel;
    const u16 *label;
    int topY;
    int bottomY;
    u8 messageId;
    int color;
    int number;

    Obj_SetField14_02001490(screen->textLayer, font);
    positions[0].x = 0;
    positions[0].y = confirming ? 0 : 0x10000;
    positions[1].x = screen->origin.x;
    positions[1].y = screen->origin.y + positions[0].y;
    positions[2].x = 0x80000;
    positions[2].y = positions[0].y + 0x48000;
    func_ov039_020bc14c(slot->frames[0]->bgId, 3, 7, 0x1b, 10);

    for (i = 0; i < 2; i++) {
        other = &screen->slots[i];
        if (i != slotIndex) {
            func_0204f378(panel, other->emptyElement, FALSE);
            func_0204f378(panel, other->filledElement, FALSE);
            func_ov027_020b9580(screen->panel, other->cursorElement, FALSE);
        } else {
            switch (slot->status) {
            case 0:
                func_0204f378(panel, slot->emptyElement, FALSE);
                func_0204f378(panel, slot->filledElement, TRUE);
                func_0204f13c(panel, slot->filledElement, &positions[2]);
                break;
            case 1:
                func_0204f378(panel, slot->emptyElement, FALSE);
                func_0204f378(panel, slot->filledElement, FALSE);
                emptyLabel = screen->emptyLabel;
                DrawTextAnchored_020015a0(screen->textLayer, 0x73, y + 8, 0xb, 0x10, emptyLabel);
                DrawTextAnchored_020015a0(screen->textLayer, 0x72, y + 7, 0xa, 0x10, emptyLabel);
                break;
            default:
                func_0204f378(panel, slot->filledElement, FALSE);
                visible = TRUE;
                if (slot->status != 3) {
                    visible = FALSE;
                }
                func_0204f378(panel, slot->emptyElement, visible);
                func_0204f13c(panel, slot->emptyElement, &positions[1]);
                nameWidth = func_02001908(screen->textLayer, screen->playTimeLabel, 0);
                label = screen->playTimeLabel;
                topY = y + 15;
                DrawTextAnchored_020015a0(screen->textLayer, 0x1f, topY, 7, 8, label);
                bottomY = y + 14;
                DrawTextAnchored_020015a0(screen->textLayer, 0x1e, bottomY, 6, 8, label);
                DrawTextAnchored_020015a0(screen->textLayer, nameWidth + 0x25, topY, 3, 8, slot->playerName);
                nameWidth += 0x24;
                DrawTextAnchored_020015a0(screen->textLayer, nameWidth, bottomY, 2, 8, slot->playerName);
                func_ov039_020be528(screen->textLayer, 0x1e, y, 2, 8, slot->playTime, 0xac);
                Obj_SetField14_02001490(screen->textLayer, font);
                DrawTextAnchored_020015a0(screen->textLayer, 0xc7, topY, 3, 0x20, slot->worldName);
                DrawTextAnchored_020015a0(screen->textLayer, 0xc6, bottomY, 2, 0x20, slot->worldName);
                break;
            }
        }
    }

    if (screen->step == 1) {
        color = 2;
        if (screen->overwriting) {
            if (slot->status == 1) {
                messageId = 0x13;
                color = 10;
            } else {
                messageId = 6;
            }
        } else {
            messageId = slot->status == 0 ? 7 : (func_ov039_020bc914() != 3 ? 4 : 5);
        }
        number = screen->slotIndex + 1;
        OS_SNPrintf_0202e080(text, 0x80, func_ov027_020ba2a8(&screen->messages, messageId), number, number);
        func_ov039_020be574(screen->textLayer, 0x68, confirming ? 0x30 : 0x40, color, text);
        DrawTextAnchored_020015a0(screen->textLayer, 0x34, 0x53, 2, 0x10, func_ov027_020ba2a8(&screen->messages, 0xb));
        DrawTextAnchored_020015a0(screen->textLayer, 0x9c, 0x53, 2, 0x10, func_ov027_020ba2a8(&screen->messages, 0xc));
    }

    func_ov027_020b81e8(screen->tagTracker, slot->frames[slot->frameIndex], 3, (s16)(row + 7));
    TagTracker_InvokeCallback_020b8210(screen->tagTracker, slot->frames[slot->frameIndex]);
    positions[2] = *func_ov027_020b91a8(screen->panel, screen->slots[0].cursorElement);
    positions[2].x += positions[0].x;
    positions[2].y += row << 15;
    func_ov027_020b91c8(screen->panel, slot->cursorElement, &positions[2], 0);
}
