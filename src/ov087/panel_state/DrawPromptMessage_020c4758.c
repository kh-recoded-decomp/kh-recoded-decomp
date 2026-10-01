#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xafc];
    u8 promptLayer[0x68];
    u8 labelTable[0xc];
    PanelStackEntry stack[6];
    int depth;
} PanelScene;

extern u16 *func_ov039_020bc1e4(int bgId);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void *func_ov027_020ba2a8(void *table, int index);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer_02001520(void *surface);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);

int DrawPromptMessage_020c4758(PanelScene *scene, int headerMessageId, int footerMessageId)
{
    int headerY;
    int frameId;
    int footerColor = 10;
    u16 *tileMap = func_ov039_020bc1e4(footerColor);

    CallVirtualHandlerSlot1_02001574(scene->promptLayer, 0);
    if (footerMessageId == 0x15) {
        headerY = 0x1c;
        frameId = 5;
        footerColor = 2;
    } else {
        headerY = 4;
        frameId = 6;
    }
    DrawTextAnchored_020015a0(scene->promptLayer, 0x78, headerY + 4, 2, 0x411,
                              func_ov027_020ba2a8(scene->labelTable, headerMessageId));
    DrawTextAnchored_020015a0(scene->promptLayer, 0x78, 0x36, footerColor, 0x414,
                              func_ov027_020ba2a8(scene->labelTable, footerMessageId));
    Text_UploadTileBuffer_02001520(scene->promptLayer);
    if (scene->stack[scene->depth].stateId != 0x10) {
        FillBackgroundLayerRect_02001a60(scene->promptLayer, tileMap, 1, 0xc, 0xf);
    }
    return frameId;
}
