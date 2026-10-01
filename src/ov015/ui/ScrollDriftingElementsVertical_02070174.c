#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_0000[0xcc];
    fx32 speed[2];
    fx32 lane[2];
    u8 pad_00dc[0x6ac0 - 0xdc];
    u8 secondaryPanel[1];
} SceneContext;

extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b9360(void *panel, void *element, fx32 *position, int mode);
extern void func_ov027_020b91c8(void *panel, void *element, const fx32 *position, int mode);
extern unsigned int func_0202a9d0(unsigned int range);
extern SceneContext *data_ov015_0207e960;

void ScrollDriftingElementsVertical_02070174(void) {
    fx32 position[2];
    void *panel;

    panel = data_ov015_0207e960->secondaryPanel;
    func_ov027_020b9360(panel, func_ov027_020b90a4(panel, 5), position, 0);
    position[0] = data_ov015_0207e960->lane[0];
    position[1] -= data_ov015_0207e960->speed[0];
    if ((position[1] >> 12) < -0x40) {
        position[1] = 0xe8000;
        data_ov015_0207e960->speed[0] = func_0202a9d0(0x1000) + 0x1000;
        data_ov015_0207e960->lane[0] = (func_0202a9d0(0x70) + 0x10) << 12;
    }
    panel = data_ov015_0207e960->secondaryPanel;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 5), position, 0);

    panel = data_ov015_0207e960->secondaryPanel;
    func_ov027_020b9360(panel, func_ov027_020b90a4(panel, 6), position, 0);
    position[0] = data_ov015_0207e960->lane[1];
    position[1] -= data_ov015_0207e960->speed[1];
    if ((position[1] >> 12) < -0x40) {
        position[1] = 0xe8000;
        data_ov015_0207e960->speed[1] = func_0202a9d0(0x1000) + 0x1000;
        data_ov015_0207e960->lane[1] = (func_0202a9d0(0x70) + 0x80) << 12;
    }
    panel = data_ov015_0207e960->secondaryPanel;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 6), position, 0);
}
