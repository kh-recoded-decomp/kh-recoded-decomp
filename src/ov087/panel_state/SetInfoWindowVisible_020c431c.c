#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xb30];
    u8 infoLayer[0x40];
    PanelStackEntry stack[6];
    int depth;
    u8 pad_ba4[0x8];
    BOOL infoVisible;
} PanelScene;

extern void *func_ov039_020bc1bc(void);
extern u16 *func_ov039_020bc1e4(int bgId);
extern void func_ov039_020bc14c(int bgId, int x, int y, int width, int height);
extern void func_ov039_020bc104(int bgId);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void Text_UploadTileBuffer_02001520(void *surface);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);

void SetInfoWindowVisible_020c431c(PanelScene *scene, BOOL visible)
{
    void *container = func_ov039_020bc1bc();
    u16 *tileMap = func_ov039_020bc1e4(10);

    if (visible) {
        if (scene->stack[scene->depth].stateId != 0x10) {
            FillBackgroundLayerRect_02001a60(scene->infoLayer, tileMap, 6, 0xf, 0xf);
            Text_UploadTileBuffer_02001520(scene->infoLayer);
        }
    } else {
        func_ov039_020bc14c(10, 6, 0xf, 0x14, 2);
    }
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 0xd), visible);
    func_ov039_020bc104(10);
    scene->infoVisible = visible;
}
