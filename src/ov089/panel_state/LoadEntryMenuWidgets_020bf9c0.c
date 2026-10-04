#include "nitro/types.h"

typedef struct SlotPoolConfig {
    u32 imageParams;
    u32 rest[3];
} SlotPoolConfig;

typedef struct {
    u8 pad_000[0x744];
    int entryCount;
} Ov089Menu;

extern SlotPoolConfig data_ov089_020c0500;

extern void *func_ov039_020bc1bc(void);
extern u32 BuildSlotImageParams_020bc220(int slot, u32 low);
extern void InitObjManagerAndMark_020b9060(void *container, SlotPoolConfig *config);
extern void func_ov027_020b8f98(void *container, u32 imageParams, int count);
extern void SetAllElementObjectModes_020b97fc(void *container, int mode);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern void SetFocusedWidget_020b96e4(void *container, void *widget);
extern void SetEntrySlotsVisible_020b9580(void *container, void *widget, BOOL visible);
extern void SetWidgetRootDpadEnabled_020b9874(void *container, BOOL enabled);
extern void func_ov027_020b9098(void *container, void *callback);
extern void ResolveEntryStoreWord_020b9088(void *container, int id, void *callback);
extern void func_ov089_020befc0(void);
extern void func_ov089_020c040c(void);
extern void func_ov089_020c045c(void);
extern void func_ov089_020c04c8(void);

void LoadEntryMenuWidgets_020bf9c0(Ov089Menu *menu)
{
    void *container = func_ov039_020bc1bc();
    SlotPoolConfig config = data_ov089_020c0500;

    config.imageParams = BuildSlotImageParams_020bc220(2, 0x10);
    InitObjManagerAndMark_020b9060(container, &config);
    func_ov027_020b8f98(container, BuildSlotImageParams_020bc220(2, 0x11), 10);
    SetAllElementObjectModes_020b97fc(container, 2);
    SetFocusedWidget_020b96e4(container, FindWidgetById_020b90a4(container, 2));
    if (menu->entryCount <= 1) {
        SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 9), FALSE);
    }
    SetWidgetRootDpadEnabled_020b9874(container, TRUE);
    func_ov027_020b9098(container, func_ov089_020befc0);
    ResolveEntryStoreWord_020b9088(container, 2, func_ov089_020c040c);
    ResolveEntryStoreWord_020b9088(container, 7, func_ov089_020c045c);
    ResolveEntryStoreWord_020b9088(container, 8, func_ov089_020c04c8);
}
