#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x7ec];
    u8 backgroundLayer[0x118];
    BOOL popupOpen;
} Ov089Menu;

extern void *func_ov039_020bc1bc(void);
extern u16 *func_ov039_020bc1e4(int bgId);
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b9580(void *panel, void *element, BOOL visible);
extern void func_ov039_020bc14c(int bgId, int x, int y, int width, int height);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void func_ov039_020bc104(int bgId);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ClosePopupWindow_020bfb8c(Ov089Menu *menu, int soundIndex)
{
    void *panel = func_ov039_020bc1bc();
    u16 *tileMap = func_ov039_020bc1e4(10);

    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xb), FALSE);
    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xc), FALSE);
    func_ov039_020bc14c(10, 1, 0xc, 0x1e, 10);
    FillBackgroundLayerRect_02001a60(menu->backgroundLayer, tileMap, 8, 0x12, 0xf);
    func_ov039_020bc104(10);
    PlaySoundEffect_0204d924(0, soundIndex);
    menu->popupOpen = FALSE;
}
