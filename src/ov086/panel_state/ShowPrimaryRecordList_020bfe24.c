#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x40];
    u8 listLayer[0xb4];
    void *selectedNode;
    u8 pad_0f8[0x134 - 0xf8];
    int pageIndex;
    u8 pad_138[0x154 - 0x138];
    BOOL arrowsVisible;
    u8 pad_158[0x190 - 0x158];
    u8 recordPool[0x58];
    u8 visitedPages;
} Ov086Menu;

extern u8 *func_ov039_020bc1cc(void);
extern void *func_ov027_020b90a4(u8 *panel, int elementId);
extern void func_ov027_020b9580(u8 *panel, void *element, BOOL visible);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void SelectListNodeOrFirst_020019b8(void *self, void *target);
extern void Text_UploadTileBuffer_02001520(void *surface);

void ShowPrimaryRecordList_020bfe24(Ov086Menu *menu)
{
    u8 *panel = func_ov039_020bc1cc();

    menu->arrowsVisible = FALSE;
    TagTracker_InvokeCallback_020b8210(menu->recordPool, FindActiveRecordById_020b8184(menu->recordPool, 0x3ea));
    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x14), FALSE);
    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x15), FALSE);
    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2d), FALSE);
    func_ov027_020b9580(panel, func_ov027_020b90a4(panel, 0x2e), FALSE);
    SelectListNodeOrFirst_020019b8(menu->listLayer, menu->selectedNode);
    Text_UploadTileBuffer_02001520(menu->listLayer);
    if (menu->visitedPages & (1 << menu->pageIndex)) {
        TagTracker_InvokeCallback_020b8210(menu->recordPool, FindActiveRecordById_020b8184(menu->recordPool, 0x3ed));
    } else {
        TagTracker_InvokeCallback_020b8210(menu->recordPool, FindActiveRecordById_020b8184(menu->recordPool, 0x3ef));
    }
}
