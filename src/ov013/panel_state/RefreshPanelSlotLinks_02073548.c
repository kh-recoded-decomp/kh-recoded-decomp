#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern int func_ov027_020b90a4(int panel, int id);
extern void func_ov027_020b9620(int panel, int handle);

/* Refreshes linked panel objects 0, 2, and 3. */
void RefreshPanelSlotLinks_02073548(void) {
    int handle;

    handle = func_ov027_020b90a4(data_ov013_02074ce0 + 0x6818, 0);
    func_ov027_020b9620(data_ov013_02074ce0 + 0x6818, handle);
    handle = func_ov027_020b90a4(data_ov013_02074ce0 + 0x6818, 2);
    func_ov027_020b9620(data_ov013_02074ce0 + 0x6818, handle);
    handle = func_ov027_020b90a4(data_ov013_02074ce0 + 0x6818, 3);
    func_ov027_020b9620(data_ov013_02074ce0 + 0x6818, handle);
}
