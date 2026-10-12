#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} Position2D;

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0x382c];
} SaveSlot;

typedef struct {
    u8 bytes[0x34];
} TextLayer;

typedef struct {
    u8 slotIndex;
    u8 drawnSlotIndex;
    u8 needsRedraw;
    u8 pad_03;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 promptOpen;
    u8 cursorRow;
    u8 readFailed;
    u8 overwriting;
    u8 pad_0C[0x18];
    u64 blinkStartTick;
    u8 pad_2C[0x24];
    void *tagTracker;
    void *panel;
    void *tagElement;
    u8 pad_5C[0x10];
    void *cursorElement;
    void *choiceElements[2];
    SaveSlot slots[2];
    u8 pad_70D8[0x376c];
    TextLayer layers[4];
    void *messages;
} SaveSelectScreen;

extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);
extern void DrawSaveSlotPanel_020c4e6c(SaveSelectScreen *screen, int slotIndex);
extern void DrawSlotDetailPanel_020c50f8(SaveSelectScreen *screen, int slotIndex);
extern void HideSaveSlotsShowPrompt_020c54b8(SaveSelectScreen *screen);
extern void func_ov027_020b91c8(void *panel, void *element, Position2D *position, int mode);
extern Position2D *func_ov027_020b91a8(void *panel, void *element);
extern void SetEntrySlotsVisible_020b9580(void *panel, void *element, BOOL visible);
extern void InvokeCallback40_020b8268(void *tracker, void *element);
extern void func_ov027_020b81e8(void *tracker, void *element, int x, int y);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *element);
extern int func_ov039_020bc914(void);
extern const u16 *func_ov027_020ba2a8(void **messages, int id);
extern void *OS_SNPrintf_0202e080(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern u64 OS_GetTick_02003fd4(void);

void RedrawSaveSelectScreen_020c5584(SaveSelectScreen *screen)
{
    u16 cursorX;
    int rowShift;
    BOOL showChoices;
    Position2D pos;
    u16 text[128];
    BOOL inPrompt;
    int i;
    s16 messageId;
    int color;
    u32 elapsed;
    u32 alpha;
    BOOL cursorVisible;

    if (screen->needsRedraw != 0) {
        cursorX = 4;
        rowShift = 0;
        inPrompt = TRUE;
        if (screen->step != 2) {
            inPrompt = FALSE;
        }
        showChoices = TRUE;
        if (!inPrompt && screen->step != 1) {
            showChoices = FALSE;
        }
        CallVirtualHandlerSlot1_02001574(&screen->layers[2], 0);
        if (!inPrompt) {
            if (screen->step == 0) {
                screen->cursorRow = screen->slotIndex;
                for (i = 0; i < 2; i++) {
                    DrawSaveSlotPanel_020c4e6c(screen, (u8)i);
                }
                pos.x = 0x20000;
                pos.y = (screen->slotIndex * 5 << 15) + 0x48000;
            } else {
                screen->cursorRow = 1;
                DrawSlotDetailPanel_020c50f8(screen, screen->slotIndex);
                if (screen->promptOpen == 0) {
                    pos.x = 0x20000;
                } else {
                    pos.x = 0x88000;
                }
                pos.y = 0x88000;
                cursorX--;
                rowShift = 1;
            }
            func_ov027_020b91c8(screen->panel, screen->cursorElement, &pos, 0);
        } else {
            HideSaveSlotsShowPrompt_020c54b8(screen);
            if (screen->promptOpen == 0) {
                pos.x = 0x20000;
            } else {
                pos.x = 0x88000;
            }
            pos.y = 0x60000;
            func_ov027_020b91c8(screen->panel, screen->cursorElement, &pos, 0);
        }
        Text_UploadTileBuffer_02001520(&screen->layers[2]);
        cursorVisible = TRUE;
        if (screen->step >= 3) {
            cursorVisible = FALSE;
        }
        SetEntrySlotsVisible_020b9580(screen->panel, screen->cursorElement, cursorVisible);
        InvokeCallback40_020b8268(screen->tagTracker, screen->tagElement);
        if (!inPrompt) {
            BOOL confirmOverwrite = FALSE;
            BOOL overwritePrompt = FALSE;
            if (screen->step == 1 && screen->overwriting) {
                overwritePrompt = TRUE;
            }
            if (overwritePrompt && screen->slots[screen->slotIndex].status == 1) {
                confirmOverwrite = TRUE;
            }
            if (confirmOverwrite) {
                rowShift = 0;
            } else if (screen->step != 0) {
                rowShift = 2;
            } else {
                rowShift = screen->cursorRow * 5 - rowShift;
            }
            func_ov027_020b81e8(screen->tagTracker, screen->tagElement, (s16)cursorX, (s16)(rowShift + 7));
            TagTracker_InvokeCallback_020b8210(screen->tagTracker, screen->tagElement);
        }
        if (showChoices) {
            pos = *func_ov027_020b91a8(screen->panel, screen->choiceElements[0]);
            if (inPrompt) {
                pos.y -= 0x28000;
            }
            func_ov027_020b91c8(screen->panel, screen->choiceElements[screen->promptOpen], &pos, 0);
            pos.x += 0x68000;
            func_ov027_020b91c8(screen->panel, screen->choiceElements[screen->promptOpen ^ 1], &pos, 0);
        }
        SetEntrySlotsVisible_020b9580(screen->panel, screen->choiceElements[0], showChoices);
        SetEntrySlotsVisible_020b9580(screen->panel, screen->choiceElements[1], showChoices);
        Text_UploadTileBuffer_02001520(&screen->layers[1]);
        color = 2;
        CallVirtualHandlerSlot1_02001574(&screen->layers[3], 0);
        if (screen->readFailed != 0) {
            messageId = (screen->readFailed & 1) ? 20 : 15;
            color = 10;
        } else {
            switch (screen->step) {
            case 0:
            case 1:
            case 7:
            case 8:
            case 9:
                if (screen->overwriting != 0) {
                    messageId = 8;
                    color = 10;
                } else {
                    messageId = func_ov039_020bc914() != 3 ? 2 : 3;
                }
                break;
            case 3:
                messageId = 16;
                color = 10;
                break;
            case 4:
                messageId = 13;
                break;
            case 5:
                messageId = 17;
                color = 10;
                break;
            case 6:
                messageId = 14;
                break;
            case 2:
                messageId = -1;
                break;
            }
        }
        if (messageId >= 0) {
            OS_SNPrintf_0202e080(text, 0x80, func_ov027_020ba2a8(&screen->messages, messageId), screen->slotIndex + 1);
        } else {
            text[0] = 0;
        }
        DrawTextAnchored_020015a0(&screen->layers[3], 2, 0, color, 8, text);
        Text_UploadTileBuffer_02001520(&screen->layers[3]);
        Text_UploadTileBuffer_02001520(&screen->layers[0]);
        screen->drawnSlotIndex = screen->slotIndex;
        screen->needsRedraw--;
    }
    elapsed = (u32)(((OS_GetTick_02003fd4() - screen->blinkStartTick) * 64) / 33514);
    if (elapsed >= 1000) {
        screen->blinkStartTick += (elapsed / 1000) * 33514000 / 64;
        elapsed %= 1000;
    }
    if (elapsed >= 500) {
        alpha = (1000 - elapsed) * 16 / 500;
    } else {
        alpha = elapsed * 16 / 500;
    }
    *(vu16 *)0x04000052 = (u16)alpha | 0x1000;
}
