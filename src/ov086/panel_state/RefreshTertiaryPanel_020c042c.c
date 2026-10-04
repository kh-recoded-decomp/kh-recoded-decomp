#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc];
    u8 textLayer[0x34];
    u8 listLayer[0xb4];
    void *listNodes[7];
    u8 pad_110[0x134 - 0x110];
    int pageIndex;
    u8 pad_138[4];
    int stepCount;
    int itemId;
    u8 pad_144[0xc];
    BOOL arrowsVisible;
    u8 pad_154[0x174 - 0x154];
    u8 screenLayers[0x1c];
    u8 recordPool[0x10];
} Ov086Menu;

typedef struct {
    s32 x;
    s32 y;
} ElementOffset;

extern u8 *func_ov039_020bc1cc(void);
extern void *func_ov027_020b90a4(u8 *panel, int elementId);
extern void func_ov027_020b9580(u8 *panel, void *element, BOOL visible);
extern void func_ov027_020b91c8(u8 *panel, void *element, ElementOffset *offset, int flags);
extern void RefreshSecondaryPanel_020bff24(Ov086Menu *menu);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void SelectListNodeOrFirst_020019b8(void *self, void *target);
extern void Text_UploadTileBuffer_02001520(void *surface);
extern u16 *func_ov039_020bc1e4(int layerId);
extern void func_ov039_020bc104(int layerId);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);
extern u16 *UpdateWidgetLayerDefault_020b9df0(u8 *layers, int layerId);
extern void func_ov027_020b9e00(u8 *layers, int layerId);

void RefreshTertiaryPanel_020c042c(Ov086Menu *menu)
{
    u8 *panel = func_ov039_020bc1cc();
    ElementOffset offset;
    int nodeIndex;

    if (menu->stepCount <= 1) {
        RefreshSecondaryPanel_020bff24(menu);
    } else {
        TagTracker_InvokeCallback_020b8210(menu->recordPool, FindActiveRecordById_020b8184(menu->recordPool, 0x3ee));
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x14), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x15), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2d), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2e), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xe), FALSE);
        func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x8), TRUE);
    }
    switch (menu->stepCount) {
    case 0:
        nodeIndex = 0;
        break;
    case 1:
        nodeIndex = 5;
        break;
    case 2:
        nodeIndex = 6;
        break;
    }
    SelectListNodeOrFirst_020019b8(menu->listLayer, menu->listNodes[nodeIndex]);
    Text_UploadTileBuffer_02001520(menu->listLayer);
    offset.x = (menu->stepCount * 16 - 16) << 12;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 0xa), &offset, 4);
    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0xa), TRUE);
    FillBackgroundLayerRect_02001a60(menu->listLayer, func_ov039_020bc1e4(0x18), 1, 0, 0xf);
    func_ov039_020bc104(0x18);
    FillBackgroundLayerRect_02001a60(menu->textLayer, UpdateWidgetLayerDefault_020b9df0(menu->screenLayers, 0x19), 3, 3, 0xf);
    func_ov027_020b9e00(menu->screenLayers, 0x19);
}
