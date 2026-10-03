#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 value;
} PanelItem;

typedef struct {
    u8 pad_00[0x6ac0];
    u8 container[4];
} PanelState;

extern PanelItem *func_ov027_020b90a4(void *container, int itemId);
extern void func_ov027_020b9580(void *container, PanelItem *item, int flag);
extern void ApplySelectedSubitemValues_020b94fc(void *container, PanelItem *item, int useAlt);
extern void func_ov027_020b9098(void *container, u32 callback);
extern void func_ov027_020b9620(void *container, PanelItem *item);
extern void func_ov002_020620fc(int mode);
extern PanelState *data_ov015_0207e960;

void HidePanelOptionSlots_020718fc(void) {
    void *container;

    func_ov002_020620fc(0);
    container = data_ov015_0207e960->container;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 4), 0);
    container = data_ov015_0207e960->container;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 7), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 7), 0);
    container = data_ov015_0207e960->container;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 8), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 8), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 1), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 2), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 3), 1);
    func_ov027_020b9098(data_ov015_0207e960->container, 0);
    container = data_ov015_0207e960->container;
    func_ov027_020b9620(container, func_ov027_020b90a4(container, 9));
}
