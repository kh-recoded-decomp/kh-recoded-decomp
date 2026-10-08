#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} Position2D;

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    Position2D cursor;
    Position2D empty;
    Position2D filled;
} SlotLayout;

typedef struct {
    u8 pad_00[4];
    s16 baseRow;
    u8 pad_06[0xa];
    int userData;
} SlotFrame;

typedef struct {
    u8 pad_00[6];
    s16 emptyElement;
    s16 filledElement;
    u8 pad_0A[2];
    void *cursorElement;
    SlotFrame *frames[5];
    u8 pad_24[0x3830 - 0x24];
} SaveSlot;

typedef struct {
    u8 bytes[0x34];
} TextLayer;

typedef struct {
    u16 colors[8];
} WindowStyle;

typedef struct {
    int resource;
    int unk_04;
    int unk_08;
    int unk_0C;
} ObjManagerConfig;

typedef struct {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct {
    u8 pad_00[2];
    u8 needsRedraw;
    u8 pad_03[9];
    u8 initialized;
    u8 pad_0D[7];
    BOOL returnMode;
    u8 pad_18[0xc];
    u64 blinkStartTick;
    Position2D origin;
    u8 pad_34[0x1c];
    void *tagTracker;
    void *panel;
    void *tagElement;
    u8 pad_5C[0x10];
    void *cursorElement;
    void *choiceElements[2];
    SaveSlot slots[2];
    SaveData savedGame;
    const u16 *playTimeLabel;
    const u16 *unusedLabel;
    const u16 *emptyLabel;
    TextLayer layers[4];
    void *messages;
} SaveSelectScreen;

extern SaveData *data_0205fe0c;
extern SaveSelectScreen *data_ov080_020c5e00;
extern const WindowStyle data_ov080_020c5d38;
extern const ObjManagerConfig data_ov080_020c5d28;
extern const SlotLayout data_ov080_020c5d48;
extern const char data_ov080_020c5dc4[];
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As);
extern void G2x_SetBlendAlpha_02006850(vu16 *reg, int plane1, int plane2, int ev1, int ev2);
extern void *G2_GetBG0ScrPtr_02006de0(void);
extern void func_01ff8740(u32 value, void *dst, u32 size);
extern int func_ov039_020bc914(void);
extern void LoadSlotBgImage_020bc26c(int slot, u32 low, int screenIndex, int paletteIndex, void **fileOut);
extern void func_ov039_020bc414(int a, int b, int c);
extern void SetScreenLayerDirty_020bc104(int layerId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void OpenTextFrame_020be5b8(u32 position, u32 size, int layer, TextLayer *text, WindowStyle *style);
extern void LoadPackedFileView_020ba25c(void **view, const char *path, BOOL fromTail);
extern const u16 *func_ov039_020bcb20(SaveData *save);
extern BOOL SetTextColorIfFits_020bcd04(TextLayer *layer, int limit, const u16 *text);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern const u16 *func_ov027_020ba2a8(void **messages, int id);
extern void *func_ov039_020bc18c(void);
extern void *func_ov039_020bc1bc(void);
extern int BuildSlotImageParams_020bc220(int slot, u32 low);
extern void InitObjManagerAndMark_020b9060(void *panel, ObjManagerConfig *config);
extern void PXI_Init_020b9078(void *panel, int resource);
extern void func_ov027_020b8f98(void *panel, int resource, int count);
extern void func_ov027_020b7e24(void *tracker, int resource);
extern SlotFrame *FindActiveRecordById_020b8184(void *tracker, u32 recordId);
extern void *FindWidgetById_020b90a4(void *root, int id);
extern void func_ov027_020b91c8(void *panel, void *element, Position2D *position, int mode);
extern Position2D *func_ov027_020b91a8(void *panel, void *element);
extern s16 PXI_Init_0204f0b4(void *panel, int a, int b);
extern void func_0204f13c(void *panel, int index, Position2D *position);
extern SlotFrame *AddRecordFromTemplate_020b7ecc(void *tracker, SlotFrame *source, u16 id, int userData);
extern void func_ov027_020b81e0(void *tracker, SlotFrame *frame, int row);
extern void func_ov027_020b97b8(void *panel, void *element, int mode);
extern int func_ov039_020bc7f8(void);
extern void func_ov039_020bc7e0(int flags);
extern void func_0204f498(void *panel, int mode);
extern u64 OS_GetTick_02003fd4(void);
extern void StartCardWriteFromSlot_02027034(u8 slot);
extern BOOL PollSaveSlotReads_020c4d08(SaveSelectScreen *screen);

BOOL InitSaveSelectScreen_020c42b0(SaveSelectScreen *screen)
{
    BgGraphicsData bgData;
    WindowStyle style;
    SlotLayout layout;
    ObjManagerConfig config;
    void *file;
    SaveSlot *slot;
    u16 i;
    u16 nextId;
    void *panel;
    int rowOffset;
    u16 j;
    void *tracker;
    int variant;
    const u16 *title;
    BOOL returning;

    if (screen->initialized == 0) {
        GX_SetGraphicsMode_020066c4(1, 0, 0);
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;
        *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & 0x43) | 0x1c08);
        *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & 0x43) | 0x1e08);
        *(vu16 *)0x04000008 = (u16)(*(vu16 *)0x04000008 & ~3);
        *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & ~3) | 1);
        *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 2);
        *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 3);
        G2x_SetBlendAlpha_02006850((vu16 *)0x04000050, 2, 4, 0x10, 0);
        func_01ff8740(0, G2_GetBG0ScrPtr_02006de0(), 0x600);
        variant = 0;
        if (func_ov039_020bc914() == 3) {
            variant = 4;
        }
        LoadSlotBgImage_020bc26c(2, 0, (u16)variant, 0, &file);
        func_ov039_020bc414(3, 0, 0);
        SetScreenLayerDirty_020bc104(0xb);
        GetBgDataFromArchive_0202b554(&bgData, file, -1, 1, -1);
        GX_LoadBG2Char_02007a90(((CharacterData *)bgData.character)->data, 0, ((CharacterData *)bgData.character)->size);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
        style = data_ov080_020c5d38;
        OpenTextFrame_020be5b8(0x8, 0x20018, 0, &screen->layers[0], &style);
        OpenTextFrame_020be5b8(0x30001, 0x2000a, 0, &screen->layers[1], &style);
        OpenTextFrame_020be5b8(0x150000, 0x30020, 0, &screen->layers[3], &style);
        OpenTextFrame_020be5b8(0x60003, 0xc001a, 0, &screen->layers[2], &style);
        LoadPackedFileView_020ba25c(&screen->messages, data_ov080_020c5dc4, FALSE);
        if (func_ov039_020bc914() != 3) {
            title = func_ov039_020bcb20(data_0205fe0c);
            SetTextColorIfFits_020bcd04(&screen->layers[0], 0xac, title);
            DrawTextAnchored_020015a0(&screen->layers[0], 0xbe, 2, 2, 0x20, title);
        }
        DrawTextAnchored_020015a0(&screen->layers[1], 4, 3, 2, 8, func_ov027_020ba2a8(&screen->messages, func_ov039_020bc914() == 3));
        screen->playTimeLabel = func_ov027_020ba2a8(&screen->messages, 9);
        nextId = 9;
        screen->unusedLabel = func_ov027_020ba2a8(&screen->messages, 10);
        screen->emptyLabel = func_ov027_020ba2a8(&screen->messages, 0x12);
        tracker = func_ov039_020bc18c();
        panel = func_ov039_020bc1bc();
        config = data_ov080_020c5d28;
        layout = data_ov080_020c5d48;
        config.resource = BuildSlotImageParams_020bc220(2, 1);
        InitObjManagerAndMark_020b9060(panel, &config);
        PXI_Init_020b9078(panel, BuildSlotImageParams_020bc220(3, 1));
        func_ov027_020b8f98(panel, BuildSlotImageParams_020bc220(2, 3), 9);
        func_ov027_020b7e24(tracker, BuildSlotImageParams_020bc220(2, 2));
        screen->tagElement = FindActiveRecordById_020b8184(tracker, 1);
        screen->cursorElement = FindWidgetById_020b90a4(panel, 0);
        func_ov027_020b91c8(panel, screen->cursorElement, &layout.cursor, 0);
        screen->choiceElements[0] = FindWidgetById_020b90a4(panel, 5);
        screen->choiceElements[1] = FindWidgetById_020b90a4(panel, 6);
        layout.empty = *func_ov027_020b91a8(panel, FindWidgetById_020b90a4(panel, 7));
        screen->origin = layout.empty;
        i = 0;
        do {
            slot = &screen->slots[i];
            slot->cursorElement = FindWidgetById_020b90a4(panel, i + 2);
            j = 0;
            slot->emptyElement = PXI_Init_0204f0b4(panel, 2, 0);
            func_0204f13c(panel, slot->emptyElement, &layout.empty);
            slot->filledElement = PXI_Init_0204f0b4(panel, 0, 1);
            func_0204f13c(panel, slot->filledElement, &layout.filled);
            rowOffset = i * 4;
            do {
                if (i == 0) {
                    slot->frames[j] = FindActiveRecordById_020b8184(tracker, (u16)(j + 2));
                } else {
                    slot->frames[j] = AddRecordFromTemplate_020b7ecc(tracker, screen->slots[0].frames[j], nextId++, screen->slots[0].frames[j]->userData);
                }
                func_ov027_020b81e0(tracker, slot->frames[j], (s16)(rowOffset + screen->slots[0].frames[j]->baseRow));
                j++;
            } while (j < 5);
            layout.empty.y += 0x28000;
            layout.filled.y += 0x28000;
            i++;
        } while (i < 2);
        func_ov027_020b97b8(panel, FindWidgetById_020b90a4(panel, 1), 2);
        func_ov027_020b97b8(panel, screen->choiceElements[0], 2);
        func_ov027_020b97b8(panel, screen->choiceElements[1], 2);
        screen->tagTracker = tracker;
        screen->panel = panel;
        returning = TRUE;
        if (func_ov039_020bc7f8() != 0x4000) {
            returning = FALSE;
        }
        screen->returnMode = returning;
        if (returning) {
            func_ov039_020bc7e0(0x4100);
        }
        screen->needsRedraw = 2;
        func_0204f498(screen->panel, 0);
        screen->blinkStartTick = OS_GetTick_02003fd4();
        screen->savedGame = *data_0205fe0c;
        StartCardWriteFromSlot_02027034(0);
        screen->initialized = 1;
        data_ov080_020c5e00 = screen;
    }
    return PollSaveSlotReads_020c4d08(screen);
}
