#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8bc];
    u8 popupLayer[0x48];
    BOOL popupOpen;
} Ov089Menu;

extern void *func_ov039_020bc1bc(void);
extern u16 *func_ov039_020bc1e4(int bgId);
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b9580(void *panel, void *element, BOOL visible);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void func_ov001_020645dc(u32 flagId);
extern void func_ov039_020bc104(int bgId);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void OpenPopupWindow_020bfae8(Ov089Menu *menu)
{
    void *panel = func_ov039_020bc1bc();
    u16 *tileMap = func_ov039_020bc1e4(10);

    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xb), TRUE);
    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xc), TRUE);
    FillBackgroundLayerRect_02001a60(menu->popupLayer, tileMap, 1, 0xc, 0xf);
    menu->popupOpen = TRUE;
    func_ov001_020645dc(0xff4);
    func_ov039_020bc104(10);
    PlaySoundEffect_0204d924(0, 2);
}
