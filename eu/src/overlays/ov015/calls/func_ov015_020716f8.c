#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 value;
} PanelItem;

typedef struct {
    u8 pad_00[0xbb];
    u8 unk_BB;
    u8 pad_BC[0xc];
    u32 selectedValue;
    u8 pad_CC[0x6ac0 - 0xcc];
    u8 container[4];
} PanelState;

extern PanelItem *FindWidgetById(void *container, int itemId);
extern void SetEntrySlotsVisible(void *container, PanelItem *item, int flag);
extern void ApplySelectedSubitemValues(void *container, PanelItem *item, int useAlt);
extern void SetFocusedWidget(void *container, PanelItem *item);
extern void func_ov027_020b90b8(void *container, u32 callback);
extern void func_ov027_020b9604(void *container, PanelItem *item);
extern void func_ov027_020b96c0(void *container, PanelItem *item, int mode);
extern void func_ov015_0206eefc(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void UpdatePanelSelectionSound(PanelItem *item);
extern PanelState *data_ov015_0207e960;

void func_ov015_020716f8(void) {
    void *container;

    container = data_ov015_0207e960->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 4), 1);
    container = data_ov015_0207e960->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 7), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 7), 1);
    container = data_ov015_0207e960->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 8), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 8), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 1), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 2), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 3), 0);
    SetFocusedWidget(data_ov015_0207e960->container, FindWidgetById(data_ov015_0207e960->container, 8));
    data_ov015_0207e960->selectedValue = FindWidgetById(data_ov015_0207e960->container, 8)->value;
    func_ov015_0206eefc();
    data_ov015_0207e960->unk_BB = 0;
    func_ov027_020b90b8(data_ov015_0207e960->container, (u32)UpdatePanelSelectionSound);
    PlaySoundEffect(2, 2);
    container = data_ov015_0207e960->container;
    func_ov027_020b9604(container, FindWidgetById(container, 9));
    container = data_ov015_0207e960->container;
    func_ov027_020b96c0(container, FindWidgetById(container, 9), 0);
}
