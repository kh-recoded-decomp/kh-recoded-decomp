#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x174];
    u8 flagTracker[0x1c];
} Ov086Menu;

extern u8 *func_ov039_020bc1cc(void);
extern void *func_ov027_020b90a4(u8 *panel, int elementId);
extern void func_ov027_020b9580(u8 *panel, void *element, BOOL visible);
extern void func_ov027_020b9d18(u8 *tracker, int id);
extern void func_ov039_020bc14c(int arg0, int arg1, int arg2, int arg3, int arg4);

void ShowSecondaryPanelElementE_020c0320(Ov086Menu *menu)
{
    u8 *panel = func_ov039_020bc1cc();
    void *element;

    element = func_ov027_020b90a4(panel, 0x8);
    func_ov027_020b9580(panel, element, FALSE);
    element = func_ov027_020b90a4(panel, 0x14);
    func_ov027_020b9580(panel, element, FALSE);
    element = func_ov027_020b90a4(panel, 0x15);
    func_ov027_020b9580(panel, element, FALSE);
    element = func_ov027_020b90a4(panel, 0x2d);
    func_ov027_020b9580(panel, element, FALSE);
    element = func_ov027_020b90a4(panel, 0x2e);
    func_ov027_020b9580(panel, element, FALSE);
    element = func_ov027_020b90a4(panel, 0xa);
    func_ov027_020b9580(panel, element, FALSE);
    element = func_ov027_020b90a4(panel, 0xe);
    func_ov027_020b9580(panel, element, TRUE);
    func_ov027_020b9d18(menu->flagTracker, 0x19);
    func_ov039_020bc14c(0x18, 1, 0, 0xb, 2);
}
