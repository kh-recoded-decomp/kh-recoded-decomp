#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    s32 state;
    u32 flags;
    u8 pad_08[0x10];
    TextLayer textLayer;
    u16 *text;
} PopupWindow;

extern u32 TestPopupFlags_020c2778(PopupWindow *window, u32 mask);
extern void ClearPopupFlags_020c2764(PopupWindow *window, u32 mask);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int color);
extern void FlushBufferAndRunCallback_0200153c(TextLayer *layer);
extern void DestroyFndObjectList_020014f0(TextLayer *layer);
extern void *G2S_GetBG2ScrPtr_02006f0c(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);

void ClosePopupText_020c1ae8(PopupWindow *window)
{
    if (TestPopupFlags_020c2778(window, 1)) {
        if (window->text != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(window->text);
            window->text = NULL;
            CallVirtualHandlerSlot1_02001574(&window->textLayer, 0);
            FlushBufferAndRunCallback_0200153c(&window->textLayer);
            DestroyFndObjectList_020014f0(&window->textLayer);
        }
        ClearPopupFlags_020c2764(window, 1);
    }
    MIi_CpuClearFast_01ff8740(0, G2S_GetBG2ScrPtr_02006f0c(), 0x800);
}
