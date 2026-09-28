#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct GraphicsView {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} GraphicsView;

typedef struct HudContext {
    u8 pad_000[0x1c];
    u8 recordPool[0x624 - 0x1c];
    u16 iconPalettes[1][0x30];
} HudContext;

typedef struct HudGlobals {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04a4;
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern u32 func_ov001_020711ec(u32 index);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void func_0202b554(GraphicsView *view, void *file, int screenIndex, int characterIndex, int paletteIndex);
extern void func_0200344c(void *buffer, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadSlotIconGraphics_0207001c(int slot, int iconId)
{
    HudContext *context = data_ov001_020a04a4.context;
    void *file;
    GraphicsView view;

    TagTracker_InvokeCallback_020b8210(context->recordPool, FindActiveRecordById_020b8184(context->recordPool, slot + 8));
    TagTracker_InvokeCallback_020b8210(context->recordPool, FindActiveRecordById_020b8184(context->recordPool, slot + 2));
    file = func_0202c48c(func_ov001_020711ec(iconId + 8), 0xe);
    func_0202b554(&view, file, -1, 0, 0);
    func_0200344c(view.character->pRawData, view.character->szByte);
    func_0200344c(view.palette->pRawData, view.palette->szByte);
    GX_LoadBG3Char_02007b70(view.character->pRawData, (slot * 9 + 0x2c) * 0x20, view.character->szByte);
    func_02007250(view.palette->pRawData, (slot + 3) * 0x20, 0x20);
    func_01ff869c(view.palette->pRawData, context->iconPalettes[slot], 0x60);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
