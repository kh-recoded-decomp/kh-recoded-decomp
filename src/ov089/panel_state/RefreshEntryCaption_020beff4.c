#include "nitro/types.h"

typedef struct {
    u8 pad_0[8];
    int textId;
} Ov089Entry;

typedef struct {
    u8 pad_000[0x738];
    Ov089Entry *entries;
    u8 pad_73C[0xc];
    int cursor;
    u8 pad_74C[0x38];
    u8 captionLayer[0x16c];
    u8 messages[4];
} Ov089Menu;

extern void CallVirtualHandlerSlot1_02001574(void *layer, int arg);
extern int GetGridTableValue_02051f48(int row, int column);
extern void *func_ov027_020ba2a8(void *messages, int index);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer_02001520(void *layer);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void RefreshEntryCaption_020beff4(Ov089Menu *menu, BOOL playSound)
{
    int textId = menu->entries[menu->cursor].textId;
    const u16 *text;

    CallVirtualHandlerSlot1_02001574(menu->captionLayer, 0);
    if (textId >= 0) {
        text = (const u16 *)GetGridTableValue_02051f48(textId, -1);
    } else {
        text = func_ov027_020ba2a8(menu->messages, 4);
    }
    DrawTextAnchored_020015a0(menu->captionLayer, 0x40, 2, 2, 0x411, text);
    Text_UploadTileBuffer_02001520(menu->captionLayer);
    if (playSound) {
        PlaySoundEffect_0204d924(0, 0);
    }
}
