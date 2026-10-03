#include "nitro/types.h"

typedef struct PanelElement PanelElement;

typedef struct PanelState {
    u8 pad_0000[0x6ac0];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern PanelElement *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b9620(void *panel, PanelElement *element);
extern u32 DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer);
extern void func_ov002_02066a68(void);

void ResetPanelMenuElements_020720e4(void)
{
    u8 *panel;

    panel = data_ov015_0207e960->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 11));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 30));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 31));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 32));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 33));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 9));
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9620(panel, func_ov027_020b90a4(panel, 17));
    DispatchContextCommand_02066c78(0x80000015, 1, 0, NULL);
    func_ov002_02066a68();
}
