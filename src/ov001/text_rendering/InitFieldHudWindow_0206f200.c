#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct MessageSet {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct FieldGraphics {
    u8 pad_00[0x24];
    u8 *charData;
} FieldGraphics;

typedef struct FieldHud {
    u8 pad_00[0x34];
    u8 window[0x20];
    FieldGraphics *graphics;
    u8 pad_58[0x18];
    u8 *palettes;
} FieldHud;

typedef struct FieldScene {
    u8 pad_000[0x50c];
    MessageSet messages;
    u8 pad_518[0x38];
    FieldHud hud;
    u8 pad_5c4[0x4];
    BOOL bottomRowEnabled;
} FieldScene;

extern const TextFrame data_ov001_0209dc74;
extern void *func_ov001_0207123c(void);
extern void *UpdateWidgetLayerDefault_020b9df0(void *widgets, int layer);
extern void func_ov027_020b9e00(void *widgets, int layer);
extern void *GetFieldFont3_020711e0(void);
extern void InitTextLayerAt_020014b0(void *window, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void CallVirtualHandlerSlot1_02001574(void *window, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *window);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern u32 func_ov001_02073634(u32 messageId);
extern void func_ov027_020ba25c(MessageSet *messages, u32 fileId, int compressed);
extern void LoadFieldBottomRowTiles_0206ed30(FieldScene *scene);

void InitFieldHudWindow_0206f200(FieldScene *scene, u8 *source)
{
    FieldHud *hud = &scene->hud;
    void *widgets = func_ov001_0207123c();
    TextFrame frame = data_ov001_0209dc74;
    void *charBase = UpdateWidgetLayerDefault_020b9df0(widgets, 9);
    u8 *charData;

    UpdateWidgetLayerDefault_020b9df0(widgets, 0x19);
    InitTextLayerAt_020014b0(hud->window, 1, charBase, GetFieldFont3_020711e0(), &frame);
    CallVirtualHandlerSlot1_02001574(hud->window, 1);
    func_ov027_020b9e00(widgets, 9);
    hud->palettes = NNSi_FndAllocFromDefaultHeap_0202a178(0x60);
    func_01ff878c(source + 0x29c0, hud->palettes, 0x20);
    func_01ff878c(source + 0x2a00, hud->palettes + 0x20, 0x20);
    func_01ff878c(source + 0x2a80, hud->palettes + 0x40, 0x20);
    charData = hud->graphics->charData;
    func_01ff878c(hud->palettes, charData, 0x20);
    func_01ff878c(hud->palettes + 0x20, charData + 0x3a0, 0x20);
    func_01ff878c(hud->palettes + 0x40, charData + 0x760, 0x20);
    FlushBufferAndRunCallback_0200153c(hud->window);
    func_ov027_020ba25c(&scene->messages, func_ov001_02073634(2), 0);
    if (scene->bottomRowEnabled) {
        LoadFieldBottomRowTiles_0206ed30(scene);
    }
}
