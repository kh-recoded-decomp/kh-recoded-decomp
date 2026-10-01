#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x84];
    u8 textBuffer[0x3fc];
    u32 pad_bits0 : 9;
    u32 hidden : 1;
    u32 pad_bits1 : 7;
    u32 locked : 1;
    u32 pad_bits2 : 14;
    u8 pad_484[0x518 - 0x484];
    int captionId;
    u8 textLayer[1];
} FieldCaption;

typedef struct {
    u32 pad_00;
    FieldCaption *caption;
} FieldManager;

extern FieldManager data_ov001_020a04a4;
extern int func_ov001_02072040(void);
extern void CallVirtualHandlerSlot1_02001574(void *layer, int arg);
extern void *UpdateFieldWidgetLayer_020736b4(int id);
extern void FillBackgroundLayerRect_02001a60(void *layer, void *dst, int a, int b, u8 c);
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9e00(void *obj, int id);
extern void func_0200160c(void *layer, int x, int y, int palette, int width, int textId, void *buffer, int size);
extern void Text_UploadTileBuffer_02001520(void *layer);

void SetFieldCaptionText_02072178(int captionId)
{
    FieldCaption *caption = data_ov001_020a04a4.caption;
    void *layer = caption->textLayer;

    if (caption->hidden != 1 && func_ov001_02072040() == 0) {
        if (caption->locked == 1) {
            if (captionId == 0) {
                return;
            }
            if (captionId == -1) {
                captionId = 0;
            }
        } else if (captionId == -1) {
            captionId = 0;
        }
        if (caption->captionId != captionId) {
            caption->captionId = captionId;
            CallVirtualHandlerSlot1_02001574(layer, 0);
            if (captionId != 0) {
                FillBackgroundLayerRect_02001a60(layer, UpdateFieldWidgetLayer_020736b4(0xb), 0xb, 0x13, 0xf);
                func_ov027_020b9e00(func_ov001_0207123c(), 0xb);
                func_0200160c(layer, 0x29, 0x18, 1, 0x214, captionId, caption->textBuffer, 0x50);
                func_0200160c(layer, 0x28, 0x17, 2, 0x214, captionId, caption->textBuffer, 0x50);
            }
            Text_UploadTileBuffer_02001520(layer);
            caption->locked = 0;
        }
    }
}



