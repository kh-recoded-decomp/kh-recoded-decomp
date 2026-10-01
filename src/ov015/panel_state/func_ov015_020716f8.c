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

extern PanelItem *func_ov027_020b90a4(void *container, int itemId);
extern void func_ov027_020b9580(void *container, PanelItem *item, int flag);
extern void ApplySelectedSubitemValues_020b94fc(void *container, PanelItem *item, int useAlt);
extern void func_ov027_020b96e4(void *container, PanelItem *item);
extern void func_ov027_020b9098(void *container, u32 callback);
extern void func_ov027_020b95e4(void *container, PanelItem *item);
extern void func_ov027_020b96a0(void *container, PanelItem *item, int mode);
extern void func_ov015_0206eefc(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov015_02072718(PanelItem *item);
extern PanelState *data_ov015_0207e960;

void func_ov015_020716f8(void) {
    void *container;

    container = data_ov015_0207e960->container;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 4), 1);
    container = data_ov015_0207e960->container;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 7), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 7), 1);
    container = data_ov015_0207e960->container;
    func_ov027_020b9580(container, func_ov027_020b90a4(container, 8), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 8), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 1), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 2), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, 3), 0);
    func_ov027_020b96e4(data_ov015_0207e960->container, func_ov027_020b90a4(data_ov015_0207e960->container, 8));
    data_ov015_0207e960->selectedValue = func_ov027_020b90a4(data_ov015_0207e960->container, 8)->value;
    func_ov015_0206eefc();
    data_ov015_0207e960->unk_BB = 0;
    func_ov027_020b9098(data_ov015_0207e960->container, (u32)func_ov015_02072718);
    PlaySoundEffect_0204d924(2, 2);
    container = data_ov015_0207e960->container;
    func_ov027_020b95e4(container, func_ov027_020b90a4(container, 9));
    container = data_ov015_0207e960->container;
    func_ov027_020b96a0(container, func_ov027_020b90a4(container, 9), 0);
}
