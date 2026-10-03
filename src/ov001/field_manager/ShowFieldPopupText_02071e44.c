#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    u8 *tiles;
} FontData;

typedef struct {
    int active;
    u8 timer[0x1c];
    u64 duration;
    u8 pad_28[0xc];
    u8 layer[0x20];
    FontData *font;
    u8 pad_58[0x10];
    u16 *text;
    u16 *cursor;
    u8 *tileBuffer;
    int mode;
    int pad_78;
    int pending;
} FieldPopup;

typedef struct {
    u8 pad_000[0x47c];
    int busy;
    u32 pad_bits0 : 17;
    u32 locked : 1;
    u32 pad_bits1 : 14;
    u8 pad_484[0x88];
    int captionObject[0x11];
    FieldPopup popup;
} FieldManager;

typedef struct {
    u32 pad_00;
    FieldManager *manager;
} FieldManagerHandle;

typedef struct {
    u8 pad_000[0x214];
    u32 pad_bits0 : 11;
    u32 popupDisabled : 1;
    u32 pad_bits1 : 20;
} Session;

extern FieldManagerHandle data_ov001_020a04a4;
extern Session *data_ov001_020a0460;
extern void func_02052514(void *record, int value0, int value1, int value2, int value3);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern int LengthTerminatedHalfwords(u16 *text);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void CallVirtualHandlerSlot1_02001574(void *layer, int arg);
extern void Text_UploadTileBuffer_02001520(void *layer);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void *func_ov027_020ba2a8(int *object, int index);
extern void SetFieldCaptionText_02072178(int captionId);

BOOL ShowFieldPopupText_02071e44(u16 *text, u32 frames)
{
    FieldPopup *popup;
    FieldManager *manager;
    u8 *tiles;
    u32 size;

    manager = data_ov001_020a04a4.manager;
    popup = &manager->popup;

    if (manager->busy != 0) {
        return FALSE;
    }
    if (popup->active != 0) {
        return FALSE;
    }
    popup->pending = 1;
    popup->duration = (u64)((s64)frames * 0x82ea) >> 6;
    func_02052514(popup->timer, 4, 0x28000, 0, 500);
    if (popup->text != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(popup->text);
    }
    size = (LengthTerminatedHalfwords(text) + 1) * 2;
    popup->text = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, -4);
    popup->cursor = popup->text;
    func_01ff869c(text, popup->text, size);
    popup->mode = 4;
    CallVirtualHandlerSlot1_02001574(popup->layer, 1);
    tiles = popup->font->tiles;
    func_01ff878c(popup->tileBuffer, tiles, 0x20);
    func_01ff878c(popup->tileBuffer + 0x20, tiles + 0x3a0, 0x20);
    func_01ff878c(popup->tileBuffer + 0x40, tiles + 0x760, 0x20);
    Text_UploadTileBuffer_02001520(popup->layer);
    if (!data_ov001_020a0460->popupDisabled && ReadSessionPackedBits_02064574(0x1a00, 2) == 1) {
        SetFieldCaptionText_02072178((int)func_ov027_020ba2a8(manager->captionObject, 2));
        manager->locked = 1;
    }
    return TRUE;
}
